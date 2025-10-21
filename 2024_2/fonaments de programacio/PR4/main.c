/*
* File: main.c
* Author: UOC
* Course: 20242
* Description: PR4
*/

/* System header files */
#include "forecast.h"

/* main */
int main(int argc, char **argv)
{
	tSkiResortsTable resorts;
	tTemperature scale = 1; /* Default temperature scale */
	tSkiResortsTable resortsResultsTable;
	char filename[MAX_FILE_NAME];
	bool isRead = false;
	
	/* Variables for user input */
	char resortName[MAX_NAME_LENGTH];
    bool found = false;
	
    /* Initializations */
    resortsResultsTable.nResorts = 0;
    
	/* Data input */		
	/* Input the temperature scale */
	printf("INPUT DATA\n");
	
	do {
		printf ("SELECT TEMPERATURE SCALE (1-CELSIUS, 2-FAHRENHEIT) >>\n");
		scanf("%u", &scale);
		getchar();

		/* Data validation */
		if (scale < CELSIUS || scale > FAHRENHEIT) {
			printf("INVALID DATA, TRY AGAIN!\n");
		}
	} while (scale < CELSIUS || scale > FAHRENHEIT);
		
	
	/* load data from file */ 
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");
    scanf("%s", filename);
	loadSkiResortsDataFromFile(filename, scale, &resorts, &isRead);	
	
	if (isRead) { /* Data successfully loaded */
		
		/* Exercise 2 */
		/* Retrieve and display ski resorts with any emergency. */
		getResortsWithEmergencies(&resorts, &resortsResultsTable);
		printf("\nRESULTS:\n");
		printf("SKI RESORTS WITH EMERGENCIES: R W S\n");
		printf("===================================\n");
        /* Exercise 3 */
        /* Print resorts and their emergencies */
        if (resortsResultsTable.nResorts > 0) { 
			writeResorts(&resortsResultsTable);
        } else {
            printf("NO EMERGENCY SITUATIONS\n");
        }

        /* Ask for resort to find */
        printf("\nSELECT RESORT BY NAME >> \n");
        scanf("%s", resortName);

        /* Exercise 4 */
        /* Search for resort in emergency list */
		found = isResortInEmergencies(&resortsResultsTable, resortName);
        if (found) {
               printf("RESORT IN EMERGENCY LIST\n");
           } else {
               printf("RESORT NOT IN EMERGENCY LIST\n");
           }
	}
	else {
		/* No data recovered */
		printf("NO SKI RESORTS RECOVERED\n");	
	}
		
	return 0;
}







