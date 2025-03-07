/*
* File: main.c
* Author: UOC
* Course: 20242
* Description: PAC2-PEC2-CAA2
*/

/* System header files */
#include <stdio.h>
#include <stdbool.h>

typedef enum {MOTORCYCLE, CAR, VAN, TRUCK} tVehicle;
typedef enum {MON, TUE, WED, THU, FRI, SAT, SUN} tDay;

int main()
{
    /* Define and initialize variables */
    tVehicle vehicle;
    bool isElectric;
    int passengers;
    tDay day;
    bool hasDiscount = false;  // Aquí podrás decidir la lógica necesaria

    /* Input the data */
    printf("INPUT\n");
    
    // Vehicle type
    printf("VEHICLE (0-MOTORCYCLE, 1-CAR, 2-VAN, 3-TRUCK)?\n");
    int vehicleTemp;
    scanf("%d", &vehicleTemp);
    vehicle = (tVehicle)vehicleTemp;
    
    // Is the vehicle electric?
    printf("IS AN ELECTRIC VEHICLE (0-FALSE, 1-TRUE)?\n");
    int isElectricTemp;
    scanf("%d", &isElectricTemp);
    isElectric = (isElectricTemp != 0);
    
    // How many passengers?
    printf("PASSENGERS?\n");
    scanf("%d", &passengers);
    
    // What day of the week is it?
    printf("DAY (0-MON, 1-TUE, 2-WED, 3-THU, 4-FRI, 5-SAT, 6-SUN)?\n");
    int dayTemp;
    scanf("%d", &dayTemp);
    day = (tDay)dayTemp;
 
    /* Determine using only expressions whether the highway user is entitled to discount or not */
    // hasDiscount = (vehicle == CAR && isElectric && (day == SAT || day == SUN));
    hasDiscount = (
        ((day == 0 || day == 1) && (vehicle >= 0 && vehicle <= 2)) || 
        ((day >= 0 && day <= 4) && vehicle == 3) ||
        ((vehicle == 1 && passengers >= 4) || isElectric)
    );

    /* Output results */
    printf("OUTPUT\n");
    printf("HAS DISCOUNT (0-FALSE, 1-TRUE): %d\n", hasDiscount);
}