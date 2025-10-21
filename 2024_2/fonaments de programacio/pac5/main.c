/*
* File: main.c
* Author: Victor Martinez Santos
* Course: 20242
* Description: PAC5-PEC5-CAA5
*/

#include <stdio.h>
#include <stdbool.h>
#include "book.h"


int main() {
    tBook book1;
    tBook book2;
    tBook bestBook;
    bool haveSameName;

    readBook(&book1);
    readBook(&book2);

    haveSameName = checkBookNames(&book1, &book2);
    if (haveSameName) {
        getMostValuable(&book1, &book2, &bestBook);
        printBook(&bestBook);
    } else {
        printf("NON-COMPARABLE BOOKS\n");
    }

    return 0;
}