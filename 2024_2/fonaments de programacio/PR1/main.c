/*
* File: main.c
* Author: Victor Martinez Santos
* Course: 20242
* Description: PR1
*/

/* System header files */
#include <stdio.h>
#include <stdlib.h>

#define DAYS_OF_THE_WEEK 7
#define HEAVY_RAIN_THRESHOLD 50
#define MAX_TEMP 10
#define MIN_TEMP -10
#define MAX_FILE_NAME 100

typedef enum {MONDAY=1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY} tDays;

int main() {
    /*Define variables - arrays dimensionados para índices del 1 al 7*/
    int avgTemperatures[DAYS_OF_THE_WEEK+1] = {0};
    int avgRainFall[DAYS_OF_THE_WEEK+1] = {0};
    int heavyRainfallDays[DAYS_OF_THE_WEEK+1] = {0};
    int abruptChangeTemperatureDays[DAYS_OF_THE_WEEK+1] = {0};
    int i = 1;
    int abruptChangeCount = 0;
    float sumTemperature = 0.0f;
    float sumRain = 0.0f;
    FILE *fileToRead = NULL;
    char filename[MAX_FILE_NAME];
    float averageTemperature = 0.0f;
    float averageRainfall = 0.0f;
    int heavyRainfallCount = 0;

    /*Get the file name and open*/
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >> \n");
    scanf("%s", filename);
    fileToRead = fopen(filename, "r");

    /*Load file input (desde 1 hasta DAYS_OF_THE_WEEK)*/
    for (i = 1; i <= DAYS_OF_THE_WEEK; i++) {
        fscanf(fileToRead, "%d %d", &avgTemperatures[i], &avgRainFall[i]);
        sumTemperature += (float)(avgTemperatures[i]);
        sumRain += (float)(avgRainFall[i]);
    }
    
    /*Close file*/
    fclose(fileToRead);

    /*Calculate average temperature and rainfall*/
    averageTemperature = sumTemperature /(float)(DAYS_OF_THE_WEEK);
    averageRainfall = sumRain / (float)(DAYS_OF_THE_WEEK);

    /*Data Processing*/
    /*To check abrupt changes on tempreature we check with a for loop if its difference is more than 10 or less than -10*/
    for (i = 1; i < DAYS_OF_THE_WEEK; i++) {
        if ((avgTemperatures[i] - avgTemperatures[i+1]) >= MAX_TEMP ||
            (avgTemperatures[i] - avgTemperatures[i+1]) <= MIN_TEMP) {
            abruptChangeCount++;
            abruptChangeTemperatureDays[abruptChangeCount] = i + 1;  // i representa el día
        }
    }
    
    /*Check if the rain is bigger than 50mm with a for loop to take every value from avgRainFall*/
    for (i = 1; i <= DAYS_OF_THE_WEEK; i++) {
        if (avgRainFall[i] >= HEAVY_RAIN_THRESHOLD) {
            heavyRainfallCount++;
            heavyRainfallDays[heavyRainfallCount] = i;
        }
    }

    /*Print results*/
    printf("ESTIMATED WEEKLY AVERAGE TEMPERATURE (CELSIUS): %.2f \n", averageTemperature);
    printf("ESTIMATED WEEKLY AVERAGE RAINFALL (MILLIMETERS): %.2f \n", averageRainfall);

    /*check for weather alerts*/
    if (abruptChangeCount > 0 || heavyRainfallCount > 0) {
        printf("WEATHER ALERTS (1-MONDAY, 2-TUESDAY, 3-WEDNESDAY, 4-THURSDAY, 5-FRIDAY, 6-SATURDAY, 7-SUNDAY): \n");

        /*Days with abrupt temperature changes*/
        if (abruptChangeCount > 0) {
            printf("DAYS WITH ESTIMATED ABRUPT TEMPERATURE CHANGES:\n");
            for (i = 1; i <= abruptChangeCount; i++) {
                printf("%d\n", abruptChangeTemperatureDays[i]);
            }
        }

        /*Days with estimated heavy rainfall*/
        if (heavyRainfallCount > 0) {
            printf("ESTIMATED HEAVY RAINFALL DAYS: \n");
            for (i = 1; i <= heavyRainfallCount; i++) {
                printf("%d\n", heavyRainfallDays[i]);
            }
        }
    }
    else {
        printf("NO WEATHER ALERTS");
    }
    
    return 0;
}