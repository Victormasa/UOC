#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "job.h"

//////////////////////////////////
// Available methods
//////////////////////////////////


// Parse a tDate from string information
void date_parse(tDate* date, const char* s_date) {
    // Check output data
    assert(date != NULL);

    // Check input date
    assert(s_date != NULL);
    assert(strlen(s_date) == 10);

    // Parse the input date
    sscanf(s_date, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Copy the data from the source to destination
void date_cpy(tDate* destination, tDate source) {
    destination->day = source.day;
    destination->month = source.month;
    destination->year = source.year;
}

// Compare two dates. Returns -1 if date1<date2, 0 if date1=date2 and 1 if date1>date2
int date_cmp(tDate date1, tDate date2) {
    int result;

    // Checkl year
    if (date1.year < date2.year) {
        result = -1;
    }
    else if (date1.year > date2.year) {
        result = 1;
    }
    // Check month
    else if (date1.month < date2.month) {
        result = -1;
    }
    else if (date1.month > date2.month) {
        result = 1;
    }
    // Check day
    else if (date1.day < date2.day) {
        result = -1;
    }
    else if (date1.day > date2.day) {
        result = 1;
    }
    else {
        result = 0;
    }

    return result;
}

// Copy the data from the source to destination
void person_cpy(tPerson* destination, tPerson source) {
    // Copy identity document data
    strncpy(destination->document, source.document, MAX_DOCUMENT + 1);

    // Copy name data
    strncpy(destination->name, source.name, MAX_CHARS + 1);

    // Copy surname data
    strncpy(destination->surname, source.surname, MAX_CHARS + 1);

    // Copy phone data
    strncpy(destination->phone, source.phone, MAX_PHONE + 1);

    // Copy email data
    strncpy(destination->email, source.email, MAX_CHARS + 1);

    // Copy address data
    strncpy(destination->address, source.address, MAX_CHARS + 1);

    // Copy cp data
    strncpy(destination->cp, source.cp, MAX_CP + 1);

    // Copy the birthday date
    date_cpy(&(destination->birthday), source.birthday);
}

// Get person data using a string
void person_get(tPerson data, char* buffer)
{
    // Print all data at same time
    sprintf(buffer,"%s;%s;%s;%s;%s;%s;%s;%02d/%02d/%04d",
        data.document,
        data.name,
        data.surname,
        data.phone,
        data.email,
        data.address,
        data.cp,
        data.birthday.day, data.birthday.month, data.birthday.year);
}

// Initialize the people data
void people_init(tPeople* data) {
    // Check input/output data
    assert(data != NULL);

    data->count = 0;
}

// Get person data of position index using a string
void people_get(tPeople data, int index, char* buffer)
{
    assert(index >= 0 && index < data.count);
    person_get(data.elems[index], buffer);
}

// Return the position of a person with provided document. -1 if it does not exist
int people_find(tPeople data, const char* document) {
    bool found = false;
    int result = -1;
    int i = 0;
    while (i < data.count && !found) {
        if (strcmp(data.elems[i].document, document) == 0) {
            result = i;
        }
        i++;
    }

    return result;
}

// Print people data
void people_print(tPeople data) {
    char buffer[BUFFER_SIZE];
    int i;
    for (i = 0; i < data.count; i++) {
        people_get(data, i, buffer);
        printf("%s\n", buffer);
    }
}

// Print jobs data
void jobs_print(tJobs data) {
    char buffer[BUFFER_SIZE];
    int i;
    for (i = 0; i < data.count; i++) {
        jobs_get(data, i, buffer);
        printf("%s\n", buffer);
    }
}

//////////////////////////////////////
// EX2: Implement your methods here....
//////////////////////////////////////

// Parse input from CSVEntry
void person_parse(tPerson* data, tCSVEntry entry) {
    // Check input data
    assert(data != NULL);

    // Check entry fields
    assert(csv_numFields(entry) == 8);

    int pos = 0; // Allow to easy incremental position of the income data

    // Copy identity document data
    assert(strlen(entry.fields[pos]) == MAX_DOCUMENT);
    csv_getAsString(entry, pos, data->document, MAX_DOCUMENT + 1);

    // Copy name data
    csv_getAsString(entry, ++pos, data->name, MAX_CHARS + 1);

    // Copy surname data
    csv_getAsString(entry, ++pos, data->surname, MAX_CHARS + 1);

    // Copy phone data
    csv_getAsString(entry, ++pos, data->phone, MAX_PHONE + 1);

    // Copy email data
    csv_getAsString(entry, ++pos, data->email, MAX_CHARS + 1);

    // Copy address data
    csv_getAsString(entry, ++pos, data->address, MAX_CHARS + 1);

    // Copy cp data
    assert(strlen(entry.fields[++pos]) == MAX_CP);
    csv_getAsString(entry, pos, data->cp, MAX_CP + 1);

    // Parse the birthday date
    assert(strlen(entry.fields[++pos]) == MAX_DATE);
    date_parse(&(data->birthday), entry.fields[pos]);
}

// Add a new person to people data
void people_add(tPeople* data, tPerson person) {
    // Check input data
    assert(data != NULL);

    // If person does not exist add it
    if (people_find(*data, person.document) < 0) {
        // Copy the data to the new position if there is space
        assert(data->count < MAX_PEOPLE);
        person_cpy(&(data->elems[data->count]), person);

        // Increase the number of elements
        data->count++;
    }
}

// Parse input from CSVEntry
void job_parse(tJob* data, tCSVEntry entry) {
    // Check input data
    assert(data != NULL);

    // Check entry fields
    assert(csv_numFields(entry) == 8);

    int pos = 0; // Allow to easy incremental position of the income data

    // Copy job's id data
    data->id = csv_getAsInteger(entry, pos);

    // Copy role and company data
    csv_getAsString(entry, ++pos, data->role, MAX_CHARS + 1);
    csv_getAsString(entry, ++pos, data->company, MAX_CHARS + 1);

    // Copy number of positions data
    data->nPos = csv_getAsInteger(entry, ++pos);

    // Parse start date
    assert(strlen(entry.fields[++pos]) == MAX_DATE);
    date_parse(&(data->startDate), entry.fields[pos]);

    // Parse end date
    assert(strlen(entry.fields[++pos]) == MAX_DATE);
    date_parse(&(data->endDate), entry.fields[pos]);

    // Copy salary data
    data->minSalary = csv_getAsInteger(entry, ++pos);
    data->maxSalary = csv_getAsInteger(entry, ++pos);
}

// Copy the data from the source to destination (individual data)
void job_cpy(tJob* destination, tJob source) {
    // Copy job's id data
    destination->id = source.id;

    // Copy role and company data
    strncpy(destination->role, source.role, MAX_CHARS + 1);
    strncpy(destination->company, source.company, MAX_CHARS + 1);

    // Copy number of positions data
    destination->nPos = source.nPos;

    // Copy start/end date
    date_cpy(&(destination->startDate), source.startDate);
    date_cpy(&(destination->endDate), source.endDate);

    // Copy salary data
    destination->minSalary = source.minSalary;
    destination->maxSalary = source.maxSalary;
}

// Get job data using a string
void job_get(tJob data, char* buffer)
{
    // Print all data at same time
    sprintf(buffer,"%d;%s;%s;%d;%02d/%02d/%04d;%02d/%02d/%04d;%d;%d",
        data.id,
        data.role,
        data.company,
        data.nPos,
        data.startDate.day, data.startDate.month, data.startDate.year,
        data.endDate.day, data.endDate.month, data.endDate.year,
        data.minSalary,
        data.maxSalary);
}

// Initialize jobs data
void jobs_init(tJobs* data) {
    // Check input data
    assert(data != NULL);
	// Ex 2
    data->count = 0;
    data->elems = NULL;
}

// Add a new job
void jobs_add(tJobs* data, tJob job) {
    // Check input data
    assert(data != NULL);
    assert(job.id >= 1);
    assert(job.nPos >= 1);
    assert(date_cmp(job.startDate, job.endDate) == -1);
    assert(job.minSalary <= job.maxSalary || job.minSalary == EMPTY_SALARY || job.maxSalary == EMPTY_SALARY );

    tJob *temp; // Temporary pointer to reallocate memory

    // Check that salary is legal or not informed. It is not a precondition, we could receive this data
    // It is recommended to check first salary, find if exists could need more computational time
    if ((job.minSalary == EMPTY_SALARY || job.minSalary >= LEGAL_MIN_SALARY) &&
        (job.maxSalary == EMPTY_SALARY || job.maxSalary >= LEGAL_MIN_SALARY)) {
        // If job does not exist add it
        if (jobs_find(*data, job.id) < 0) {
            // Copy the data to the new position
			// Ex 2
            tJob* temp = (tJob*)realloc(data->elems, (data->count + 1) * sizeof(tJob));
            
            // Check if reallocation was successful
            if (temp != NULL) {
                data->elems = temp;
                
                // Copy the job data to the new position
                job_cpy(&(data->elems[data->count]), job);
                
                // Increase the number of elements
                data->count++;
            }
        }
    }
}

// Get job data of position index using a string
void jobs_get(tJobs data, int index, char* buffer)
{
    assert(index >= 0 && index < data.count);
    job_get(data.elems[index], buffer);
}

// Returns the position of a job looking for id's job. -1 if it does not exist
int jobs_find(tJobs data, int id) {
    // An alternative solution compared to people_find
    int i = 0;
    int result = -1;
    while (i < data.count && result == -1) {
        if (data.elems[i].id == id) {
            result = i;
        }
        i++;
    }

    return result;
}

// Remove a job
void jobs_del(tJobs* data, int id) {
    int job_found = 0;

    job_found = jobs_find(*data, id);

    if (job_found != -1) {
        // Shift elements to the left to overwrite the deleted job
        for (int i = job_found; i < data->count - 1; i++) {
            job_cpy(&(data->elems[i]), data->elems[i + 1]);
        }

        // Decrease the count of jobs
        data->count--;

        // Reallocate memory to shrink the array
        tJob* temp = (tJob*)realloc(data->elems, data->count * sizeof(tJob));
        if (temp != NULL || data->count == 0) { // Allow NULL if count is 0
            data->elems = temp;
        }

    }
}

// Remove all elements 
void jobs_free(tJobs* data) { 
    // Free the dynamically allocated memory for job elements
    free(data->elems);
    data->elems = NULL;
    data->count = 0;
}
