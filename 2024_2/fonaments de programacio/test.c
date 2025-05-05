#include <stdio.h>
#define NUMBER 10

void fill(int table[]) { 
    int i;

    *table = 5;

    for (i = 0; i< NUMBER; i++){
        table[i] ++;
    }
} 


int main() { 
    /* Variable definition */ 
    int i;
    int data[NUMBER];

    for (i = 0; i < NUMBER; i++){
        data[i] = 3;
    }

    fill(data);

    for (i =0 ; i < NUMBER; i++){
        printf("%d ", data[i]);
    }

    return 0;
}