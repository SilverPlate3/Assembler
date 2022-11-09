#ifndef MEMORYRELATEDFUNCTIONS_H_INCLUDED
#define MEMORYRELATEDFUNCTIONS_H_INCLUDED

#include "DataAccumulater.h"
#include "SymbolRelated.h"

#define SafeFree(pointer) SmartFree((void**)&(pointer))
#define FreeArrayOfPointers(counter, pointer) DeallocateArrayOfPointers(counter, (void**)(pointer))


/*
	Reallocates 2D dynamic arrays

	input: 
		[in] 2D dynamic array.
		[in] new length needed. 

	output: Pointer of a new 2D dynamic array.

	Remarks: Returns NULL if reallocation failed
*/
void** ReallocationPointerOfPointer(void** buffer, unsigned int size);



/*
	 Deallocates a 2D dynamically alocated array. 

	 Input: 
		[in] 2D array length.
		[in] 2D dynamic array.

	 Output: None

	 Remarks: This function shouldn't be called directly, but should be called only by its Macro FreeArrayOfPointers()
*/
void DeallocateArrayOfPointers(int array_length, void** array);


/*
	 Deallocates all the Symbols in a Symbol HashTable

	 Input:
		[in] Hashtable of Symbols

	 Output: None

	 Remarks: Free's only the symbols. The table itself isn't dynammically allocated. 
*/
void FreeTable(Symbol* table[]);


/*
	 Deallocates a dynamically alocated doubly linked list. 

	 Input:
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.

	 Output: None

	 Remarks: Free's both the linked kist and the structure that holded it.
*/
void FreeLinkedList(LinkedListMaster* linked_list);


/*
	 Allocates a 2D dynamically alocated array.

	 Input:
		[in] Needed array size.

	 Output: void 2D array.

	 Remarks: The array should be explicitly casted by the caller. 
*/
void** AllocateArrayOfPointers(int array_length);


/*
	 Trying to Refrence Null to every pointer after its free'd  

	 Input:
		[in, out] Pointer to the pointer we want to free.

	 Output: None

	 Remarks: This function shouldn't be called directly, but should be called only by its Macro SafeFree()
*/
void SmartFree(void** pointer);

#endif // !MEMORYRELATEDFUNCTIONS_H_INCLUDED