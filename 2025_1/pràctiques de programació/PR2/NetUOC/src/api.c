#include <stdio.h>
#include <assert.h>
#include "csv.h"
#include "api.h"
#include <string.h>

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
    // Check preconditions
	assert(data != NULL);
	
	people_init(&(data->people));
	companyList_init(&(data->companies));
	
	/////////////////////////////////
	// PR2_3b
	/////////////////////////////////
  applicationTable_init(&(data->applications));
	/////////////////////////////////
	
	return E_SUCCESS;
    /////////////////////////////////
	// return E_NOT_IMPLEMENTED;
}

// Add a person into the data if it does not exist
tApiError api_addPerson(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR1_3c
	/////////////////////////////////
	tPerson person;
	tApiError error;
	
	// Check preconditions
	assert(data != NULL);
	
	// Check the entry type
    if (strcmp(csv_getType(&entry), "PERSON") != 0)
        return E_INVALID_ENTRY_TYPE;
    
    // Check the number of fields
    if(csv_numFields(entry) != NUM_FIELDS_PERSON)
        return E_INVALID_ENTRY_FORMAT;
	
	// Parse a person
	person_parse(&person, entry);
	
	// Try to add the person or return an error if the person already exists
	error = people_add(&(data->people), person);
	
	// Release the allocated memory
	person_free(&person);
	
	return error;
	/////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Add a company if it does not exist
tApiError api_addCompany(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR1_3d
	/////////////////////////////////
	tCompany company;
	tPerson *founder;
	tApiError error;
	int idx;
	char buffer[FILE_READ_BUFFER_SIZE];
	
	// Check preconditions
	assert(data != NULL);
	
	// Check the entry type
    if (strcmp(csv_getType(&entry), "COMPANY") != 0)
        return E_INVALID_ENTRY_TYPE;
	
    // Check the number of fields
    if(csv_numFields(entry) != NUM_FIELDS_COMPANY)
        return E_INVALID_ENTRY_FORMAT;
	
	// Parse a company
	company_parse(&company, buffer, entry);
	
	// Get the pointer of the founder
	idx = people_find(data->people, buffer);
	if (idx < 0) {
        company_free(&company);
		return E_PERSON_NOT_FOUND;
	}
	founder = &(data->people.elems[idx]);
	
	// Add the company or return an error if the company already exists
	error = companyList_add(&(data->companies), company, founder);
	
	// Release the allocated memory
	company_free(&company);
	
	return error;
	/////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Add a job into the company if it does not exist
tApiError api_addJob(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR1_3e
	/////////////////////////////////
	tCompany *company;
	char buffer[FILE_READ_BUFFER_SIZE];
	tJob job;
	
	// Check preconditions
	assert(data != NULL);
	
	// Check the entry type
    if (strcmp(csv_getType(&entry), "JOB") != 0)
        return E_INVALID_ENTRY_TYPE;
    
    // Check the number of fields
    if(csv_numFields(entry) != NUM_FIELDS_JOB)
        return E_INVALID_ENTRY_FORMAT;
	
	// Parse a job
	job_parse(&job, buffer, entry);
	
	// Find the company
	company = companyList_find(data->companies, buffer);
	
	// If the company does not exists, return an error
	if (company == NULL) {
        job_free(&job);
		return E_COMPANY_NOT_FOUND;
	}
	
	// Assign the pointer to the company
	job.company = company;
	
	// Add the job into the company
	jobs_add(&(company->jobs), job);
	
	// Release the allocated memory
	job_free(&job);
	
	return E_SUCCESS;
	/////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Add an application into the data
tApiError api_addApplication(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR2_3e
	/////////////////////////////////
  	tApplication application;
  	char personDocument[FILE_READ_BUFFER_SIZE];
  	int jobId;
  	int personIdx, applicationIdx;
  	tJob *job = NULL;
  	tCompanyListNode *companyNode;
  	tApiError error;
	tApplication *appPtr;
  	// Check the entry type
  	if (strcmp(csv_getType(&entry), "APPLICATION") != 0) {
  		error = E_INVALID_ENTRY_TYPE;
  	}
  	// Check the number of fields
  	else {
		if (csv_numFields(entry) != NUM_FIELDS_APPLICATION) {
		error = E_INVALID_ENTRY_FORMAT;
		}
		else { 
			// Parse the application
			application_parse(&application, personDocument, &jobId, entry);
			// Search the person
			personIdx = people_find(data->people, personDocument);
			if (personIdx < 0) {
	    	application_free(&application);
	    	error = E_PERSON_NOT_FOUND;
	  		}
	  		else {
				// Search the job in all companies
  				companyNode = data->companies.first;
  				while (companyNode != NULL && job == NULL) {
  				for (int i = 0; i < companyNode->elem.jobs.count; i++) {
  			  	if (companyNode->elem.jobs.elems[i].id == jobId) {
  			    	job = &(companyNode->elem.jobs.elems[i]);
  			    	break;
  			  	}
  				}
  			    	companyNode = companyNode->next;
  				}
				if (job == NULL) {
	      			application_free(&application);
	      			error = E_JOB_NOT_FOUND;
				}
			
	  			else {  
			    	// Set the person and job pointers
			    	application.person = &(data->people.elems[personIdx]);
			    	application.job = job;
					applicationTable_add(&(data->applications), application);
					applicationIdx = applicationTable_find(data->applications, application.id);
				    appPtr = &(data->applications.elems[applicationIdx]);
            		applicationStack_push(&(application.person->applicationsStack), appPtr);
            		applicationQueue_enqueue(&(job->applicationsQueue), appPtr);

            		// Release the temporary application
			    	application_free(&application);
			    	error = E_SUCCESS;
	  			}
			}
		}
	}  
    return error; 
    /////////////////////////////////

}
// Get the number of people registered on the application
int api_peopleCount(tApiData data) {
	/////////////////////////////////
	// PR1_3f
	/////////////////////////////////
	return people_count(data.people);
	/////////////////////////////////
    // return -1;
}

// Get the number of companies registered on the application
int api_companiesCount(tApiData data) {
	/////////////////////////////////
	// PR1_3g
	/////////////////////////////////
	return companyList_len(data.companies);
	/////////////////////////////////
    // return -1;
}

// Get the number of jobs registered on the application
int api_jobsCount(tApiData data) {
	/////////////////////////////////
	// PR1_3h
	/////////////////////////////////
	int nJobs = 0;
	tCompanyListNode *node = data.companies.first;
	
	while (node != NULL) {
		nJobs += node->elem.jobs.count;
		node = node->next;
	}
	
	return nJobs;
	/////////////////////////////////
    // return -1;
}

// Get the number of applications registered on the application
int api_applicationsCount(tApiData data) {
	/////////////////////////////////
	// PR2_3f
	/////////////////////////////////
  return applicationTable_len(data.applications);	
	/////////////////////////////////
}

// Free all used memory
tApiError api_freeData(tApiData* data) {
	/////////////////////////////////
	// PR1_3i
	/////////////////////////////////
	// Check preconditions
	assert(data != NULL);
	
	people_free(&(data->people));
	companyList_free(&(data->companies));
	
	/////////////////////////////////
	// PR2_3b
	/////////////////////////////////
	applicationTable_free(&(data->applications));
	/////////////////////////////////
	
	return E_SUCCESS;
    /////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}

// Add a new entry
tApiError api_addDataEntry(tApiData* data, tCSVEntry entry) {
	/////////////////////////////////
	// PR1_3j
	/////////////////////////////////
	tApiError error;
	
	// Check preconditions
	assert(data != NULL);
	
	// Assign default value to return it if does not match any type
	error = E_INVALID_ENTRY_TYPE;
	
	if (strcmp(csv_getType(&entry), "PERSON") == 0)
		// Add a person
		error = api_addPerson(data, entry);
	else if (strcmp(csv_getType(&entry), "COMPANY") == 0)
		// Add a company
		error = api_addCompany(data, entry);
	else if (strcmp(csv_getType(&entry), "JOB") == 0)
		// Add a job into a company
		error = api_addJob(data, entry);
	/////////////////////////////////
	// PR2_3g
	/////////////////////////////////
	else if (strcmp(csv_getType(&entry), "APPLICATION") == 0)
    // Add an application
    error = api_addApplication(data, entry);
	/////////////////////////////////
	
	return error;
    /////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}

// Get person data
tApiError api_getPerson(tApiData data, const char *document, tCSVEntry *entry) {
	/////////////////////////////////
	// PR1_4a
	/////////////////////////////////
	char buffer[FILE_READ_BUFFER_SIZE];
	tPerson *person = NULL;
	int idx;
	
	// Check preconditions
    assert(entry != NULL);
	
	// Search the person
	idx = people_find(data.people, document);
	
	if (idx < 0)
		return E_PERSON_NOT_FOUND;
	
	person = &(data.people.elems[idx]);
	
	// Print data in the buffer
    person_get(*person, buffer);
	
	// Initialize the ouput structure
	csv_initEntry(entry);
	csv_parseEntry(entry, buffer, "PERSON");
	
	return E_SUCCESS;
	/////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}

// Get company data
tApiError api_getCompany(tApiData data, const char* cif, tCSVEntry *entry) {
	/////////////////////////////////
	// PR1_4b
	/////////////////////////////////
	char buffer[FILE_READ_BUFFER_SIZE];
	tCompany *company;
	
	// Check preconditions
	assert(cif != NULL);
    assert(entry != NULL);
	
	// Search the company
	company = companyList_find(data.companies, cif);
	
	if (company == NULL)
		return E_COMPANY_NOT_FOUND;
	
	company_get(*company, buffer);
	
	// Initialize the output structure
	csv_initEntry(entry);
	csv_parseEntry(entry, buffer, "COMPANY");
	
	return E_SUCCESS;
	/////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}

// Get jobs data
tApiError api_getJobs(tApiData data, tCSVData *jobs) {
	/////////////////////////////////
	// PR1_4c
	/////////////////////////////////
	char buffer[FILE_READ_BUFFER_SIZE];
	tCompanyListNode *pNode = NULL;
	
	// Check preconditions
	assert(jobs != NULL);
	
	// Initialize the output structure
	csv_init(jobs);
	
	// Iterate all companies
	pNode = data.companies.first;
	while (pNode != NULL) {
		// Iterate every job
		for (int i = 0; i < pNode->elem.jobs.count; i++) {
			job_get(pNode->elem.jobs.elems[i], buffer);
			csv_addStrEntry(jobs, buffer, "JOB");
		}
		
		pNode = pNode->next;
	}
	
	return E_SUCCESS;
	/////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}

// Get jobs data by company and salary
tApiError api_getJobsByCompanyAndSalary(tApiData data, tCSVData *jobs, const char *companyCif, int salary) {
	/////////////////////////////////
	// PR1_4d
	/////////////////////////////////
	char buffer[FILE_READ_BUFFER_SIZE];
	tCompany *company;
	tJob *job;
	
	// Check preconditions
	assert(jobs != NULL);
	
	// Initialize the output structure
	csv_init(jobs);
	
	// Find the company
	company = companyList_find(data.companies, companyCif);
	
	// Only add data if the company was found
	if (company != NULL) {
		for (int i = 0; i < company->jobs.count; i++) {
			job = &(company->jobs.elems[i]);
			
			// Only add data if the salary is between the range
			if (salary >= job->minSalary && salary <= job->maxSalary) {
				job_get(*job, buffer);
				csv_addStrEntry(jobs, buffer, "JOB");
			}
		}
	}
	
	return E_SUCCESS;
	/////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}


// Recursivitat interna per recórrer la pila en ordre invers
void rec(tApplicationStackNode *node, tCSVData *applications) {
	if (node == NULL) return;
	rec(node->next, applications);
	char buffer[FILE_READ_BUFFER_SIZE];
	application_get(*(node->elem), buffer);
	csv_addStrEntry(applications, buffer, "APPLICATION");
}

// Reverse a person's application stack
tApiError api_reversePersonApplicationStack(tApiData data, tCSVData *applications, const char *document) {
    //////////////////////////////////
    // PR2_4a
    //////////////////////////////////
    int idx;
    tPerson *person;

    // Comprova precondicions
    assert(applications != NULL);
    assert(document != NULL);

    // Busca la persona
    idx = people_find(data.people, document);
    if (idx < 0) {
        return E_PERSON_NOT_FOUND;
    }
    person = &(data.people.elems[idx]);

    // Inicialitza la sortida
    csv_init(applications);
    rec(person->applicationsStack.first, applications);

    return E_SUCCESS;
}

// Reverse a job's application queue
tApiError api_reverseJobApplicationQueue(tApiData data, tCSVData *applications, int id) {
    //////////////////////////////////
    // PR2_4b
    //////////////////////////////////
    tJob *job = NULL;
    tCompanyListNode *companyNode;
    int found = 0;

    // Comprova precondicions
    assert(applications != NULL);

    // Busca el job per id a totes les companyies
    companyNode = data.companies.first;
    while (companyNode != NULL && !found) {
        for (int i = 0; i < companyNode->elem.jobs.count; i++) {
            if (companyNode->elem.jobs.elems[i].id == id) {
                job = &(companyNode->elem.jobs.elems[i]);
                found = 1;
                break;
            }
        }
        companyNode = companyNode->next;
    }

    // Si no troba el job, retorna error
    if (job == NULL) {
        return E_JOB_NOT_FOUND;
    }

    // Inicialitza la sortida
    csv_init(applications);
    rec(job->applicationsQueue.first, applications);

    return E_SUCCESS;
}