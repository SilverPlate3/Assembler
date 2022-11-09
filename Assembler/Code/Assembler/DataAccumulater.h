#ifndef DATAACCUMULATER_H_INCLUDED
#define DATAACCUMULATER_H_INCLUDED


typedef struct Node {
	struct Node* next;
	struct Node* previous;
	int value;
}Node;


typedef struct LinkedListMaster {
	struct Node* Head;
	struct Node* Tail;
	int counter;
} LinkedListMaster;



/*
	Add a node to the end of the linked list

	input: 
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Value to add to the linked list.

	Output: None

	Remarks: None
*/
void AddValueToEnd(LinkedListMaster* DC, int value_to_add);



/*
	Create a doubly linked list 

	input: None

	Output: Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.

	Remarks: Everything to do with the linkedlist is dynamically alocated.
*/
LinkedListMaster * CreateLinkedListMaster();



/*
	Create a Linked List node.

	input: Value that the new node will hold. 

	output: Pointer to the dynamiclly alocated Node instance.

	Remarks: Dynamically alocated Node instance
*/
Node* CreateNode(int value_to_add);



/*
	Cleans both of the linked list.

	input:
		[in, out] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in, out] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.

	Output: None

	Remarks: The linked lists are free'd and 2 new one are created.
*/
void ResetLinkedLists(LinkedListMaster** pLinked_list1, LinkedListMaster** pLinked_list2);

#endif // !DATAACCUMULATER_H_INCLUDED