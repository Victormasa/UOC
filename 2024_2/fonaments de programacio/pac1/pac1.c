/*
* File: main.c
* Author: Víctor Martinez Santos
* Course: 20242
* Description: PAC1-PEC1-CAA1
*/

/* System header files */
#include <stdio.h>

/* Constants */
#define SECONDS_IN_A_DAY 86400 //24*60*60
#define SECONDS_IN_AN_HOUR 3600 //60*60
#define SECONDS_IN_A_MINUTE 60

/* Main function */
int main() {
    /* Definition and initialization of variables */
    int seconds=0;
    int days=0;
    int hours=0;
    int minutes=0;

    /* Input data */
    printf("INPUT\n");
    printf("SECONDS?\n");
    scanf("%d", &seconds);

    /* Calculations */
    days = seconds / SECONDS_IN_A_DAY;
    seconds = seconds % SECONDS_IN_A_DAY;

    hours = seconds / SECONDS_IN_AN_HOUR;
    seconds = seconds % SECONDS_IN_AN_HOUR;

    minutes = seconds / SECONDS_IN_A_MINUTE;
    seconds = seconds % SECONDS_IN_A_MINUTE;

    printf("%d DAYS\n %d HOURS\n %d MINUTES \n %d SECONDS", days, hours, minutes, seconds);

    return 0;
}