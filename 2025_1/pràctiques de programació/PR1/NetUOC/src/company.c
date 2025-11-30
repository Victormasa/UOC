#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "company.h"
#include "csv.h"
#include "error.h"

//////////////////////////////////
// Company info functions
//////////////////////////////////

// Initialize a company info
void companyInfo_init(tCompanyInfo *info, const char *cif, const char *name, tDate foundation, int minSize, int maxSize, bool hasAIEnabled) {
	// Check input data
	assert(info != NULL);
	assert(cif != NULL);
	assert(name != NULL);
	assert(minSize > 0);
	assert(maxSize >= minSize);
	
	// CIF
	info->cif = (char*)malloc(sizeof(char) * (strlen(cif) + 1));
	assert(info->cif != NULL);
	strcpy(info->cif, cif);
	
	// Name
	info->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	assert(info->name != NULL);
	strcpy(info->name, name);
	
	// Foundation
	date_cpy(&(info->foundation), foundation);
	
	// Size of the company
	info->minSize = minSize;
	info->maxSize = maxSize;
	
	// Has AI enabled
	info->hasAIEnabled = hasAIEnabled;
}

// Release the company info
void companyInfo_free(tCompanyInfo *info) {
	// Check input data
	assert(info != NULL);
	
	if (info->cif != NULL) {
		free(info->cif);
		info->cif = NULL;
	}

	if (info->name != NULL) {
		free(info->name);
		info->name = NULL;
	}
}

//////////////////////////////////
// Company functions
//////////////////////////////////

// Parse input from CSVEntry
void company_parse(tCompany *data, char *founderDocument, tCSVEntry entry) {
	// Check input data
	assert(data != NULL);
	
	// Check entry fields
    assert(csv_numFields(entry) == NUM_FIELDS_COMPANY);
	
	int pos = 0;

    // CIF
    const char *cif = entry.fields[pos++];

    // Name
    const char *name = entry.fields[pos++];

    // Foundation date
    assert(strlen(entry.fields[pos]) == DATE_LENGTH);
    tDate foundation;
    date_parse(&foundation, entry.fields[pos++]);

    // minSize
    int minSize = csv_getAsInteger(entry, pos++);

    // maxSize
    int maxSize = csv_getAsInteger(entry, pos++);

    // hasAIEnabled
    bool hasAIEnabled = csv_getAsInteger(entry, pos++) == 1;

    // Initialize its info
    companyInfo_init(&(data->info), cif, name, foundation, minSize, maxSize, hasAIEnabled);

    // Initialize the founder
    data->founder = NULL;
	
	// Initialize the jobs
	jobs_init(&(data->jobs));

    // Copy the founder document
    strcpy(founderDocument, entry.fields[pos++]);
}

// Get company data using a string
void company_get(tCompany data, char* buffer) {
	// Print all data at same time
	sprintf(buffer, "%s;%s;%02d/%02d/%04d;%d;%d;%d;%s",
		data.info.cif,
		data.info.name,
		data.info.foundation.day, data.info.foundation.month, data.info.foundation.year,
		data.info.minSize,
		data.info.maxSize,
		data.info.hasAIEnabled,
		data.founder->document
	);
}

// Release all the allocated memory
void company_free(tCompany *data) {
	// Check preconditions
	assert(data != NULL);
	
	// Release the allocated memory from company info
	companyInfo_free(&(data->info));
    
    // Release the allocated memory from jobs
    jobs_free(&(data->jobs));
}

//////////////////////////////////
// Company list functions
//////////////////////////////////

// Initialize a list of companies
tApiError companyList_init(tCompanyList *list) {
	/////////////////////////////////
	// PR1_2a
	/////////////////////////////////
  //Initialize the first and last pointers to NULL
  
  list->first = NULL;	
  list->last = NULL;
  list->size = 0;

	return E_SUCCESS;
}

// Return the number of companies of the list
int companyList_len(tCompanyList list) {
	/////////////////////////////////
	// PR1_2b
	/////////////////////////////////
  // Assign a counter and traverse the list to count the nodes
  int count = 0;
  tCompanyListNode* current = list.first;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  /// Return the count
	return count;
}

// Search a company by cif
tCompany* companyList_find(tCompanyList list, const char *cif) {
  /////////////////////////////////
  /// PR1_2c
  ///////////////////////////////// 
  tCompanyListNode* current = list.first;
  tCompany* companyFound = NULL;

  while (current != NULL && companyFound == NULL) {
    if (strcmp(current->elem.info.cif, cif) == 0) {
      companyFound = &current->elem;
    }
    current = current->next;
  }
    return companyFound;
}

// Add a company into the list
tApiError companyList_add(tCompanyList *list, tCompany company, tPerson *founder) {
	/////////////////////////////////
	// PR1_2d
	/////////////////////////////////
	tCompanyListNode* newNode;
  // Variable to store error code in order to not have many returns
  // and make the code more readable
  tApiError status;;
  tCompany* companyFound;

  // Variable to check if the company already exists
  companyFound = companyList_find(*list, company.info.cif);
  /* If company already exists, report duplication */
  if (companyFound != NULL) {
    status = E_COMPANY_DUPLICATED;
  } else {
    // Allocate memory for the new node 
    newNode = (tCompanyListNode*)malloc(sizeof(tCompanyListNode));
    // If successful add the new node to the list
    if (newNode == NULL) {
      status = E_MEMORY_ERROR;
    } 
    else {
      // Allocate memory for CIF and name strings as they are pointers
      // Check for memory allocation errors
      newNode->elem.info.cif = (char*)malloc(strlen(company.info.cif) + 1);
      newNode->elem.info.name = (char*)malloc(strlen(company.info.name) + 1);
      if (newNode->elem.info.cif == NULL || newNode->elem.info.name == NULL) {
        // in case of error free previously allocated memory and return memory error
        free(newNode->elem.info.cif);
        free(newNode->elem.info.name);
        free(newNode);
        status = E_MEMORY_ERROR;
      } 
      // in case of no error on memory allocation append info for the new company
      else { 
        strcpy(newNode->elem.info.cif, company.info.cif);
        strcpy(newNode->elem.info.name, company.info.name);

        // Copiar resto de campos de info
        newNode->elem.info.foundation = company.info.foundation;
        newNode->elem.info.minSize = company.info.minSize;
        newNode->elem.info.maxSize = company.info.maxSize;
        newNode->elem.info.hasAIEnabled = company.info.hasAIEnabled;
      }
      // Assign the founder pointer
      newNode->elem.founder = founder;

      // Initialize empty jobs
      jobs_init(&newNode->elem.jobs);

      newNode->next = NULL;
      
      // Append the new node to the end of the list
      if (list->first == NULL) {
        list->first = newNode;
        list->last = newNode;
      } 
      else {
        list->last->next = newNode;
        list->last = newNode;
      }

      // Update list size 
      list->size++;

      /* Do not reassign the incoming founder pointer here (type mismatch) */
      status = E_SUCCESS;
    }
  }
  return status;
}

tApiError companyList_del(tCompanyList *list, const char* cif) { 
  ///////////////////////////////// 
  // PR1_2e 
  ///////////////////////////////// 
  /// Variable to store error code in order to not have many returns 
  /// and make the code more readable 
  tApiError status;
  tCompanyListNode* nextNode;
  tCompanyListNode* current; 
  tCompanyListNode* previous; 
  // Temporary pointer to the node to delete 
  tCompanyListNode* toDelete;
  
  nextNode = NULL;
  current = list->first; 
  previous = NULL;
  status = E_COMPANY_NOT_FOUND; 
  toDelete = NULL; 
  
  // While loop to find the node to delete 
  while (current != NULL && status != E_SUCCESS) { 
    if (strcmp(current->elem.info.cif, cif) == 0) { 
      nextNode = current->next;
      // Once found check if the node is the first, last or in between and if it's not unique 
      toDelete = current; 
      if (list->first != list->last) { 
        // More than one node in the list 
        if (previous != NULL) { 
          // As previous is not NULL, it's not the first node 
          previous->next = current->next; 
        } 
        else { 
          // As previous is NULL, it's the first node 
          list->first = current->next; 
        } 
        if (current == list->last) {
          // As next node from current is the last node 
          list->last = previous; 
        } 
      } 
      else { 
        // Only one node in the list 
        list->first = NULL; list->last = NULL; 
      }
      // Free memory of the node 
      company_free(&toDelete->elem);
      // Free the current node 
      free(toDelete); 
      // Update size of the list
      list->size--; 
      // set error to success 
      status = E_SUCCESS; 
    } 
  
    previous = current; 
    current = current->next; 
  } 
  return status; 
}
  

// Remove all the companies from the list
tApiError companyList_free(tCompanyList *list) {
    /////////////////////////////////
	  // PR1_2f
	  /////////////////////////////////

    tCompanyListNode *current = list->first;
    tCompanyListNode *next;

    while (current != NULL) {
        next = current->next;
        company_free(&current->elem);
        free(current);  
        current = next;
    }
    
    // reset list pointers and size
    
    list->first = NULL;  
    list->last  = NULL;
    list->size  = 0;

    return E_SUCCESS;
}
