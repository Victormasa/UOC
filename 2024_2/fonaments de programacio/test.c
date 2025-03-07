#include <stdio.h>
#include <stdbool.h>

int main() {
    char character;
    bool isAlphabetical;

    printf("Enter a character: ");
    scanf("%c", &character);

    isAlphabetical = (
    ('a' <= character && character <= 'z' ) ||
    ('A' <= character && character <= 'Z') 
    );

    printf("Is the character %c alphabetical? (0=false, 1=true) : %d \n", character, isAlphabetical);

    return 0;
}