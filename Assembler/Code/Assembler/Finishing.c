#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Finishing.h"
#include "MemoryRelatedFunctions.h"
#include "OutputFiles.h"

void DeleteFiles();


void CleanAll(Symbol* Extrn[], Symbol* Entry[], Symbol* Ordinary[],
	LinkedListMaster* IC, LinkedListMaster* DC,
	int number_of_important_lines, important_line** important_file_lines, int line_parts_counter, char** line_parts)
{
	CleanMemory(Extrn, Entry, Ordinary,
		IC, DC,
		number_of_important_lines, important_file_lines, line_parts_counter, line_parts);

	DeleteFiles();
}


void CleanMemory(Symbol* Extrn[], Symbol* Entry[], Symbol* Ordinary[],
	LinkedListMaster* IC, LinkedListMaster* DC, 
	int number_of_important_lines, important_line** important_file_lines, int line_parts_counter, char ** line_parts)
{
	FreeTable(Extrn);
	FreeTable(Entry);
	FreeTable(Ordinary);

	FreeLinkedList(IC);
	FreeLinkedList(DC);

	FreeArrayOfPointers(number_of_important_lines, important_file_lines);
	if(line_parts != NULL)
		FreeArrayOfPointers(line_parts_counter, line_parts);
}


void DeleteFiles()
{
	DeleteExtFile();
	DeleteEntFile();
}