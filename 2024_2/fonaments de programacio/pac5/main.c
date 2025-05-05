#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH_BOOK_NAME 30

typedef enum {MANUSCRIPT, HARDCOVER, PAPERBACK} tBookBinding;
typedef enum {TRUE, FALSE} tBookSignature;
typedef struct {
    char name[MAX_LENGTH_BOOK_NAME];
    tBookBinding binding;
    tBookSignature signature;
} tBook;

bool checkBookNames (char book1_title[MAX_LENGTH_BOOK_NAME] , char book2_title[MAX_LENGTH_BOOK_NAME]) {
    if (book1_title == book2_title) {
        return true;
    }
    else {
        return false;
    }

    //opción 2: return (book1_title == book2_title)
}

bool compareBook (int book1_feature, int book2_feature) {
    if (book1_feature == book2_feature){
        return false;
    }
    else {
        if (book1_feature > book2_feature){
            return false;
        }
        else {
            return true;
        }
    }
};
int main() {
    tBook book1;
    tBook book2;

    strcpy(book1.name, "The_Lord_Of_The_Rings");
    book1.signature = 0;
    book1.binding = 1;

    strcpy(book2.name, "The_Lord_Of_The_Rings");
    book2.signature = 1;
    book1.binding = 2;

    printf("%d", checkBookNames(book1.name, book2.name));

}
