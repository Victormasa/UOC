/*
 * File:        main.c
 * Description: Contains the main functionality for the application
 */
 
#include <stdio.h>

#include "main.h"


/* 
 * Function:    main
 * Description: Application entry method
 * Arguments:   ---
 * Returns:     0 always.
 */
int main(int argc, char **argv)
{
	int version;
	version = getVersion();
	
	printf("\n");
	printf("UOC email: vmartinezsanto@uoc.edu\n");
	printf("Program Version: %d\n", version);
	printf("\n");
	printf("Press any key to continue\n");
	getchar();
	return 0;
}


/*
 * Function: 	getVersion
 * Description: Obtains the version of the application
 * Arguments:   ---
 * Returns: 	The release version of the application
 */
int getVersion()
{
#ifndef NDEBUG
	printf("\n[DEBUG] - Getting library version...\n");
#endif	
	return VERSION;
}