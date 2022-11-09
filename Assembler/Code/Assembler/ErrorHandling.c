#include <stdio.h>
#include <stdlib.h>

#include "ErrorHandling.h"
#include "UsedByMany.h"
#include "OutputFiles.h"
#include "MemoryRelatedFunctions.h"

void ErrorFlagTrue(int* error_flag);



void ReportInputError(char* error_message, int line_number, int * error_flag)
{
	printf("\nError:  Line %d.  %s", line_number, error_message);
	ErrorFlagTrue(error_flag);
}



void ErrorFlagTrue(int* error_flag)
{
	*error_flag = TRUE;
}



DeallocateArrayOfPointersBeforeCrucialExit(int array_counter, void** array_of_pointers, char error_message[])
{
	FreeArrayOfPointers(array_counter, array_of_pointers);
	CrucialErrorExit(error_message);
}



void CrucialErrorExit(const char* error_message)
{
	printf("\n%s", error_message);
	DeleteExtFile();
	exit(EXIT_FAILURE);
}

