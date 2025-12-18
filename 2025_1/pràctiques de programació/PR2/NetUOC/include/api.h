#ifndef __UOCPLAY_API__H
#define __UOCPLAY_API__H
#include <stdbool.h>
#include "error.h"
#include "csv.h"
#include "person.h"
#include "company.h"

#define FILE_READ_BUFFER_SIZE 2048

// Type that stores all the application data
typedef struct _ApiData {
    /////////////////////////////////
	// PR1_3a
	/////////////////////////////////
    // People
    tPeople people;	
	// Companies
    tCompanyList companies;
	/////////////////////////////////
	
	/////////////////////////////////
	// PR2_3a
	/////////////////////////////////
	tApplicationTable applications;
    /////////////////////////////////
} tApiData;

// Get the API version information
const char* api_version();

// Load data from a CSV file. If reset is true, remove previous data
tApiError api_loadData(tApiData* data, const char* filename, bool reset);

// Initialize the data structure
tApiError api_initData(tApiData* data);

// Add a person into the data if it does not exist
tApiError api_addPerson(tApiData* data, tCSVEntry entry);

// Add a company if it does not exist
tApiError api_addCompany(tApiData* data, tCSVEntry entry);

// Add a job into the company if it does not exist
tApiError api_addJob(tApiData* data, tCSVEntry entry);

// Add an application into the data
tApiError api_addApplication(tApiData* data, tCSVEntry entry);

// Get the number of people registered on the application
int api_peopleCount(tApiData data);

// Get the number of companies registered on the application
int api_companiesCount(tApiData data);

// Get the number of jobs registered on the application
int api_jobsCount(tApiData data);

// Get the number of applications registered on the application
int api_applicationsCount(tApiData data);

// Free all used memory
tApiError api_freeData(tApiData* data);

// Add a new entry
tApiError api_addDataEntry(tApiData* data, tCSVEntry entry);

// Get person data
tApiError api_getPerson(tApiData data, const char *document, tCSVEntry *entry);

// Get company data
tApiError api_getCompany(tApiData data, const char* cif, tCSVEntry *entry);

// Get jobs data
tApiError api_getJobs(tApiData data, tCSVData *jobs);

// Get jobs data by company and salary
tApiError api_getJobsByCompanyAndSalary(tApiData data, tCSVData *jobs, const char *companyCif, int salary);

// Reverse a person's application stack
tApiError api_reversePersonApplicationStack(tApiData data, tCSVData *applications, const char *document);

// Auxiliary function for api_reversePersonApplicationStack
void api_reversePersonApplicationStack_rec(tApplicationStack *stack, tCSVData *applications);

// Reverse a job's application queue
tApiError api_reverseJobApplicationQueue(tApiData data, tCSVData *applications, int id);

// Auxiliary function for api_reverseJobApplicationQueue
void api_reverseJobApplicationQueue_rec(tApplicationQueue *queue, tCSVData *applications, tApplication *head);

#endif
