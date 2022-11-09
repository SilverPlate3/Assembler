#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "MemoryRelatedFunctions.h"
#include "ErrorHandling.h"


void** ReallocationPointerOfPointer(void** buffer, unsigned int size)
{
	void** temp = (void**)realloc(buffer, size * sizeof(void*));
	if (temp == NULL)
	{
		return NULL;
	}

	return temp;
}



void** AllocateArrayOfPointers(int array_length)
{
	void** array = (void**)calloc(array_length, sizeof(void*));
	if (array == NULL)
		CrucialErrorExit("Calloc failed, exiting..... ");

	return array;
}



void DeallocateArrayOfPointers(int array_length, void** array)
{
	if (array == NULL)
		return;

	for (int i = 0; i < array_length; i++)
		SafeFree(array[i]);

	SafeFree(array);
}



void FreeLinkedList(LinkedListMaster* linked_list)
{
	Node* current_node = linked_list->Head;
	while (current_node != NULL)
	{
		Node* next_node = current_node->next;
		SafeFree(current_node);
		current_node = next_node;
	}

	SafeFree(linked_list);
}



void FreeTable(Symbol* table[])
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i] != NULL)
			FreeSymbol(table[i]);
	}
	table = NULL;
}



void SmartFree(void** pointer)
{
	if (pointer != NULL && *pointer != NULL)
	{
		free(*pointer);
		*pointer = NULL;
	}
}


