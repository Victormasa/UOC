#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "company.h"
#include "csv.h"

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
	// Check preconditions
	assert(list != NULL);
	
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
	
	return E_SUCCESS;
	/////////////////////////////////
	// return E_NOT_IMPLEMENTED;
}

// Return the number of companies of the list
int companyList_len(tCompanyList list) {
	/////////////////////////////////
	// PR1_2b
	/////////////////////////////////
	return list.size;
	/////////////////////////////////
	// return -1;
}

// Search a company by cif
tCompany* companyList_find(tCompanyList list, const char *cif) {
	/////////////////////////////////
	// PR1_2c
	/////////////////////////////////
	// Check preconditions
	assert(cif != NULL);
	
	// Get the first node of the list to start the search
	tCompanyListNode *node = list.first;
	
	// Iterate until the end of the list or when the company has been found
	while (node != NULL) {
		if (strcmp(node->elem.info.cif, cif) == 0) {
			return &(node->elem);
		}
		
		// Iterate to the next node
		node = node->next;
	}
	
	// Return NULL if the company is not in the list
	return NULL;
	/////////////////////////////////
	// return NULL;
}

// Add a company into the list
tApiError companyList_add(tCompanyList *list, tCompany company, tPerson *founder) {
	/////////////////////////////////
	// PR1_2d
	/////////////////////////////////
	// Check preconditions
	assert(list != NULL);
	
	// Check if the company already exists
	if (companyList_find(*list, company.info.cif) != NULL) {
        return E_COMPANY_DUPLICATED;
    }
	
	// Create the node and allocate the memory
	tCompanyListNode *node = (tCompanyListNode*)malloc(sizeof(tCompanyListNode));
    if (node == NULL) {
        return E_MEMORY_ERROR;
    }
	
	// Initialize the company info
	companyInfo_init(&(node->elem.info),
                     company.info.cif,
                     company.info.name,
                     company.info.foundation,
                     company.info.minSize,
                     company.info.maxSize,
                     company.info.hasAIEnabled);
	
	// Update founder pointer
	node->elem.founder = founder;
	
	// Initialize the jobs vector
	jobs_init(&(node->elem.jobs));
	
	// Point the next to NULL because this will be the last node
	node->next = NULL;
	
	// Update the pointers of the list to link the new node
	if (list->size == 0) {
		list->first = node;
		list->last  = node;
	} else {
		list->last->next = node;
		list->last = node;
	}
	
	// Update the new size of the list
	list->size++;
	
	return E_SUCCESS;
	/////////////////////////////////
	// return E_NOT_IMPLEMENTED;
}

// Remove a company from the list
tApiError companyList_del(tCompanyList *list, const char* cif) {
	/////////////////////////////////
	// PR1_2e
	/////////////////////////////////
	// Check preconditions
	assert(list != NULL);
	assert(cif != NULL);
	
	tCompanyListNode *prev = NULL;
    tCompanyListNode *cur  = list->first;
	
	// Find the node by its CIF
    while (cur != NULL && strcmp(cur->elem.info.cif, cif) != 0) {
        prev = cur;
        cur  = cur->next;
    }
	
	// Return an error if the company is not found
	if (cur == NULL) {
        return E_COMPANY_NOT_FOUND;
    }
	
	// Update the first or next pointers (removing the current node)
	if (prev == NULL) {
		list->first = cur->next;
	} else {
		prev->next = cur->next;
	}
	
	// Update the last pointer (only if the node to remove was the last one)
	if (cur->next == NULL) {
        list->last = prev;
    }
	
	// Release the memory of every element of this node
    company_free(&(cur->elem));
	
	// Release the memory of this node
	free(cur);
	
	// Update the list to the new size
	list->size--;
	
	return E_SUCCESS;
	/////////////////////////////////
	// return E_NOT_IMPLEMENTED;
}

// Remove all the companies from the list
tApiError companyList_free(tCompanyList *list) {
	/////////////////////////////////
	// PR1_2f
	/////////////////////////////////
	// Check preconditions
	assert(list != NULL);
	
	// Delete items while the list is not empty
	while (list->size > 0) {
		companyList_del(list, list->first->elem.info.cif);
	}
	
	// Initialize the structure
	companyList_init(list);
	
	return E_SUCCESS;
	/////////////////////////////////
	// return E_NOT_IMPLEMENTED;
}
