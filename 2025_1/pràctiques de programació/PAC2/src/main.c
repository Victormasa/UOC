#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "csv.h"
#include "job.h"

int main(int argc, char** argv)
{
    tCSVData test_data;
    int i;
    tPerson person;
    tPeople people;
    tJob job;
    tJob job2;
    tJobs jobs;
    char buffer[BUFFER_SIZE];

    const char* test_people = "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954\n" \
        "33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867\n" \
        "55565432Z;Nils;Gustaf Dalen;555123123;nils.gustaf@example.com;Picadilly street, 123;12345;25/11/1972\n" \
        "98765432J;Jean Baptiste;Perrin;999654654;jean.perrin@example.com;Champs-Elysees, 44;77777;12/01/1983\n" \
        "12345672C;Anne;Huiller;666789789;anne.huiller@example.com;rue percebe, 125;22222;12/01/1969";
   
    const char* test_jobs = "1;Junior software developer;My Company;1;01/10/2025;20/11/2025;20000;35000\n" \
        "2;Chef assistant;Cooking Restaurant;1;15/11/2025;15/02/2026;-1;25000\n" \
        "3;Course instructor;UOC;2;15/10/2025;31/10/2025;-1;-1\n" \
        "4;Senior software developer;My Company;1;15/10/2025;15/12/2025;30000;-1\n" \
        "4;Senior software developer;My Company;1;15/10/2025;15/12/2025;30000;-1\n" \
        "5;Chef;Cooking Restaurant;2;15/10/2025;31/10/2025;20000;45000\n" \
        "6;Junior English Teacher;My Academy;2;15/10/2025;31/10/2025;15000;-1\n" \
        "6;English Teacher;My Academy;1;07/08/2025;01/11/2025;-1;16500\n" \
        "6;English Teacher;My Academy;1;07/08/2025;01/11/2025;-1;19500";

    const char* test_jobs2 = "7;Course instructor;UOC;10;01/01/2026;31/12/2026;-1;-1";

    // Read people data
    csv_init(&test_data);
    csv_parse(&test_data, test_people, "PEOPLE");

    // Initialize people data
    people_init(&people);

    // Add people data
    for (i = 0; i < csv_numEntries(test_data); i++) {
        // Fills a person with all information
        person_parse(&person, csv_getEntry(test_data, i)[0]);
        // Add new person to the list (table) of people
        people_add(&people, person);
    }

    // Print current people
    printf("People:\n");
    people_print(people);

    // Remove people data
    csv_free(&test_data);

    // Read job data
    csv_init(&test_data);
    csv_parse(&test_data, test_jobs2, "JOB");

    // Copy a job
    job_parse(&job, csv_getEntry(test_data, 0)[0]);
    job_cpy(&job2, job);

    // Print duplicated job
    printf("\nDuplicated job:\n");
    job_get(job2, buffer);
    printf("%s\n", buffer);

    // Remove job data
    csv_free(&test_data);

    // Read job data
    csv_init(&test_data);
    csv_parse(&test_data, test_jobs, "JOB");

    // Initialize jobs data
    jobs_init(&jobs);

    // Add jobs data
    for (i = 0; i < csv_numEntries(test_data); i++) {
        job_parse(&job, csv_getEntry(test_data, i)[0]);
        jobs_add(&jobs, job);
    }

    // Print current jobs
    printf("\nJobs before deleting the one with id = 2:\n");
    jobs_print(jobs);
    
	// Remove a job
	jobs_del(&jobs, 2);    

    // Print current jobs
    printf("\nJobs after deleting the one with id = 2:\n");
    jobs_print(jobs);

    // Remove jobs data
    csv_free(&test_data);
    
    jobs_free(&jobs);

    printf("\nPress key to end...\n");
    getchar();
    return 0;
}
