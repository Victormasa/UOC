#ifndef __JOB_H__
#define __JOB_H__
#include "csv.h"

#define BUFFER_SIZE 2048
#define MAX_DOCUMENT 9
#define MAX_CHARS 250
#define MAX_PHONE 15
#define MAX_CP 5
#define MAX_DATE 10
#define MAX_PEOPLE 100
// Ex1 and ex2 remove MAX_JOBS in PEC2 as they should not be used
#define MAX_JOBS 125
#define LEGAL_MIN_SALARY 16576
#define EMPTY_SALARY -1

typedef struct _tDate {
    int day;
    int month;
    int year;
} tDate;

typedef struct _tPerson {
    char document[MAX_DOCUMENT + 1];
    char name[MAX_CHARS + 1];
    char surname[MAX_CHARS + 1];
    char phone[MAX_PHONE + 1];;
    char email[MAX_CHARS + 1];;
    char address[MAX_CHARS + 1];;
    char cp[MAX_CP + 1];;
    tDate birthday;
} tPerson;

typedef struct _tPeople {
    tPerson elems[MAX_PEOPLE];
    int count;
} tPeople;

// Ex 1: Define data types here...

typedef struct _tJob {
    int id;
    char role[MAX_CHARS + 1]; // +1 to store NULL at the end of string
    char company[MAX_CHARS + 1];
    int nPos;
    tDate startDate;
    tDate endDate;
    int minSalary;
    int maxSalary;
} tJob;


// Ex 1 and 2: dynamic memory for jobs
typedef struct _tJobs {
    tJob* elems;    // pointer to dynamically allocated array
    int count;      // number of used elements
} tJobs;

//////////////////////////////////
// Available methods
//////////////////////////////////

// Parse a tDate from string information
void date_parse(tDate* date, const char* s_date);

// Copy the data from the source to destination
void date_cpy(tDate* destination, tDate source);

// Compare two dates. Returns -1 if date1<date2, 0 if date1=date2 and 1 if date1>date2
int date_cmp(tDate date1, tDate date2);

// Copy the data from the source to destination
void person_cpy(tPerson* destination, tPerson source);

// Get person data using a string
void person_get(tPerson data, char* buffer);

// Initialize people data
void people_init(tPeople* data);

// Get person data of position index using a string
void people_get(tPeople data, int index, char* buffer);

// Return the position of a person with provided document. -1 if it does not exist
int people_find(tPeople data, const char* document);

// Print people data
void people_print(tPeople data);

// Print jobs data
void jobs_print(tJobs data);

/////////////////////////////////////
// Ex 2: Requested methods ....
/////////////////////////////////////

// Parse input from CSVEntry
void person_parse(tPerson* data, tCSVEntry entry);

// Add a new person to people data
void people_add(tPeople* data, tPerson person);

// Parse input from CSVEntry
void job_parse(tJob* data, tCSVEntry entry);

// Copy the data from the source to destination (individual data)
void job_cpy(tJob* destination, tJob source);

// Get job data using a string
void job_get(tJob data, char* buffer);

// Initialize jobs data
void jobs_init(tJobs* data);

// Add a new job
void jobs_add(tJobs* data, tJob job);

// Get job data of position index using a string
void jobs_get(tJobs data, int index, char* buffer);

// Returns the position of a job looking for id's job. -1 if it does not exist
int jobs_find(tJobs data, int id);

// Remove a job (ex2 new method to implement)
void jobs_del(tJobs* data, int id);

// Remove all elements (ex2 new method to implement)
void jobs_free(tJobs* data);

////////////////////////////////////////////

#endif
