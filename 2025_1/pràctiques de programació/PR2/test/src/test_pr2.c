#include "test_pr2.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "application.h"

// Run all tests for PR2
bool run_pr2(tTestSuite *test_suite, const char *input) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR2", "Tests for PR2 exercices");

    section = testSuite_getSection(test_suite, "PR2");
    assert(section != NULL);

    ok = run_pr2_ex1(section, input);
    ok = run_pr2_ex2(section, input) && ok;
    ok = run_pr2_ex3(section, input) && ok;
    ok = run_pr2_ex4(section, input) && ok;

    return ok;
}

// Run tests for PR2 exercice 1
bool run_pr2_ex1(tTestSection* test_section, const char* input) {
	tApiError error;
	tCSVEntry entry;
	tApplication application, *applicationPtr;
	tApplicationTable applications;
	tApplicationStack applicationsStack, applicationsStack2;
	char personDocument[FILE_READ_BUFFER_SIZE];
	int jobId;
	tApiData data;
	
	bool passed = true;
	bool failed = false;
	bool fail_all = false;
	
	// Initialize the data
	api_initData(&data);
	applicationTable_init(&applications);
	
	// Initialize people
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "00000000A;Gabriel;Ferrate;987654321;gferrate@uoc.edu;Rambla de Poblenou, 154-156;08001;03/03/1932", "PERSON");
	api_addPerson(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954", "PERSON");
	api_addPerson(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867", "PERSON");
	api_addPerson(&data, entry);
	csv_freeEntry(&entry);
	
	// Intialize companies
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "G60667813;Universitat Oberta de Catalunya;06/10/1994;1000;9999;1;00000000A", "COMPANY");
	api_addCompany(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "B90234567;TechNova Solutions;15/03/2010;50;300;1;33365111X", "COMPANY");
	api_addCompany(&data, entry);
	csv_freeEntry(&entry);
	
	// Initialize jobs
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "1;Junior software developer;1;01/10/2025;20/11/2025;20000;35000;G60667813", "JOB");
	api_addJob(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "2;Course instructor;2;15/10/2025;31/10/2025;19000;22000;G60667813", "JOB");
	api_addJob(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "3;Senior software developer;1;15/10/2025;15/12/2025;30000;33000;B90234567", "JOB");
	api_addJob(&data, entry);
	csv_freeEntry(&entry);
	
	// Initialize applications
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "1;98765432J;1;06/11/2025;20:51", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "2;98765432J;2;08/11/2025;17:22", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "3;98765432J;3;09/11/2025;10:58", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "4;00000000A;3;10/11/2025;12:01", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "5;33365111X;1;12/11/2025;07:57", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "6;33365111X;2;14/11/2025;12:35", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	/////////////////////////////
	/////  PR2 EX1 TEST 1  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX1_1", "Initialize the application stack", 0.2);
	// Initialize the applications stack
	error = applicationStack_createStack(&applicationsStack);
	if (error != E_SUCCESS) {
		failed = true;
		passed = false;
		fail_all = true;
	} else if (applicationsStack.first != NULL) {
		failed = true;
		passed = false;
		fail_all = true;
	}
	end_test(test_section, "PR2_EX1_1", !failed);

	/////////////////////////////
	/////  PR2 EX1 TEST 2  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX1_2", "Push an application to an empty stack", 0.25);
	if (fail_all) {
		failed = true;
	} else {
		// Push an application to an empty stack
		error = applicationStack_push(&applicationsStack, &(applications.elems[1]));
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (applicationsStack.first == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsStack.first->elem == NULL || applicationsStack.first->elem != &(applications.elems[1]) || applicationsStack.first->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR2_EX1_2", !failed);
	
	/////////////////////////////
	/////  PR2 EX1 TEST 3  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX1_3", "Push an application to a non-empty stack", 0.5);
	if (fail_all) {
		failed = true;
	} else {
		// Push an application to a non-empty stack
		error = applicationStack_push(&applicationsStack, &(applications.elems[2]));
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (applicationsStack.first == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsStack.first->elem == NULL || applicationsStack.first->elem != &(applications.elems[2]) || applicationsStack.first->next == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsStack.first->next->elem == NULL || applicationsStack.first->next->elem != &(applications.elems[1]) || applicationsStack.first->next->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			}
			
			if (!failed) {
				error = applicationStack_push(&applicationsStack, &(applications.elems[0]));
				if (error != E_SUCCESS) {
					failed = true;
					passed = false;
					fail_all = true;
				} else {
					if (applicationsStack.first == NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsStack.first->elem == NULL || applicationsStack.first->elem != &(applications.elems[0]) || applicationsStack.first->next == NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsStack.first->next->elem == NULL || applicationsStack.first->next->elem != &(applications.elems[2]) || applicationsStack.first->next->next == NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsStack.first->next->next->elem == NULL || applicationsStack.first->next->next->elem != &(applications.elems[1]) || applicationsStack.first->next->next->next != NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					}
				}
			}
		}
	}
	end_test(test_section, "PR2_EX1_3", !failed);
	
	/////////////////////////////
	/////  PR2 EX1 TEST 4  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX1_4", "Check if an application stack is empty", 0.2);
	if (fail_all) {
		failed = true;
	} else {
		applicationStack_createStack(&applicationsStack2);
		if (applicationStack_emptyStack(applicationsStack)) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (!applicationStack_emptyStack(applicationsStack2)) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX1_4", !failed);
	
	/////////////////////////////
	/////  PR2 EX1 TEST 5  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX1_5", "Pop an application from an empty stack", 0.25);
	if (fail_all) {
		failed = true;
	} else {
		error = applicationStack_pop(&applicationsStack2);
		if (error != E_APP_NOT_FOUND) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX1_5", !failed);
	
	/////////////////////////////
	/////  PR2 EX1 TEST 6  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX1_6", "Pop an application from a non-empty stack", 0.5);
	if (fail_all) {
		failed = true;
	} else {
		error = applicationStack_pop(&applicationsStack);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (applicationsStack.first == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsStack.first->elem == NULL || applicationsStack.first->elem != &(applications.elems[2]) || applicationsStack.first->next == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsStack.first->next->elem == NULL || applicationsStack.first->next->elem != &(applications.elems[1]) || applicationsStack.first->next->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			}
			
			if (!failed) {
				error = applicationStack_pop(&applicationsStack);
				if (error != E_SUCCESS) {
					failed = true;
					passed = false;
					fail_all = true;
				} else {
					if (applicationsStack.first == NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsStack.first->elem == NULL || applicationsStack.first->elem != &(applications.elems[1]) || applicationsStack.first->next != NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					}
				}
				
				error = applicationStack_pop(&applicationsStack);
				if (error != E_SUCCESS) {
					failed = true;
					passed = false;
					fail_all = true;
				} else {
					if (applicationsStack.first != NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					}
				}
				
				error = applicationStack_pop(&applicationsStack);
				if (error != E_APP_NOT_FOUND) {
					failed = true;
					passed = false;
					fail_all = true;
				}
			}
		}
	}
	end_test(test_section, "PR2_EX1_6", !failed);
	
	/////////////////////////////
	/////  PR2 EX1 TEST 7  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX1_7", "Get the top of the stack", 0.3);
	if (fail_all) {
		failed = true;
	} else {
		applicationPtr = applicationStack_top(applicationsStack);
		if (applicationPtr != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			applicationStack_push(&applicationsStack, &(applications.elems[3]));
			applicationPtr = applicationStack_top(applicationsStack);
			if (applicationPtr != &(applications.elems[3])) {
				failed = true;
				passed = false;
				fail_all = true;
			}
			
			applicationStack_push(&applicationsStack, &(applications.elems[1]));
			applicationPtr = applicationStack_top(applicationsStack);
			if (applicationPtr != &(applications.elems[1])) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR2_EX1_7", !failed);
	
	/////////////////////////////
	/////  PR2 EX1 TEST 8  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX1_8", "Pop all the applications from the stack", 0.3);
	if (fail_all) {
		failed = true;
	} else {
		error = applicationStack_free(&applicationsStack);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (applicationsStack.first != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX1_8", !failed);
	
	// Release all data
	applicationStack_free(&applicationsStack2);
	applicationStack_free(&applicationsStack);
	applicationTable_free(&applications);
	api_freeData(&data);
	
	return passed;
}

// Run tests for PR2 exercice 2
bool run_pr2_ex2(tTestSection* test_section, const char* input) {
	tApiError error;
	tCSVEntry entry;
	tApplication application, *applicationPtr;
	tApplicationTable applications;
	tApplicationQueue applicationsQueue, applicationsQueue2;
	char personDocument[FILE_READ_BUFFER_SIZE];
	int jobId;
	tApiData data;
	
	bool passed = true;
	bool failed = false;
	bool fail_all = false;
	
	// Initialize the data
	api_initData(&data);
	applicationTable_init(&applications);
	
	// Initialize people
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "00000000A;Gabriel;Ferrate;987654321;gferrate@uoc.edu;Rambla de Poblenou, 154-156;08001;03/03/1932", "PERSON");
	api_addPerson(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954", "PERSON");
	api_addPerson(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867", "PERSON");
	api_addPerson(&data, entry);
	csv_freeEntry(&entry);
	
	// Intialize companies
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "G60667813;Universitat Oberta de Catalunya;06/10/1994;1000;9999;1;00000000A", "COMPANY");
	api_addCompany(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "B90234567;TechNova Solutions;15/03/2010;50;300;1;33365111X", "COMPANY");
	api_addCompany(&data, entry);
	csv_freeEntry(&entry);
	
	// Initialize jobs
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "1;Junior software developer;1;01/10/2025;20/11/2025;20000;35000;G60667813", "JOB");
	api_addJob(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "2;Course instructor;2;15/10/2025;31/10/2025;19000;22000;G60667813", "JOB");
	api_addJob(&data, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "3;Senior software developer;1;15/10/2025;15/12/2025;30000;33000;B90234567", "JOB");
	api_addJob(&data, entry);
	csv_freeEntry(&entry);
	
	// Initialize applications
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "1;98765432J;1;06/11/2025;20:51", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "2;98765432J;2;08/11/2025;17:22", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "3;98765432J;3;09/11/2025;10:58", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "4;00000000A;3;10/11/2025;12:01", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "5;33365111X;1;12/11/2025;07:57", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "6;33365111X;2;14/11/2025;12:35", "APPLICATION");
	application_parse(&application, personDocument, &jobId, entry);
	applicationTable_add(&applications, application);
	application_free(&application);
	csv_freeEntry(&entry);
	
	/////////////////////////////
	/////  PR2 EX2 TEST 1  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX2_1", "Initialize the application queue", 0.2);
	// Initialize the applications queue
	error = applicationQueue_createQueue(&applicationsQueue);
	if (error != E_SUCCESS) {
		failed = true;
		passed = false;
		fail_all = true;
	} else if (applicationsQueue.first != NULL || applicationsQueue.last != NULL) {
		failed = true;
		passed = false;
		fail_all = true;
	}
	end_test(test_section, "PR2_EX2_1", !failed);
	
	/////////////////////////////
	/////  PR2 EX2 TEST 2  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX2_2", "Enqueue an application to an empty queue", 0.25);
	if (fail_all) {
		failed = true;
	} else {
		// Enqueue an application to an empty queue
		error = applicationQueue_enqueue(&applicationsQueue, &(applications.elems[0]));
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (applicationsQueue.first == NULL || applicationsQueue.last == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.first != applicationsQueue.last) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.first->elem == NULL || applicationsQueue.first->elem != &(applications.elems[0]) || applicationsQueue.first->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.last->elem == NULL || applicationsQueue.last->elem != &(applications.elems[0]) || applicationsQueue.last->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR2_EX2_2", !failed);
	
	/////////////////////////////
	/////  PR2 EX2 TEST 3  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX2_3", "Enqueue an application to a non-empty queue", 0.5);
	if (fail_all) {
		failed = true;
	} else {
		// Enqueue an application to a non-empty queue
		error = applicationQueue_enqueue(&applicationsQueue, &(applications.elems[2]));
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (applicationsQueue.first == NULL || applicationsQueue.last == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.first == applicationsQueue.last) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.first->elem == NULL || applicationsQueue.first->elem != &(applications.elems[0]) || applicationsQueue.first->next == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.first->next->elem == NULL || applicationsQueue.first->next->elem != &(applications.elems[2]) || applicationsQueue.first->next->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.last->elem == NULL || applicationsQueue.last->elem != &(applications.elems[2]) || applicationsQueue.last->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			}
			
			if (!failed) {
				error = applicationQueue_enqueue(&applicationsQueue, &(applications.elems[1]));
				if (error != E_SUCCESS) {
					failed = true;
					passed = false;
					fail_all = true;
				} else {
					if (applicationsQueue.first == NULL || applicationsQueue.last == NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsQueue.first == applicationsQueue.last) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsQueue.first->elem == NULL || applicationsQueue.first->elem != &(applications.elems[0]) || applicationsQueue.first->next == NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsQueue.first->next->elem == NULL || applicationsQueue.first->next->elem != &(applications.elems[2]) || applicationsQueue.first->next->next == NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsQueue.first->next->next->elem == NULL || applicationsQueue.first->next->next->elem != &(applications.elems[1]) || applicationsQueue.first->next->next->next != NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsQueue.last->elem == NULL || applicationsQueue.last->elem != &(applications.elems[1]) || applicationsQueue.last->next != NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					}
				}
			}
		}
	}
	end_test(test_section, "PR2_EX2_3", !failed);
	
	/////////////////////////////
	/////  PR2 EX2 TEST 4  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX2_4", "Check if an application queue is empty", 0.2);
	if (fail_all) {
		failed = true;
	} else {
		applicationQueue_createQueue(&applicationsQueue2);
		if (applicationQueue_emptyQueue(applicationsQueue)) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (!applicationQueue_emptyQueue(applicationsQueue2)) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX2_4", !failed);
	
	/////////////////////////////
	/////  PR2 EX2 TEST 5  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX2_5", "Dequeue an application from an empty queue", 0.25);
	if (fail_all) {
		failed = true;
	} else {
		error = applicationQueue_dequeue(&applicationsQueue2);
		if (error != E_APP_NOT_FOUND) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX2_5", !failed);
	
	/////////////////////////////
	/////  PR2 EX2 TEST 6  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX2_6", "Dequeue an application from a non-empty queue", 0.5);
	if (fail_all) {
		failed = true;
	} else {
		error = applicationQueue_dequeue(&applicationsQueue);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (applicationsQueue.first == NULL || applicationsQueue.last == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.first == applicationsQueue.last) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.first->elem == NULL || applicationsQueue.first->elem != &(applications.elems[2]) || applicationsQueue.first->next == NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.first->next->elem == NULL || applicationsQueue.first->next->elem != &(applications.elems[1]) || applicationsQueue.first->next->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (applicationsQueue.last->elem == NULL || applicationsQueue.last->elem != &(applications.elems[1]) || applicationsQueue.last->next != NULL) {
				failed = true;
				passed = false;
				fail_all = true;
			}
			
			if (!failed) {
				error = applicationQueue_dequeue(&applicationsQueue);
				if (error != E_SUCCESS) {
					failed = true;
					passed = false;
					fail_all = true;
				} else {
					if (applicationsQueue.first == NULL || applicationsQueue.last == NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsQueue.first != applicationsQueue.last) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsQueue.first->elem == NULL || applicationsQueue.first->elem != &(applications.elems[1]) || applicationsQueue.first->next != NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					} else if (applicationsQueue.last->elem == NULL || applicationsQueue.last->elem != &(applications.elems[1]) || applicationsQueue.last->next != NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					}
				}
				
				error = applicationQueue_dequeue(&applicationsQueue);
				if (error != E_SUCCESS) {
					failed = true;
					passed = false;
					fail_all = true;
				} else {
					if (applicationsQueue.first != NULL || applicationsQueue.last != NULL) {
						failed = true;
						passed = false;
						fail_all = true;
					}
				}
				
				error = applicationQueue_dequeue(&applicationsQueue);
				if (error != E_APP_NOT_FOUND) {
					failed = true;
					passed = false;
					fail_all = true;
				}
			}
		}
	}
	end_test(test_section, "PR2_EX2_6", !failed);
	
	/////////////////////////////
	/////  PR2 EX2 TEST 7  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX2_7", "Get the head of the queue", 0.3);
	if (fail_all) {
		failed = true;
	} else {
		applicationPtr = applicationQueue_head(applicationsQueue);
		if (applicationPtr != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			applicationQueue_enqueue(&applicationsQueue, &(applications.elems[3]));
			applicationPtr = applicationQueue_head(applicationsQueue);
			if (applicationPtr != &(applications.elems[3])) {
				failed = true;
				passed = false;
				fail_all = true;
			}
			
			applicationQueue_enqueue(&applicationsQueue, &(applications.elems[1]));
			applicationPtr = applicationQueue_head(applicationsQueue);
			if (applicationPtr != &(applications.elems[3])) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR2_EX2_7", !failed);
	
	/////////////////////////////
	/////  PR2 EX2 TEST 8  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX2_8", "Dequeue all the applications from the queue", 0.3);
	if (fail_all) {
		failed = true;
	} else {
		error = applicationQueue_free(&applicationsQueue);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (applicationsQueue.first != NULL || applicationsQueue.last != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX2_8", !failed);
	
	// Release all data
	applicationQueue_free(&applicationsQueue2);
	applicationQueue_free(&applicationsQueue);
	applicationTable_free(&applications);
	api_freeData(&data);
	
	return passed;
}

// Run tests for PR2 exercice 3
bool run_pr2_ex3(tTestSection* test_section, const char* input) {
	tApiError error;
	tCSVEntry entry;
	tPerson person1, person2;
	tJob job1, job2;
	tApplication application1, application2;
	char document[FILE_READ_BUFFER_SIZE];
	int jobId;
	tApiData data;
	int nPeople, nCompanies, nJobs, nApplications;
	
	bool passed = true;
	bool failed = false;
	bool fail_all = false;
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "1;98765432J;1;06/11/2025;20:51", "APPLICATION");
	application_parse(&application1, document, &jobId, entry);
	csv_freeEntry(&entry);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "2;98765432J;2;08/11/2025;17:22", "APPLICATION");
	application_parse(&application2, document, &jobId, entry);
	csv_freeEntry(&entry);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 1  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_1", "Initialize the API data structure with applications", 0.15);
	error = api_initData(&data);
	if (error != E_SUCCESS) {
		failed = true;
		passed = false;
		fail_all = true;
	} else if (data.people.elems != NULL || data.people.count != 0) {
		failed = true;
		passed = false;
		fail_all = true;
	} else if (data.companies.first != NULL || data.companies.last != NULL || data.companies.size != 0) {
		failed = true;
		passed = false;
		fail_all = true;
	} else if (data.applications.count != 0) {
		failed = true;
		passed = false;
		fail_all = true;
	}
	end_test(test_section, "PR2_EX3_1", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 2  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_2", "Parse a person with a stack of applications", 0.05);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "00000000A;Gabriel;Ferrate;987654321;gferrate@uoc.edu;Rambla de Poblenou, 154-156;08001;03/03/1932", "PERSON");
	person_parse(&person1, entry);
	csv_freeEntry(&entry);
	
	if (fail_all) {
		failed = true;
	} else {
		if (person1.applicationsStack.first != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_2", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 3  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_3", "Add an application pointer to a person's applications stack", 0.1);
	if (fail_all) {
		failed = true;
	} else {
		applicationStack_push(&(person1.applicationsStack), &application1);
		
		if (person1.applicationsStack.first == NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (person1.applicationsStack.first->elem != &application1) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_3", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 4  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_4", "Copy a person with a stack of applications", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		person_cpy(&person2, person1);
		if (person1.applicationsStack.first == NULL || person1.applicationsStack.first->elem != &application1 || person2.applicationsStack.first != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_4", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 5  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_5", "Pop all the applications from a person's stack ", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		person_free(&person1);
		person_free(&person2);
		if (person1.applicationsStack.first != NULL || person2.applicationsStack.first != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_5", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 6  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_6", "Parse a job with a queue of applications", 0.05);
	
	csv_initEntry(&entry);
	csv_parseEntry(&entry, "1;Junior software developer;1;01/10/2025;20/11/2025;20000;35000;G60667813", "JOB");
	job_parse(&job1, document, entry);
	csv_freeEntry(&entry);
	
	if (job1.applicationsQueue.first != NULL || job1.applicationsQueue.last != NULL) {
		failed = true;
		passed = false;
		fail_all = true;
	}
	end_test(test_section, "PR2_EX3_6", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 7  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_7", "Add an application pointer to a jobs's applications queue", 0.1);
	if (fail_all) {
		failed = true;
	} else {
		applicationQueue_enqueue(&(job1.applicationsQueue), &application2);
		
		if (job1.applicationsQueue.first == NULL || job1.applicationsQueue.last == NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (job1.applicationsQueue.first->elem != &application2 || job1.applicationsQueue.last->elem != &application2) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_7", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 8  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_8", "Copy a job with a queue of applications", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		job_cpy(&job2, job1);
		if (job1.applicationsQueue.first == NULL || job1.applicationsQueue.last == NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (job1.applicationsQueue.first->elem != &application2 || job1.applicationsQueue.last->elem != &application2) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (job2.applicationsQueue.first != NULL || job2.applicationsQueue.last != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_8", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 9  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_9", "Dequeue all the applications from a job's queue", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		job_free(&job1);
		job_free(&job2);
		if (job1.applicationsQueue.first != NULL || job1.applicationsQueue.last != NULL || job2.applicationsQueue.first != NULL || job2.applicationsQueue.last != NULL) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_9", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 10  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_10", "Add an invalid type application to a data API structure", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;33365111X;1;06/11/2025;20:51", "APLICATION");
		error = api_addApplication(&data, entry);
		if (error != E_INVALID_ENTRY_TYPE || data.applications.count != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR2_EX3_10", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 11  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_11", "Add an invalid format application to a data API structure", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;33365111X;1;06/11/2025;20:51;oops", "APPLICATION");
		error = api_addApplication(&data, entry);
		if (error != E_INVALID_ENTRY_FORMAT || data.applications.count != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR2_EX3_11", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 12  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_12", "Add an application with a non-existing person to a data API structure", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;11111111X;1;06/11/2025;20:51", "APPLICATION");
		error = api_addApplication(&data, entry);
		if (error != E_PERSON_NOT_FOUND || data.applications.count != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR2_EX3_12", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 13  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_13", "Add an application with a non-existing job to a data API structure", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867", "PERSON");
		api_addPerson(&data, entry);
		csv_freeEntry(&entry);

		csv_initEntry(&entry);
		csv_parseEntry(&entry, "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954", "PERSON");
		api_addPerson(&data, entry);
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;33365111X;1;06/11/2025;20:51", "APPLICATION");
		error = api_addApplication(&data, entry);
		if (error != E_JOB_NOT_FOUND || data.applications.count != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR2_EX3_13", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 14  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_14", "Add a valid application to a data API structure", 0.8);
	if (fail_all) {
		failed = true;
	} else {
		// Add companies
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "G60667813;Universitat Oberta de Catalunya;06/10/1994;1000;9999;1;98765432J", "COMPANY");
		api_addCompany(&data, entry);
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "B90234567;TechNova Solutions;15/03/2010;50;300;1;33365111X", "COMPANY");
		api_addCompany(&data, entry);
		csv_freeEntry(&entry);
		
		// Add jobs
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;Junior software developer;1;01/10/2025;20/11/2025;20000;35000;G60667813", "JOB");
		api_addJob(&data, entry);
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "2;Course instructor;2;15/10/2025;31/10/2025;19000;22000;G60667813", "JOB");
		api_addJob(&data, entry);
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "3;Senior software developer;1;15/10/2025;15/12/2025;30000;33000;B90234567", "JOB");
		api_addJob(&data, entry);
		csv_freeEntry(&entry);

		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;33365111X;1;06/11/2025;20:51", "APPLICATION");
		error = api_addApplication(&data, entry);
		if (error != E_SUCCESS || data.applications.count != 1) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (data.applications.elems[0].id != 1 || data.applications.elems[0].person != &(data.people.elems[0]) || data.applications.elems[0].job != &(data.companies.first->elem.jobs.elems[0])) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (data.people.elems[0].applicationsStack.first->elem != &(data.applications.elems[0]) || data.companies.first->elem.jobs.elems[0].applicationsQueue.first->elem != &(data.applications.elems[0])) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "2;98765432J;3;07/11/2025;14:02", "APPLICATION");
		error = api_addApplication(&data, entry);
		if (error != E_SUCCESS || data.applications.count != 2) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (data.applications.elems[0].id != 1 || data.applications.elems[0].person != &(data.people.elems[0]) || data.applications.elems[0].job != &(data.companies.first->elem.jobs.elems[0])) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (data.people.elems[0].applicationsStack.first->elem != &(data.applications.elems[0]) || data.companies.first->elem.jobs.elems[0].applicationsQueue.first->elem != &(data.applications.elems[0])) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (data.applications.elems[1].id != 2 || data.applications.elems[1].person != &(data.people.elems[1]) || data.applications.elems[1].job != &(data.companies.first->next->elem.jobs.elems[0])) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (data.people.elems[1].applicationsStack.first->elem != &(data.applications.elems[1]) || data.companies.first->next->elem.jobs.elems[0].applicationsQueue.first->elem != &(data.applications.elems[1])) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR2_EX3_14", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 15  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_15", "Check the number of applications", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		nApplications = api_applicationsCount(data);
		if (nApplications != 2) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "3;33365111X;2;06/11/2025;20:51", "APPLICATION");
			api_addApplication(&data, entry);
			csv_freeEntry(&entry);
			
			nApplications = api_applicationsCount(data);
			if (nApplications != 3) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR2_EX3_15", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 16  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_16", "Free API data", 0.15);
	if (fail_all) {
		failed = true;
	} else {
		error = api_freeData(&data);
		nPeople = api_peopleCount(data);
		nCompanies = api_companiesCount(data);
		nJobs = api_jobsCount(data);
		nApplications = api_applicationsCount(data);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (nPeople != 0 || nCompanies != 0 || nJobs != 0 || nApplications != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_16", !failed);
	
	/////////////////////////////
	/////  PR2 EX3 TEST 17  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX3_17", "Load data from file", 0.25);
	if (fail_all) {
		failed = true;
	} else {
		api_initData(&data);
		error = api_loadData(&data, input, true);
		nPeople = api_peopleCount(data);
		nCompanies = api_companiesCount(data);
		nJobs = api_jobsCount(data);
		nApplications = api_applicationsCount(data);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (nPeople != 5 || nCompanies != 5 || nJobs != 9 || nApplications != 12) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR2_EX3_17", !failed);
	
	// Release all data
	//job_free(&job1);
	//job_free(&job2);
	application_free(&application1);
	application_free(&application2);
	api_freeData(&data);
	// person1 and person2 already released
	
	return passed;
}

// Run tests for PR2 exercice 4
bool run_pr2_ex4(tTestSection* test_section, const char* input) {
	tApiData data;
	tApiError error;
	tCSVData report;
	tCSVData refReport;
	tApplicationStack *stackPtr;
	tApplicationQueue *queuePtr;
	
	bool passed = true;
	bool failed = false;
	bool fail_all = false;
	
	// Initialize and load data
	api_initData(&data);
	api_loadData(&data, input, true);
	
	/////////////////////////////
	/////  PR2 EX4 TEST 1  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX4_1", "Reverse the application stack of a non-existing person", 0.2);
	
	csv_init(&report);
	csv_init(&refReport);
	
	error = api_reversePersonApplicationStack(data, &report, "NON-EXIST");
	if (error != E_PERSON_NOT_FOUND) {
		failed = true;
		passed = false;
		fail_all = true;
	}
	
	csv_free(&report);
	csv_free(&refReport);
	
	end_test(test_section, "PR2_EX4_1", !failed);
	
	/////////////////////////////
	/////  PR2 EX4 TEST 2  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX4_2", "Reverse a person's stack of applications", 0.8);
	if (fail_all) {
		failed = true;
	} else {
		csv_init(&report);
		csv_init(&refReport);
		
		// Last element is observation, which is empty string at this moment
		csv_addStrEntry(&refReport, "1;47051307Z;1;0;06/11/2025;20:51;", "APPLICATION");
		csv_addStrEntry(&refReport, "2;47051307Z;4;0;07/11/2025;14:02;", "APPLICATION");
		csv_addStrEntry(&refReport, "9;47051307Z;9;0;10/08/2025;16:40;", "APPLICATION");
		
		error = api_reversePersonApplicationStack(data, &report, "47051307Z");
		
		if (error != E_SUCCESS || !csv_equals(report, refReport)) {
			failed = true;
			passed = false;
		} else {
			// Check if the order of the stack is correct
			stackPtr = &(data.people.elems[4].applicationsStack);
			if (stackPtr->first->elem->id != 9 || stackPtr->first->next->elem->id != 2 || stackPtr->first->next->next->elem->id != 1) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
		
		csv_free(&report);
		csv_free(&refReport);
	}
	end_test(test_section, "PR2_EX4_2", !failed);
	
	/////////////////////////////
	/////  PR2 EX4 TEST 3  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX4_3", "Reverse the application queue of a non-existing job", 0.2);
	if (fail_all) {
		failed = true;
	} else {
		csv_init(&report);
		csv_init(&refReport);
		
		error = api_reverseJobApplicationQueue(data, &report, 99);
		
		if (error != E_JOB_NOT_FOUND) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_free(&report);
		csv_free(&refReport);
	}
	end_test(test_section, "PR2_EX4_3", !failed);
	
	/////////////////////////////
	/////  PR2 EX4 TEST 4  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR2_EX4_4", "Reverse a job's queue of applications", 0.8);
	if (fail_all) {
		failed = true;
	} else {
		csv_init(&report);
		csv_init(&refReport);
		
		// Last element is observation, which is empty string at this moment
		csv_addStrEntry(&refReport, "12;55565432Z;4;0;17/11/2025;11:35;", "APPLICATION");
		csv_addStrEntry(&refReport, "11;12345672C;4;0;17/11/2025;10:10;", "APPLICATION");
		csv_addStrEntry(&refReport, "4;98765432J;4;0;09/11/2025;18:45;", "APPLICATION");
		csv_addStrEntry(&refReport, "2;47051307Z;4;0;07/11/2025;14:02;", "APPLICATION");
		
		error = api_reverseJobApplicationQueue(data, &report, 4);
		
		if (error != E_SUCCESS || !csv_equals(report, refReport)) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			// Check if the order of the queue is correct
			queuePtr = &(data.companies.first->next->elem.jobs.elems[0].applicationsQueue);
			if (queuePtr->first->elem->id != 2 || queuePtr->first->next->elem->id != 4 || queuePtr->first->next->next->elem->id != 11 || queuePtr->first->next->next->next->elem->id != 12) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
		
		csv_free(&report);
		csv_free(&refReport);
	}
	end_test(test_section, "PR2_EX4_4", !failed);
	
	// Release all data
	api_freeData(&data);
	
	return passed;
}
