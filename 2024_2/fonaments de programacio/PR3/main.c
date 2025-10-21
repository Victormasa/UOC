#include <stdio.h>
#include <string.h>
#include "forecast.h"

int main(void) {
    tSkiResortsTable resorts, snowyResorts;
    float minTemp, maxTemp;
    char filename[MAX_FILE_NAME];
    bool isRead;
    tTemperature scale;

    printf("INPUT DATA\n");
    do {
        printf("SELECT TEMPERATURE SCALE (1-CELSIUS, 2-FAHRENHEIT) >>\n");
        scanf("%u", &scale);
        if (scale < CELSIUS || scale > FAHRENHEIT) {
            printf("INVALID DATA, TRY AGAIN!\n");
        }
    } while (scale < CELSIUS || scale > FAHRENHEIT);

    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");
    scanf("%s", filename);

    loadSkiResortsDataFromFile(filename, scale, &resorts, &isRead);

    if (!isRead) {
        printf("NO RESORTS RECOVERED\n");
        return 1;
    }

    printf("\nRESULTS:\n");
    printf("SKI_STATION MIN_TEMP MAX_TEMP\n");
    printf("=============================\n");

    for (int i = 0; i < resorts.nResorts; i++) {
        getExtremeTempForecast(resorts.resorts[i], scale, &minTemp, &maxTemp);
        printf("%s %.2f %.2f\n", resorts.resorts[i].resortName, minTemp, maxTemp);
    }

    snowyResorts = getResortsWithSnowPrediction(resorts, scale);
    if (snowyResorts.nResorts == 0) {
        printf("NO SNOW FORECAST\n");
    } else {
        printf("\nSNOWY SKI RESORTS\n=================\n");
        for (int i = 0; i < snowyResorts.nResorts; i++) {
            printf("%s\n", snowyResorts.resorts[i].resortName);
        }
    }

    return 0;
}