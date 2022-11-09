#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ErrorHandling.h"
#include "DataAccumulater.h"
#include "UsedByMany.h"
#include "SymbolRelated.h"
#include "MemoryRelatedFunctions.h"

LinkedListMaster* ResetLinkedListMaster(LinkedListMaster* linked_list);


Node* CreateNode(int value_to_add)
{
	Node* node = (Node*)calloc(1, sizeof(Node));
	if (node == NULL)
		CrucialErrorExit("[CreateNode] Calloc failed....");

	node->next = NULL;
	node->value = value_to_add;
	node->previous = NULL;

	return node;
}


void AddValueToEnd(LinkedListMaster* linked_list, int value_to_add)
{
	if (linked_list->counter == 0)
	{
		linked_list->Head->value= value_to_add;
	}
	else 
	{
		Node* new_node = CreateNode(value_to_add);

		if (linked_list->counter == 1)
		{
			Node* current_node = linked_list->Head;

			current_node->next = new_node;
			new_node->previous = current_node;
			linked_list->Tail = new_node;
		}
		else
		{
			new_node->next = linked_list->Tail->next;
			new_node->previous = linked_list->Tail;
			linked_list->Tail->next = new_node;
			linked_list->Tail = new_node;
		}
	}
	
	linked_list->counter++;
}	



LinkedListMaster * CreateLinkedListMaster()
{
	LinkedListMaster* L1 = (LinkedListMaster*)calloc(1, sizeof(LinkedListMaster));
	L1->Head = CreateNode(5555);
	L1->counter = 0;
	if (L1 == NULL || L1->Head == NULL )
		CrucialErrorExit("Calloc failed....");

	return L1;
}



void ResetLinkedLists(LinkedListMaster** pLinked_list1, LinkedListMaster** pLinked_list2)
{
	*pLinked_list1 = ResetLinkedListMaster(*pLinked_list1);
	*pLinked_list2 = ResetLinkedListMaster(*pLinked_list2);
}


LinkedListMaster* ResetLinkedListMaster(LinkedListMaster * linked_list)
{
	FreeLinkedList(linked_list);
	linked_list = CreateLinkedListMaster();
	return linked_list;
}