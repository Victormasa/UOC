#include "forecast.h"

/* Function that converts Celsius degrees to Fahrenheit */
float celsiusToFahrenheit(float celsius) {
	float fahrenheit;
	
	fahrenheit = (celsius * FAHRENHEIT_FACTOR) + FAHRENHEIT_OFFSET;
    return fahrenheit;
}

/* Function that converts Fahrenheit degrees to Celsius */
float fahrenheitToCelsius(float fahrenheit) {
	float celsius;
	
	celsius = (fahrenheit - FAHRENHEIT_OFFSET) * CELSIUS_FACTOR;	
    return celsius;
}


/* Function to load ski resort data from file */
void loadSkiResortsDataFromFile(const char* filename, tTemperature scale, tSkiResortsTable *resortsTable, bool* isRead) {
    #define TYPEDEF_COMPLETED
    FILE* fin = NULL;
    char line[MAX_LINE];
	char buffer[MAX_LINE];
    tSkiResort newResort;
    int i;
	
	float temperature;
	tWeatherData weatherDataTmp;

    /* Open the input file */
    if ((fin = fopen(filename, "r")) != NULL) {
		
		/* Initialize resort table */
		resortsTable -> nResorts = 0;
				
        /* Read all the resorts */  
        while (!feof(fin) && resortsTable -> nResorts < MAX_RESORTS) {
            /* Remove any content from the line */
            line[0] = '\0';

            /* Read one line (maximum MAX_LINE chars) and store it in "line" variable */
            fgets(line, MAX_LINE - 1, fin);

            /* Ensure that the string is ended by 0 */
            line[MAX_LINE - 1] = '\0';

            if (strlen(line) > 0) {
                /* Obtain the resort name and weather data from the file line */
                sscanf(line, "%s %[^\n]s", newResort.resortName, buffer);
				for (i = 0; i < DAYS_IN_WEEK; i++) {
					sscanf(buffer, "%f %f %f %d %[^\n]s", &temperature, &weatherDataTmp.rainAccumulation, 
                           &weatherDataTmp.windSpeed, &weatherDataTmp.snowAccumulation, buffer);
	

					weatherDataTmp.scale = scale;
					/* If Fahrenheit is needed, convert the temperature */					
					if (weatherDataTmp.scale == FAHRENHEIT) {
						weatherDataTmp.temperature = celsiusToFahrenheit(temperature);
					}	
					else {
						weatherDataTmp.temperature = temperature;
					}
					
					newResort.weekData[i] = weatherDataTmp;
				}	
				
				
				/* Add new resort to resorts vector */
				resortsTable->resorts[resortsTable->nResorts] = newResort;
                /* Increment the resorts counter. */
				resortsTable->nResorts++ ;
                	
            }
        }
        /* Close the file */
        fclose(fin);
        *isRead = true;
    } else {
        *isRead = false;
    }
}

/* Exercise 2 */
/* Action to get resorts with some emergency */
void getResortsWithEmergencies(tSkiResortsTable *resorts, tSkiResortsTable *resortsResultsTable) {
    int i;

    /* Initialize the results table */
    resortsResultsTable->nResorts = 0;

    /* Iterate through all resorts */
    for (i = 0; i < resorts->nResorts; i++) {
        getExtremeConditions(&resorts->resorts[i]);

        /* Check if there is any emergency */
        if (resorts->resorts[i].hasRainEmergency || resorts->resorts[i].hasSnowEmergency || resorts->resorts[i].hasWindEmergency) {
            /* Insert resort into results table */
            insertOrderedResort(&resorts->resorts[i], resortsResultsTable);
        }
    }
}

/* Exercise 2.1 */
/* Action to modify resort with emergencies */
void getExtremeConditions(tSkiResort *resort) {
    int i;
    int rainAccumulationDay = 0;
    int windAccumulationDay = 0;
    int snowAccumulationDay = 0;

    for (i = 0; i < DAYS_IN_WEEK; i++) {
        /* Check for rain emergency */
        if (resort->weekData[i].rainAccumulation > HEAVY_RAIN_THRESHOLD) {
            rainAccumulationDay++;
            if (rainAccumulationDay >= RAIN_EMERGENCY_DAYS) {
                resort->hasRainEmergency = true;
            }
        }
        else {
            rainAccumulationDay = 0;
        }
        
        /* Check for wind emergency */
        if (resort->weekData[i].windSpeed > WIND_THRESHOLD) {
            windAccumulationDay++;
            if (windAccumulationDay >= WIND_EMERGENCY_DAYS) {
                resort->hasWindEmergency = true;
            }
        } 
        else {
            windAccumulationDay = 0;
        }
        if (isSnowRecommended(resort->weekData[i].snowAccumulation)) {
            snowAccumulationDay++;
            if (snowAccumulationDay >= SNOW_EMERGENCY_DAYS) {
                resort->hasSnowEmergency = true;
            }
        }
    }
}

/* Exercise 2.2 */
/* Function that test if snow levels is recommendedEs */
bool isSnowRecommended(int snowAccumulation) {
    bool isRecommended = false;

    if (snowAccumulation >= MINIMUM_SNOW_LEVEL && snowAccumulation <= MAXIMUM_SNOW_LEVEL) {
        isRecommended = false;  // Snow level is within the recommended range
    } else {
        isRecommended = true; // Snow level is not recommended
    }

    return isRecommended;

}

/* Exercise 2.3 */
/* Action to insert resort in table sorted by name */
void insertOrderedResort(tSkiResort *resort, tSkiResortsTable *resortsTable) {
    int i = 0;
    int j = 0;
    bool foundPos = false;

    /* Find the position to insert the new resort */
    if (!(resortsTable->nResorts == 0 || strcmp(resort->resortName, resortsTable->resorts[0].resortName) < 0)) {
        i = 0;
        while (i < resortsTable->nResorts && !foundPos) {
            if (strcmp(resort->resortName, resortsTable->resorts[i].resortName) < 0) {
                foundPos = true;
            } else {
                i++; 
            }
        }
    } else {
        i = 0;
    }
    

    for (j = resortsTable->nResorts; j > i; j--) {
        resortsTable->resorts[j] = resortsTable->resorts[j - 1];
    }
    /* Insert the new resort at the found position */
    resortsTable->resorts[i] = *resort;
    resortsTable->nResorts++;
}

/* Exercise 3 */
/* Action to print resort data */
void writeResorts(tSkiResortsTable *resortsTable) {
    int i;

    /* Iterate through all resorts */
    for (i = 0; i < resortsTable->nResorts; i++) {
        printf("%s", resortsTable->resorts[i].resortName);
        printf(" %d", resortsTable->resorts[i].hasRainEmergency);
        printf(" %d", resortsTable->resorts[i].hasWindEmergency);
        printf(" %d", resortsTable->resorts[i].hasSnowEmergency);
        printf("\n");
    }
}

/* Exercise 4 */
/* Function that test if resort is in emergencies resort list */
bool isResortInEmergencies(tSkiResortsTable *resultTable, const char *resortName) {
    int i = 0;
    bool found = false;

    /* Iterate through all resorts */
    for (i = 0; i < resultTable->nResorts; i++) {
        if (strcmp(resultTable->resorts[i].resortName, resortName) == 0) {
            found = true;  // Resort found
        }
    }
    return found;  
}