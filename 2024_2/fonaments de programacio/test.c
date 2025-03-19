#include <stdbool.h>
#include <stdio.h>

int main() {
    char ch;
    bool bo;
    int in1, in2;
    float re;
    FILE* fileToWrite;

    fileToWrite = fopen("file_name.txt", "w");
    ch = 'a';
    bo = true;
    in1 = 2;
    in2 = 3;
    re = 2.0;

    fprintf(fileToWrite, "%c \n", ch);
    fprintf(fileToWrite, "%d \n", bo);
    fprintf(fileToWrite, "%d \t %d \t %d \n", in1, in2, in1 + in2);
    fprintf(fileToWrite, "%f \n", re);

    fclose(fileToWrite);

    return 0;
}