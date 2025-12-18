#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include <stdbool.h>
#include "date.h"
#include "csv.h"
#include "error.h"

// Define the struct despite its incompleteness to prevent including recursion error
typedef struct _tJob tJob;
typedef struct _tPerson tPerson;

#define MAX_APPLICATIONS 100
#define NUM_FIELDS_APPLICATION 5

typedef enum {
	APP_STATUS_PENDING,
	APP_STATUS_REJECTED,
	APP_STATUS_HIRED
} tApplicationStatus;

typedef struct _tApplication {
	int id;
	tPerson *person;
	tJob *job;
	tApplicationStatus status;
	tDateTime appliedAt;
	char *observations;
} tApplication;

typedef struct _tApplicationTable {
	tApplication elems[MAX_APPLICATIONS];
	int count;
} tApplicationTable;

typedef struct _tApplicationStackNode {
	tApplication *elem;
	struct _tApplicationStackNode *next;
} tApplicationStackNode;

typedef struct _tApplicationStack {
	tApplicationStackNode *first;
} tApplicationStack;

typedef struct _tApplicationQueueNode {
	tApplication *elem;
	struct _tApplicationQueueNode *next;
} tApplicationQueueNode;

typedef struct _tApplicationQueue {
	tApplicationQueueNode *first;
	tApplicationQueueNode *last;
} tApplicationQueue;

//////////////////////////////////
// Available functions
//////////////////////////////////

// Parse input from CSVEntry
void application_parse(tApplication *data, char *personDocument, int *jobId, tCSVEntry entry);

// Copy the data from the source to destination (individual data)
void application_cpy(tApplication* destination, tApplication source);

// Get application data using a string
void application_get(tApplication data, char* buffer);

// Release all the allocated memory
void application_free(tApplication *data);

// Initialize applications data
void applicationTable_init(tApplicationTable* data);

// Add a new application
void applicationTable_add(tApplicationTable *data, tApplication application);

// Return the number of applications of the table
int applicationTable_len(tApplicationTable data);

// Returns the position of an application looking for application id. -1 if it does not exist
int applicationTable_find(tApplicationTable data, int id);

// Release all the applications
void applicationTable_free(tApplicationTable *data);

// Create the applications stack
tApiError applicationStack_createStack(tApplicationStack *stack);

// Check if the stack is empty
bool applicationStack_emptyStack(tApplicationStack stack);

// Push a new application to the stack
tApiError applicationStack_push(tApplicationStack *stack, tApplication *application);

// Pop an application from the stack
tApiError applicationStack_pop(tApplicationStack *stack);

// Get the pointer to the top of the stack
tApplication* applicationStack_top(tApplicationStack stack);

// Remove all the elements from the stack
tApiError applicationStack_free(tApplicationStack *stack);

// Create the applications queue
tApiError applicationQueue_createQueue(tApplicationQueue *queue);

// Check if the queue is empty
bool applicationQueue_emptyQueue(tApplicationQueue queue);

// Enqueue a new application to the queue
tApiError applicationQueue_enqueue(tApplicationQueue *queue, tApplication *application);

// Dequeue an application from the queue
tApiError applicationQueue_dequeue(tApplicationQueue *queue);

// Get the pointer to the first application of the queue
tApplication* applicationQueue_head(tApplicationQueue queue);

// Remove all the elements from the queue
tApiError applicationQueue_free(tApplicationQueue *queue);

#endif
