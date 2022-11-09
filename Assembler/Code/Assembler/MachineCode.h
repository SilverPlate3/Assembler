#include "SymbolRelated.h"
#include "DataAccumulater.h"

#ifndef MACHINECODE_H_INCLUDED
#define MACHINECODE_H_INCLUDED

#define ARE_ABSOLUTE 0;
#define ARE_EXTERNAL 1;
#define ARE_RELOCATABLE 2;

#define DESTINATION_OPERAND_BIT_BASE 2;
#define COMMAND_BIT_BASE 5;
#define SOURCE_OPERAND_BIT_BASE 9;
#define SOURCE_OPERAND_WHEN_TWO_REGISTERS_BIT_BASE 7;

#define REGISTER_TYPE_OPERAND_BINARY_REPRESENTATION 5;
#define NUMBER_TYPE_OPERAND_BINARY_REPRESENTATION 1;
#define SYMBOL_TYPE_OPERAND_BINARY_REPRESENTATION 3;

#define BASE_ADDRESS 100;


/*
	Creates the integer values that correspond to input file lines with commands. 
	Inserts the integer values to the correct doubly linked list.

	input:
		[in] Number that represents the length of the line_parts array
		[in] Array of strings that represent the current input file line parts
		[in, out] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Hashtable of Symbols
		[in] Hashtable of Symbols

	Output: Boolean that indicates the function success.

	Remarks: None. 
*/
int MachineCodeFunctionsConductor(int line_parts_counter, char** line_parts, LinkedListMaster* IC, LinkedListMaster* DC, Symbol* Extrn[], Symbol* Ordinary[], int iteration_number);


/*
	Calculates the current memory address.

	input:
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.

	Output: The integer value that represents the current memory address. 

	Remarks: The calculation: IC->counter + DC->counter + 100
*/
int GetCurrentMemoryAddress(LinkedListMaster* IC, LinkedListMaster* DC);

#endif //!MACHINECODE_H_INCLUDED