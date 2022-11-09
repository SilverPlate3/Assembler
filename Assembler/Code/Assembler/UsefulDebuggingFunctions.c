#include <stdio.h>
#include <stdlib.h>

#include "UsefulDebuggingFunctions.h"


void PrintTable(Symbol* Table[], char table_name[])
{
	printf("\n======================================  %s start  =======================================\n", table_name);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (Table[i] != NULL)
		{
			printf("\n[%d] Symbol: %s   Value: %d", i, Table[i]->name, Table[i]->value);
		}
	}
	printf("\n======================================  %s end  =======================================\n", table_name);
}


void PrintLinkedList(LinkedListMaster* linked_list, char list_name[])
{
	printf("\n======================================  %s start  =======================================\n", list_name);
	Node* current_node = linked_list->Head;
	int counter = 0;
	
	while (current_node != NULL)
	{
		printf("[%d]  %d", counter, current_node->value);
		current_node = current_node->next;
		counter++;
	}

	printf("\n======================================  %s end  =======================================\n", list_name);
}