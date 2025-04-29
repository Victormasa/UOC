/*
* File: main.c
* Author: UOC
* Course: 20242
* Description: PR2
*/

/* System header files */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*Constants for file reading */
#define MAX_FILE_NAME 100+1
#define MAX_LINE 514

#define MAX_NAME_LENGTH 25+1
#define DAYS_IN_WEEK 7

#define MAX_RESORTS 20   /* Max. number of ski resorts */

/* Constants for converting Celsius to Fahrenheit */
#define FAHRENHEIT_FACTOR 1.8f
#define FAHRENHEIT_OFFSET 32.0f

#define SNOW_TEMP_THRESHOLD 0.0f   /* Temperature below for snow */
#define SNOW_RAIN_THRESHOLD 10.0f  /* Minimum rain in millimeters for snow */

/*****************************/

/* User defined types */
typedef enum {CELSIUS = 1, FAHRENHEIT} tTemperature; /* Type of temperature scale */

typedef struct {
    float temperature;      /* Temperatura in Celcius */
    float rainAccumulation; /* accumulated rainfall in millimeters */
} tWeatherData;

typedef struct {
    char resortName[MAX_NAME_LENGTH];     /* Name of the ski resort */
    tWeatherData weekData[DAYS_IN_WEEK];  /* Array to store weather data for each day of the week */
} tSkiResort;


/* Functions prototypes declaration for auxiliary functions */
void loadSkiResortsDataFromFile(const char* filename, tSkiResort resorts[], int* resortCount, bool* isRead);

/* Functions prototypes declaration for exercises */
/* Exercise 1 */
float celsiusToFahrenheit (float temperatureCelsius) {
/*F = C * 9/5 + 32*/
	float temperatureFahrenheit = 0.0f;
	
	temperatureFahrenheit = temperatureCelsius * FAHRENHEIT_FACTOR + FAHRENHEIT_OFFSET;
	return temperatureFahrenheit;

}

/* Exercise 2 */
float avgTemperature (float sumTemperatures, int days) {
	float avgTemp = 0.00f;
	avgTemp = sumTemperatures/(float)days;
	return avgTemp;
}

/* Exercise 3 */
bool isSnowyWeek(tWeatherData weekData[], int days) {
	for (int i = 0; i < days; i++) {
		if (weekData[i].temperature <= SNOW_TEMP_THRESHOLD && weekData[i].rainAccumulation >= SNOW_RAIN_THRESHOLD) {
			return true; // Return true as soon as one day meets the condition
		}
	}
	return false; // Return false if no day meets the condition
}

/* main */
int main(int argc, char **argv) {
	
	tSkiResort resorts[MAX_RESORTS];
	tTemperature temperatureScale = CELSIUS; /* Default temperature scale */
	
	bool isRead = NULL; /* Flag to check if data was read successfully */
	bool itWillSnow = false;
	float avgTemp = 0.0f;
	float sumTemperatures = 0.0f;
	
	int i = 0;
	int d = 0;
	int resortsCount = 0;
	char filename[MAX_FILE_NAME];
	
	/* load data from file*/ 
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");
    scanf("%s", filename);	
    loadSkiResortsDataFromFile(filename, resorts, &resortsCount, &isRead);	
	
	if (isRead) {
        do {
            printf("SELECT TEMPERATURE SCALE (1-CELSIUS, 2-FAHRENHEIT) >>\n");
            scanf("%d", &temperatureScale);
			if (temperatureScale < CELSIUS || temperatureScale > FAHRENHEIT) {
				printf("INVALID DATA, TRY AGAIN! \n");
			}
        } while (temperatureScale < CELSIUS || temperatureScale > FAHRENHEIT);

		/* Print the data */
		printf("NAME AVG_TEMP IT_WILL_SNOW (1-TRUE, 0-FALSE)\n");
		printf("--------------------------------------------\n");
		
		for (i = 0; i < resortsCount; i++) {
			itWillSnow = isSnowyWeek(resorts[i].weekData, DAYS_IN_WEEK);
			for (d = 0; d < DAYS_IN_WEEK; d++) {
				if (temperatureScale == FAHRENHEIT) {
					resorts[i].weekData[d].temperature = celsiusToFahrenheit(resorts[i].weekData[d].temperature);
				}
				sumTemperatures += resorts[i].weekData[d].temperature;
			}
		
			avgTemp = avgTemperature(sumTemperatures, DAYS_IN_WEEK);
			printf("%s %.2f, %d\n", resorts[i].resortName , avgTemp, itWillSnow);
			sumTemperatures = 0.0f; // Reset sum for next resort
		}
	}

	else {
        printf("NO RESORTS RECOVERED");
    }

	return 0;
}


/* Function to load ski resort data from file */
void loadSkiResortsDataFromFile(const char* filename, tSkiResort resorts[], int* resortCount, bool* isRead) {
    FILE* fin = NULL;
    char line[MAX_LINE];
	char buffer[MAX_LINE];
    tSkiResort newResort;
    int i = 0;
	
	float temperatureVector [DAYS_IN_WEEK];
	float rainAccumulationVector [DAYS_IN_WEEK];
	tWeatherData weatherDataTmp;

    /* Open the input file */
    if ((fin = fopen(filename, "r")) != NULL) {
        /* Read all the resorts */
        *resortCount = 0;

        while (!feof(fin) && *resortCount < MAX_RESORTS) {
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
					sscanf(buffer, "%f %f %[^\n]s", &temperatureVector[i], &rainAccumulationVector[i], buffer);
				}
	
				/* Generate wheather data and add them to the vector */
				for (i = 0; i < DAYS_IN_WEEK; i++) {
					weatherDataTmp.temperature = temperatureVector[i];
					weatherDataTmp.rainAccumulation = rainAccumulationVector[i];
					newResort.weekData[i] = weatherDataTmp;
				}

                /* Add resort to resorts vector */
                resorts[*resortCount] = newResort;
                /* Increment the counter */
                *resortCount = *resortCount + 1;
            }
        }
        /* Close the file */
        fclose(fin);
        *isRead = true;
    } else {
        *isRead = false;
    }
}

