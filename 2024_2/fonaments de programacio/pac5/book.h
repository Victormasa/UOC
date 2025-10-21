#ifndef BOOK_H
#define BOOK_H

#include <stdbool.h>

#define MAX_LENGTH_BOOK_NAME 30

typedef enum {MANUSCRIPT, HARDCOVER, PAPERBACK} tBookBinding;
typedef enum {TRUE, FALSE} tBookSignature;

typedef struct {
    char name[MAX_LENGTH_BOOK_NAME];
    tBookBinding binding;
    tBookSignature signature;
} tBook;

// Reads book data
void readBook(tBook *book);

// Checks if two books have the same name
bool checkBookNames(const tBook *book1, const tBook *book2);

// Compares two books to decide the most valuable
void getMostValuable(const tBook *book1, const tBook *book2, tBook *mostValuable);

// Prints book data
void printBook(const tBook *book);

#endif