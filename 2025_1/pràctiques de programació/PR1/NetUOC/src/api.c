#include <stdio.h>
#include <assert.h>
#include "csv.h"
#include "api.h"
#include "company.h"
#include "error.h"
#include <string.h>
#include <stdlib.h>

// Get the API version information
const char* api_version()
{
    return "UOC PP 20251";
}

// Load data from a CSV file. If reset is true, remove previous data
tApiError api_loadData(tApiData* data, const char* filename, bool reset)
{
    tApiError error;
    FILE *fin;    
    char buffer[FILE_READ_BUFFER_SIZE];
    tCSVEntry entry;
    
    // Check input data
    assert( data != NULL );
    assert(filename != NULL);
    
    // Reset current data    
    if (reset) {
        // Remove previous information
        error = api_freeData(data);
        if (error != E_SUCCESS) {
            return error;
        }
        
        // Initialize the data
        error = api_initData(data);
        if (error != E_SUCCESS) {
            return error;
        }
    }

    // Open the input file
    fin = fopen(filename, "r");
    if (fin == NULL) {
        return E_FILE_NOT_FOUND;
    }
    
    // Read file line by line
    while (fgets(buffer, FILE_READ_BUFFER_SIZE, fin)) {
        // Remove new line character     
        buffer[strcspn(buffer, "\n\r")] = '\0';
        
        csv_initEntry(&entry);
        csv_parseEntry(&entry, buffer, NULL);
        // Add this new entry to the api Data
        error = api_addDataEntry(data, entry);
        if (error != E_SUCCESS) {
			csv_freeEntry(&entry);
			fclose(fin);
            return error;
        }
        csv_freeEntry(&entry);

    }
    
    fclose(fin);
    
    return E_SUCCESS;
}

// Initialize the data structure
tApiError api_initData(tApiData* data) {
	/////////////////////////////////
	// PR1_3b
	/////////////////////////////////
  
  assert(data != NULL);

  // Allocate memory for people and companies
  data->people = (tPeople*) malloc(sizeof(tPeople));
  data->companies = (tCompanyList*) malloc(sizeof(tCompanyList)); 
  data->jobs = (tJobs*) malloc (sizeof(tJobs)); 

  // Initialize people and companies
  people_init(data->people);
  companyList_init(data->companies);
  jobs_init(data->jobs);

  return E_SUCCESS;
}

// Add a person into the data if it does not exist
tApiError api_addPerson(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR1_3c
	/////////////////////////////////
  
  tApiError status;
  char document[10];
  int fieldsCount;
  int peopleExist;
  tPerson person;
  
  if (strcmp(csv_getType(&entry),"PERSON") != 0) {
    status = E_INVALID_ENTRY_TYPE;
  }
  else {
    fieldsCount = csv_numFields(entry);
    if (fieldsCount != MAX_CSV_FIELDS) {
      status = E_INVALID_ENTRY_FORMAT;
    }
    else {
      csv_getAsString(entry , 0, document, 10);
      peopleExist = people_find(*(data->people), document);
      if (peopleExist != -1) {
        status = E_PERSON_DUPLICATED;
      }
      else {
        person_parse(&person, entry);
        people_add(data->people,person);
        status = E_SUCCESS;
      }
    }
  }

  return status;
}

// Add a company if it does not exist
tApiError api_addCompany(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR1_3d
	/////////////////////////////////
  
  tApiError status;
  char cif[10];
  char document[10];
  int fieldsCount;
  tCompany* companyExist;
  tCompany company;
  int personExist;
  tPerson* personFound;


  fieldsCount = csv_numFields(entry);
  
  if (strcmp(csv_getType(&entry),"COMPANY") != 0) {
    status = E_INVALID_ENTRY_TYPE;
  }
  else if (fieldsCount != NUM_FIELDS_COMPANY) {
    status = E_INVALID_ENTRY_FORMAT;
  }
  else {
    csv_getAsString(entry , 0, cif, 10);
    companyExist = companyList_find(*(data->companies), cif);
    csv_getAsString(entry , 6, document, 10);
    personExist = people_find(*(data->people), document);
    if (companyExist != NULL) {
      status = E_COMPANY_DUPLICATED;
    }
    else if (personExist == -1) {
      status = E_PERSON_NOT_FOUND;
    }
    else {
      for (int person = 0; person < data->people->count; person++) {
        if (strcmp(data->people->elems[person].document, document) == 0) {
            personFound = &data->people->elems[person];
        }
      }
      company_parse(&company, document, entry);
      companyList_add(data->companies,company, personFound);
      status = E_SUCCESS;
    }
  }
  return status;
}
// Add a job into the company if it does not exist
tApiError api_addJob(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR1_3e
	/////////////////////////////////
  
  tApiError status;
  char cif[10];
  int fieldsCount;
  tCompany* companyExist;
  tJob job;

  fieldsCount = csv_numFields(entry);
  if (strcmp(csv_getType(&entry),"JOB") != 0) {
    status = E_INVALID_ENTRY_TYPE;
  }
  else if (fieldsCount != NUM_FIELDS_JOB) {
      status = E_INVALID_ENTRY_FORMAT;
  }
  else {
    csv_getAsString(entry , 7, cif, 10);
    companyExist = companyList_find(*(data->companies), cif);
    if (companyExist == NULL) {
      status = E_COMPANY_NOT_FOUND;
    }
    else {
      job_parse(&job, companyExist->info.cif, entry);
      job.company = companyExist;
      jobs_add(data->jobs, job);

      status = E_SUCCESS;
    }
  }
  return status;
}

// Get the number of people registered on the application
int api_peopleCount(tApiData data) {
	/////////////////////////////////
	// PR1_3f
  return data.people->count;  
}

// Get the number of companies registered on the application
int api_companiesCount(tApiData data) {
	/////////////////////////////////
	// PR1_3g
	/////////////////////////////////
    return data.companies->size;
}

// Get the number of jobs registered on the application
int api_jobsCount(tApiData data) {
	/////////////////////////////////
  // PR1_3h
	/////////////////////////////////
  return data.jobs->count;
}

// Free all used memory
tApiError api_freeData(tApiData* data) {
	/////////////////////////////////
	// PR1_3i
	/////////////////////////////////
	
  companyList_free(data->companies);
  people_free(data->people);
  jobs_free(data->jobs);
  // Check and free pointers
  free(data->companies);
  free(data->people);
  free(data->jobs);
  data->companies = NULL;
  data->people = NULL;
  data->jobs = NULL;
  
  return E_SUCCESS;
}

// Add a new entry
tApiError api_addDataEntry(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR1_3j
	/////////////////////////////////
  
  tApiError status;

  if (strcmp(csv_getType(&entry),"PERSON") == 0) {
    status = api_addPerson(data, entry);
  }
  else if (strcmp(csv_getType(&entry),"COMPANY") == 0) {
    status = api_addCompany(data, entry);
  }
  else if (strcmp(csv_getType(&entry),"JOB") == 0) {
    status = api_addJob(data, entry);
  }
  else {
    status = E_INVALID_ENTRY_TYPE;
  }
  
  return status;
}

// Get person data
tApiError api_getPerson(tApiData data, const char *document, tCSVEntry *entry) {
	/////////////////////////////////
	// PR1_4a
	/////////////////////////////////
  
  tApiError status;
  int personFound;
  char person[FILE_READ_BUFFER_SIZE];

  personFound = people_find(*(data.people), document);
  if (personFound == -1) { 
    status = E_PERSON_NOT_FOUND;
  }
  else {
    sprintf(person, "%s;%s;%s;%s;%s;%s;%s;%02d/%02d/%04d", data.people->elems[personFound].document, data.people->elems[personFound].name, data.people->elems[personFound].surname, data.people->elems[personFound].phone, data.people->elems[personFound].email, data.people->elems[personFound].address, data.people->elems[personFound].cp, data.people->elems[personFound].birthday.day, data.people->elems[personFound].birthday.month, data.people->elems[personFound].birthday.year);

    csv_parseEntry(entry, person, "PERSON");
    status = E_SUCCESS;
  }

  return status;
}

// Get company data
tApiError api_getCompany(tApiData data, const char* cif, tCSVEntry *entry) {
	/////////////////////////////////
	// PR1_4b
	/////////////////////////////////
	
  tApiError status;
  tCompany* companyFound;
  char company[FILE_READ_BUFFER_SIZE];

  companyFound = companyList_find(*(data.companies), cif);
  if (companyFound == NULL) { 
    status = E_COMPANY_NOT_FOUND;
  }
  else {
    sprintf(company, "%s;%s;%02d/%02d/%04d;%d;%d;%d;%s", companyFound->info.cif, companyFound->info.name, companyFound->info.foundation.day, companyFound->info.foundation.month, companyFound->info.foundation.year, companyFound->info.minSize, companyFound->info.maxSize, companyFound->info.hasAIEnabled, companyFound->founder->document);

    csv_parseEntry(entry, company, "COMPANY");
    status = E_SUCCESS;
  }
  return status;
}

// Get jobs data
tApiError api_getJobs(tApiData data, tCSVData *jobs) {
	/////////////////////////////////
	// PR1_4c
	/////////////////////////////////
	
  tApiError status;
  tCompany* companyFound;
  tCSVEntry jobEntry;
  char job[FILE_READ_BUFFER_SIZE];
  
  for (int jobList = 0; jobList < data.jobs->count; jobList++) {
    companyFound = companyList_find(*(data.companies), data.jobs->elems[jobList].company->info.cif);
    sprintf(job, "%d;%s;%d;%02d/%02d/%04d;%02d/%02d/%04d;%d;%d;%s", data.jobs->elems[jobList].id, data.jobs->elems[jobList].role, data.jobs->elems[jobList].nPos, data.jobs->elems[jobList].startDate.day, data.jobs->elems[jobList].startDate.month, data.jobs->elems[jobList].startDate.year, data.jobs->elems[jobList].endDate.day, data.jobs->elems[jobList].endDate.month, data.jobs->elems[jobList].endDate.year, data.jobs->elems[jobList].minSalary, data.jobs->elems[jobList].maxSalary, companyFound->info.cif);
    
    csv_addStrEntry(jobs, job, "JOB");
  } 

  status = E_SUCCESS;

  return status;
}

// Get jobs data by company and salary
tApiError api_getJobsByCompanyAndSalary(tApiData data, tCSVData *jobs, const char *companyCif, int salary) {
	/////////////////////////////////
	// PR1_4d
	/////////////////////////////////
	
  for (int i = 0; i < data.jobs->count; i++) {
    if (strcmp(data.jobs->elems[i].company->info.cif, companyCif) == 0 &&
        data.jobs->elems[i].minSalary <= salary && 
        data.jobs->elems[i].maxSalary >= salary) {
        
        char job[FILE_READ_BUFFER_SIZE];
        sprintf(job, "%d;%s;%d;%02d/%02d/%04d;%02d/%02d/%04d;%d;%d;%s", data.jobs->elems[i].id, data.jobs->elems[i].role, data.jobs->elems[i].nPos, data.jobs->elems[i].startDate.day, data.jobs->elems[i].startDate.month, data.jobs->elems[i].startDate.year, data.jobs->elems[i].endDate.day, data.jobs->elems[i].endDate.month, data.jobs->elems[i].endDate.year, data.jobs->elems[i].minSalary, data.jobs->elems[i].maxSalary, data.jobs->elems[i].company->info.cif);
        
        csv_addStrEntry(jobs, job, "JOB");
    }
  }

  return E_SUCCESS;
}
