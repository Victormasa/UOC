/*
* File: main.c
* Author: Victor Martinez Santos
* Course: 20242
* Description: PAC3-PEC3-CAA3
*/


/* System header files */
#include <stdio.h>
#include <string.h>

/* User defined constants */
#define MAX_ELEMENTS 9+1
#define MAX_FILE_NAME 200

/* Main function */
int main() {
    /* Definition and initialization of variables */
    char dice1[MAX_ELEMENTS] = "....O....";
    char dice2[MAX_ELEMENTS] = "..O...O..";
    char dice2_b[MAX_ELEMENTS] = "O.......O";
    char dice3[MAX_ELEMENTS] = "O...O...O";
    char dice3_b[MAX_ELEMENTS] = "..O.O.O..";
    char dice4[MAX_ELEMENTS] = "O.O...O.O";
    char dice5[MAX_ELEMENTS] = "O.O.O.O.O";
    char dice6[MAX_ELEMENTS] = "OOO...OOO";
    char dice6_b[MAX_ELEMENTS] = "O.OO.OO.O";
    char dice_input[MAX_ELEMENTS];
    char file[MAX_FILE_NAME];
    int result = 0;
    FILE* fileToRead = NULL;

    /* Read data from file */ 
    printf("FILENAME \n");
    scanf("%s", file);
    fileToRead = fopen(file,"r");
    
    /*Read array*/
    fscanf(fileToRead, "%c %c %c %c %c %c %c %c %c", &dice_input[0], &dice_input[1], &dice_input[2], &dice_input[3], &dice_input[4], &dice_input[5], &dice_input[6], &dice_input[7], &dice_input[8]);
    
    /* Close data file */
    fclose(fileToRead);

    /* Check the dice if statements*/
    if (strcmp(dice_input, dice1) == 0) {
        result = 1;
    }
    else  {
        if (strcmp(dice_input, dice2) == 0 || strcmp(dice_input, dice2_b) == 0) {
            result = 2;
        }
        else {
            if (strcmp(dice_input, dice3) == 0 || strcmp(dice_input, dice3_b) == 0) {
                result = 3;
            }
            else {
                if (strcmp(dice_input, dice4) == 0) {
                    result = 4;
                }
                else {
                    if (strcmp(dice_input, dice5) == 0) {
                        result = 5;
                    }
                    else {
                        if (strcmp(dice_input, dice6) == 0 || strcmp(dice_input, dice6_b) == 0) {
                            result = 6;
                        }
                        else {
                            result = 0;
                        };
                    };
                };
            };
        };
    };

    
    /* Output results */
    printf("OUTPUT \n");
    printf("VALUE: %d ", result);

    return 0;
}
