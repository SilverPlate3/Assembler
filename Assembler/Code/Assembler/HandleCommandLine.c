#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ErrorHandling.h"
#include "UsedByMany.h"
#include "MemoryRelatedFunctions.h"

char** CreateListOfFiles(int argc, char** argv);
void CheckIfAllFilesExist(int argc, char** files_list);


char** CreateFilesListFromCommandLine(int argc, char** argv)
{
	if (argc <= 1)
		CrucialErrorExit("No argument was given. Exiting.....");

	char** files_list = CreateListOfFiles(argc, argv);	
	CheckIfAllFilesExist(argc, files_list);
	
	return files_list;
}



char** CreateListOfFiles(int argc, char** argv)
{
	char** files_list = (char**)AllocateArrayOfPointers(argc);

	for (int i = 1; i < argc; i++)
	{
		files_list[i - 1] = (char*)calloc(_MAX_PATH, sizeof(char));
		if (files_list[i - 1] == NULL)
			FreeArrayOfPointersBeforeCrucialExit(i - 1, files_list, "Calloc failed... ");

		snprintf(files_list[i - 1], _MAX_PATH, "%s.as", argv[i]);
	}

	return files_list;
}



void CheckIfAllFilesExist(int argc, char** files_list)
{
	errno_t result;
	for (int i = 0; i < argc-1; i++)
	{	
		FILE* f;

		result = fopen_s(&f, files_list[i], "r");
		if (result != 0)
			FreeArrayOfPointersBeforeCrucialExit(argc - 1, files_list, "Input file doesn't exist.  Exiting.....");

		fclose(f);
	}
}