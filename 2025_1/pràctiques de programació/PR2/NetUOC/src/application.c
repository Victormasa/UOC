#include "application.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "person.h"
#include "job.h"

// Parse input from CSVEntry
void application_parse(tApplication *data, char *personDocument, int *jobId, tCSVEntry entry) {
	// Check input data
	assert(data != NULL);
	assert(personDocument != NULL);
	assert(jobId != NULL);
	
	// Check entry fields
    assert(csv_numFields(entry) == NUM_FIELDS_APPLICATION);
	
	int pos = 0;
	char date[DATE_LENGTH + 1];
	char time[TIME_LENGTH + 1];
	
	// Application id
	data->id = csv_getAsInteger(entry, pos++);
	
	// Person document
	csv_getAsString(entry, pos, personDocument, strlen(entry.fields[pos]) + 1);
	pos++;
	
	// Job id
	*jobId = csv_getAsInteger(entry, pos++);
	
	// Application date
    assert(strlen(entry.fields[pos]) == DATE_LENGTH);
    csv_getAsString(entry, pos, date, DATE_LENGTH + 1);
	pos++;
	
	// Application time
	assert(strlen(entry.fields[pos]) == TIME_LENGTH);
	csv_getAsString(entry, pos, time, TIME_LENGTH + 1);
	pos++;
	
	// Store datatime as a single property
	dateTime_parse(&(data->appliedAt), date, time);
	
	// Initialize status at PENDING
	data->status = APP_STATUS_PENDING;
	
	// Initialize the pointers to NULL
	data->person = NULL;
	data->job = NULL;
	data->observations = NULL;
}

// Copy the data from the source to destination (individual data)
void application_cpy(tApplication* destination, tApplication source) {
	// Check input data
	assert(destination != NULL);
	
	// Application id
	destination->id = source.id;
	
	// Person pointer
	destination->person = source.person;
	
	// Job offer pointer
	destination->job = source.job;
	
	// Application status
	destination->status = source.status;
	
	// Application application datetime
	dateTime_cpy(&(destination->appliedAt), source.appliedAt);
	
	// Observations
	if (source.observations != NULL) {
		destination->observations = (char*) malloc(sizeof(char) * (strlen(source.observations) + 1));
		assert(destination->observations != NULL);
		strcpy(destination->observations, source.observations);
	} else {
		destination->observations = NULL;
	}
}

// Get application data using a string
void application_get(tApplication data, char* buffer) {
	// Print all data at same time
	sprintf(buffer, "%d;%s;%d;%d;%02d/%02d/%04d;%02d:%02d;%s",
		data.id,
		data.person->document,
		data.job->id,
		data.status,
		data.appliedAt.date.day, data.appliedAt.date.month, data.appliedAt.date.year,
		data.appliedAt.time.hour, data.appliedAt.time.minutes,
		data.observations == NULL ? "" : data.observations);
}

// Release all the allocated memory
void application_free(tApplication *data) {
	// Check input data
	assert(data != NULL);
	
	// Release all memory allocated
	if (data->observations != NULL) {
		free(data->observations);
		data->observations = NULL;
	}
}

// Initialize applications data
void applicationTable_init(tApplicationTable* data) {
	// Check input data
	assert(data != NULL);
	
	data->count = 0;
}

// Add a new application
void applicationTable_add(tApplicationTable *data, tApplication application) {
	// Check input data
	assert(data != NULL);
	
	// If application does not exist, add it
	if (applicationTable_find(*data, application.id) < 0) {
		// Only add the application if the vector has not reached the maximum number of applications
		if (data->count < MAX_APPLICATIONS) {
			// Check the allocation
			assert(data->elems != NULL);
			
			// Copy the application to the new position
			application_cpy(&(data->elems[data->count]), application);
			
			// Increase the number of elements
			data->count++;
		}
	}
}

// Return the number of applications of the table
int applicationTable_len(tApplicationTable data) {
	return data.count;
}

// Returns the position of an application looking for application id. -1 if it does not exist
int applicationTable_find(tApplicationTable data, int id) {
	int i;
    
    for (i = 0; i < data.count; i++) {
        if (data.elems[i].id == id) {
            return i;
        }
    }
    
    return -1;
}

// Release all the applications
void applicationTable_free(tApplicationTable *data) {
	int i;
    
    // Check input data
    assert(data != NULL);
    
    // Remove contents
    for(i = 0; i < data->count; i++) {
        application_free(&(data->elems[i]));
    }
    
    applicationTable_init(data);
}

// Create the applications stack
tApiError applicationStack_createStack(tApplicationStack *stack) {
	/////////////////////////////////
	// PR2_1a
	/////////////////////////////////
  tApiError error;
  
  stack->first = NULL;
 
  error = E_SUCCESS;
	/////////////////////////////////
	return  error;
}

// Check if the stack is empty
bool applicationStack_emptyStack(tApplicationStack stack) {
	/////////////////////////////////
	// PR2_1b
	/////////////////////////////////
  bool isStackEmpty;

  if (stack.first == NULL) {
    isStackEmpty = true;
  } 
  else {
    isStackEmpty = false;
  }

	/////////////////////////////////
	return isStackEmpty;
}

// Push a new application to the stack
tApiError applicationStack_push(tApplicationStack *stack, tApplication *application) {
	/////////////////////////////////
	// PR2_1c
	/////////////////////////////////
	tApiError error;
  tApplicationStackNode *newNode;

  // Allocate memory for the new node
  newNode = (tApplicationStackNode *)malloc(sizeof(tApplicationStackNode));
  if (newNode == NULL) {
    error = E_MEMORY_ERROR;
  }
  else {
    // Insert the new node at the end of the stack
    if (applicationStack_emptyStack(*stack) == true) {
      applicationStack_createStack(stack);
    }

    newNode->elem = application;

    newNode->next = stack->first;
    stack->first = newNode;

    error = E_SUCCESS;
  }
  
	/////////////////////////////////
	return error;

}

// Pop an application from the stack
tApiError applicationStack_pop(tApplicationStack *stack) {
	/////////////////////////////////
	// PR2_1d
	/////////////////////////////////
	
  tApiError error;
  tApplicationStackNode *newNode;

  if (applicationStack_emptyStack(*stack) == true) {
    error = E_APP_NOT_FOUND;
  }
  else {
    tApplicationStackNode *tempNode;

    // Remove the top node from the stack
    newNode = stack->first;
    stack->first = stack->first->next;

    // Free the memory of the removed node
    free(newNode);

    error = E_SUCCESS;
  }
  
	/////////////////////////////////
	return error;
}

// Get the pointer to the top of the stack
tApplication* applicationStack_top(tApplicationStack stack) {
	/////////////////////////////////
	// PR2_1e
	/////////////////////////////////
  
  tApplication* topApplication;

  if (applicationStack_emptyStack(stack) == false) {
    topApplication = stack.first->elem;
  }
  else {
    topApplication = NULL;
  }
	/////////////////////////////////
	return topApplication;
}

// Remove all the elements from the stack
tApiError applicationStack_free(tApplicationStack *stack) {
	/////////////////////////////////
	// PR2_1f
	/////////////////////////////////
  tApplicationStackNode *application;
  
  while (stack->first != NULL) {
    application = stack->first;
    stack->first = stack->first->next;
    free(application);
  }

	/////////////////////////////////
	return E_SUCCESS;
}

// Create the applications queue
tApiError applicationQueue_createQueue(tApplicationQueue *queue) {
	/////////////////////////////////
	// PR2_2a
	/////////////////////////////////
	tApiError error;
  
  queue->first = NULL;
  queue->last = NULL;

  error = E_SUCCESS;
	/////////////////////////////////
	return error;
}

// Check if the queue is empty
bool applicationQueue_emptyQueue(tApplicationQueue queue) {
	/////////////////////////////////
	// PR2_2b
	/////////////////////////////////
	bool isQueueEmpty;

  if (queue.first == NULL) {
    isQueueEmpty = true;
  } 
  else {
    isQueueEmpty = false;
  }

	/////////////////////////////////
	return isQueueEmpty;
}

// Enqueue a new application to the queue
tApiError applicationQueue_enqueue(tApplicationQueue *queue, tApplication *application) {
	/////////////////////////////////
	// PR2_2c
	/////////////////////////////////
  tApiError error;
  tApplicationQueueNode *newQueue;
  
  newQueue = (tApplicationQueueNode *)malloc(sizeof(tApplicationQueueNode));

  if (newQueue == NULL) {
      error = E_MEMORY_ERROR;
  }
  else {
      newQueue->elem = application;
      newQueue->next = NULL;

      if (applicationQueue_emptyQueue(*queue) == true) {
          queue->first = newQueue;
          queue->last = newQueue;
      } 
      else {
          queue->last->next = newQueue;
          queue->last = newQueue;
      }

      error = E_SUCCESS;
  }

	/////////////////////////////////
	return error;
}

// Dequeue an application from the queue
tApiError applicationQueue_dequeue(tApplicationQueue *queue) {
	/////////////////////////////////
	// PR2_2d
	/////////////////////////////////
	tApiError error;
  tApplicationQueueNode *newQueue;

  if (applicationQueue_emptyQueue(*queue) == true) {
    error = E_APP_NOT_FOUND;
  }
  else {
    tApplicationQueueNode *tempNode;

    // Remove the first node from the queue
    newQueue = queue->first;
    queue->first = queue->first->next;

    // If the queue is now empty, update the last pointer
    if (queue->first == NULL) {
        queue->last = NULL;
    }

    // Free the memory of the removed node
    free(newQueue);

    error = E_SUCCESS;
  }
	/////////////////////////////////
	return error;
}

// Get the pointer to the first application of the queue
tApplication* applicationQueue_head(tApplicationQueue queue) {
	/////////////////////////////////
	// PR2_2e
	/////////////////////////////////
	tApplication *headApplication;

  if (applicationQueue_emptyQueue(queue) == false) {
    headApplication = queue.first->elem;
  }
  else {
    headApplication = NULL;
  }
	/////////////////////////////////
	return headApplication;
}

// Remove all the elements from the queue
tApiError applicationQueue_free(tApplicationQueue *queue) {
	/////////////////////////////////
	// PR2_2f
	/////////////////////////////////
  tApplicationQueueNode *application;

  while (queue->last != NULL) {
    application = queue->first;
    if (queue->first != NULL) {
      queue->first = queue->first->next;
    }
    else {
      queue->last = NULL;
    }
    free(application);
  }
	/////////////////////////////////
	return E_SUCCESS;
}
