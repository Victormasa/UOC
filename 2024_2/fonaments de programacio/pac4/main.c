/*
* File: main.c
* Author: Victor Martinez Santos
* Course: 20242
* Description: PAC4-PEC4-CAA4
*/

#include <stdio.h>
#include <string.h>

#define MAX_CHARS_FILE 12
#define MAX_CHARS_PHONE 100

typedef struct
{   
    /* data */
    char model[MAX_CHARS_PHONE];
    int screen;
    int ram_memory;
} tPhone;

int main() {
    /* Definition and initialization of variables */
    FILE *fileToRead = NULL;
    char filename[MAX_CHARS_FILE];
    tPhone phone1;
    tPhone phone2;
    char bestPhone[MAX_CHARS_PHONE];

    /*Open file 1*/
    printf("FILENAME 1?\n");
    scanf("%s", filename);
    fileToRead = fopen(filename, "r");

    /*Read file*/
    fscanf(fileToRead, "%s %d %d", phone1.model, &phone1.screen, &phone1.ram_memory);
    fclose(fileToRead);

    /*Open file 2*/
    printf("FILENAME 2?\n");
    scanf("%s", filename);
    fileToRead = fopen(filename, "r");

    /*Read file*/
    fscanf(fileToRead, "%s %d %d", phone2.model, &phone2.screen, &phone2.ram_memory);
    fclose(fileToRead);

    /* Compare the two phones */
    if (phone1.screen == phone2.screen) {
        if (phone1.ram_memory == phone2.ram_memory) {
            strcpy(bestPhone, phone2.model);
        }
        else {
            if (phone1.ram_memory > phone2.ram_memory) {
                strcpy(bestPhone, phone1.model);
            }
            else {
                strcpy(bestPhone, phone2.model);
            }
        }
    }
    else {
        if (phone1.screen > phone2.screen) {
            strcpy(bestPhone, phone1.model);
        }
        else {
            strcpy(bestPhone, phone2.model);
        }
    };

    printf("OUTPUT\n");

    printf("THE BEST CELL PHONE IS %s\n", bestPhone);

    return 0;
}
