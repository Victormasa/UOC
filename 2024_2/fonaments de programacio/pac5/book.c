#include <stdio.h>
#include <string.h>
#include "book.h"

void readBook(tBook *book) {
    printf("TITLE?\n");
    scanf(" %29[^\n]", book->name);
    printf("IS SIGNED (0-FALSE, 1-TRUE)?\n");
    scanf("%d", &book->signature);
    printf("BOOKBINDING (0-MANUSCRIPT, 1-HARDCOVER, 2-PAPERBACK)?\n");
    scanf("%d", &book->binding);
}

bool checkBookNames(const tBook *book1, const tBook *book2) {
    return (strcmp(book1->name, book2->name) == 0);
}

void getMostValuable(const tBook *book1, const tBook *book2, tBook *mostValuable) {
    // Check signatures first (1 > 0). If one book is signed and the other isn’t, the signed one wins
    if (book1->signature > book2->signature) {
        *mostValuable = *book1;
    } else if (book2->signature > book1->signature) {
        *mostValuable = *book2;
    } else {
        // Signatures tied => compare binding
        // 0 (MANUSCRIPT) is more valuable than 1 (HARDCOVER), more valuable than 2 (PAPERBACK)
        if (book1->binding < book2->binding) {
            *mostValuable = *book1;
        } else if (book2->binding < book1->binding) {
            *mostValuable = *book2;
        } else {
            // Same signature and same binding => default to the first book
            *mostValuable = *book1;
        }
    }}

void printBook(const tBook *book) {
    printf("THE MOST VALUABLE BOOK IS:\n");
    printf("TITLE: %s\n", book->name);
    printf("IS SIGNED (0-FALSE, 1-TRUE): %d\n", book->signature);
    printf("BOOKBINDING (0-MANUSCRIPT, 1-HARDCOVER, 2-PAPERBACK): %d\n", book->binding);
}
