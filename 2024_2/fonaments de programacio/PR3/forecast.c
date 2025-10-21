#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include "forecast.h"


float celsiusToFahrenheit(float celsius) {
    return (celsius * FAHRENHEIT_FACTOR) + FAHRENHEIT_OFFSET;
}

float fahrenheitToCelsius(float fahrenheit) {
    return (fahrenheit - FAHRENHEIT_OFFSET) * CELSIUS_FACTOR;
}

void loadSkiResortsDataFromFile(const char* filename, tTemperature scale, tSkiResortsTable* resortsTable, bool* isRead) {
    FILE* fin = fopen(filename, "r");
    if (!fin) {
        *isRead = false;
        return;
    }

    resortsTable->nResorts = 0;
    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, fin) && resortsTable->nResorts < MAX_RESORTS) {
        char* token = strtok(line, " \n");
        if (!token) continue;

        tSkiResort newResort;
        strncpy(newResort.resortName, token, MAX_NAME_LENGTH);

        float tempVec[DAYS_IN_WEEK];
        float rainVec[DAYS_IN_WEEK];

        for (int i = 0; i < DAYS_IN_WEEK; i++) {
            token = strtok(NULL, " \n");
            if (!token) break;
            tempVec[i] = atof(token);

            token = strtok(NULL, " \n");
            if (!token) break;
            rainVec[i] = atof(token);
        }

        for (int i = 0; i < DAYS_IN_WEEK; i++) {
            float temp = (scale == FAHRENHEIT) ? celsiusToFahrenheit(tempVec[i]) : tempVec[i];
            newResort.weekData[i].temperature = temp;
            newResort.weekData[i].rainAccumulation = rainVec[i];
        }

        resortsTable->resorts[resortsTable->nResorts++] = newResort;
    }

    fclose(fin);
    *isRead = true;
}

bool isSnowyWeek(tSkiResort resort, tTemperature scale) {
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        float temp = resort.weekData[i].temperature;
        if (scale == FAHRENHEIT) {
            temp = fahrenheitToCelsius(temp);
        }
        if (temp <= SNOW_TEMP_CELSIUS_THRESHOLD && resort.weekData[i].rainAccumulation > SNOW_RAIN_THRESHOLD) {
            return true;
        }
    }
    return false;
}
void getExtremeTempForecast(tSkiResort resort,  tTemperature scale, float* minTemperature, float* maxTemperature) {
    *minTemperature = 1000.0f;
    *maxTemperature = -1000.0f;

    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        float temp = resort.weekData[i].temperature;
        if (temp < *minTemperature) {
            *minTemperature = temp;
        }
        if (temp > *maxTemperature) {
            *maxTemperature = temp;
        }
    }
}



tSkiResortsTable getResortsWithSnowPrediction(tSkiResortsTable inputTable, tTemperature scale) {
    tSkiResortsTable outputTable = {.nResorts = 0};
    for (int i = 0; i < inputTable.nResorts; i++) {
        if (isSnowyWeek(inputTable.resorts[i], scale)) {
            outputTable.resorts[outputTable.nResorts++] = inputTable.resorts[i];
        }
    }
    return outputTable;
}
