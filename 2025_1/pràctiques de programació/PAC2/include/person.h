#ifndef __PERSON_H__
#define __PERSON_H__
#include "csv.h"

typedef struct _tDate {
    int day;
    int month;
    int year;
} tDate;

typedef struct _tPerson {
    char* document;
    char* name;
    char* surname;
    char* phone;
    char* email;
    char* address;
    char* cp;
    tDate birthday;
} tPerson;

typedef struct _tPeople {
    tPerson* elems;
    int count;
} tPeople;


// Initialize the people data
void people_init(tPeople* data);

// Remove the data from a person
void person_free(tPerson* data);

// Remove the data from all persons
void people_free(tPeople* data);

// Parse input from CSVEntry
void person_parse(tPerson* data, tCSVEntry entry);

// Add a new person
void people_add(tPeople* data, tPerson person);

// Remove a person
void people_del(tPeople* data, const char *document);

// Return the position of a person with provided document. -1 if it does not exist
int people_find(tPeople data, const char* document);

// Print the person data
void people_print(tPeople data);

// Copy the data from the source to destination
void person_cpy(tPerson* destination, tPerson source);

#endif
