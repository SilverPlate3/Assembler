#ifndef FINISHING_H_INCLUDED
#define FINISHING_H_INCLUDED

#include "ParsingFiles.h"
#include "SymbolRelated.h"
#include "DataAccumulater.h"


/*
	Clears the system from almost every trace that the Assembler leaves. 
	Gets read of the output files, of that input file and dynamiclly alocated memory of that input file. 

	input:
		[in] Hashtable of Symbols
		[in] Hashtable of Symbols
		[in] Hashtable of Symbols
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Number that represents the length of the important_file_lines array
		[in] Array of strings that represent the valuable lines in the input file. 
		[in] Number that represents the length of the line_parts array
		[in] Array of strings that represent the current input file line parts

	Output: None.

	Remarks: Clears the files .ent and .ext
	         The only dynamiclly alocated memory that is left is the array of input files.
*/
void CleanAll(Symbol* Extrn[], Symbol* Entry[], Symbol* Ordinary[],
	LinkedListMaster* IC, LinkedListMaster* DC,
	int number_of_important_lines, important_line** important_file_lines, int line_parts_counter, char** line_parts);


/*
	Clears almost all the dynamically allocated memory the assembler allocated.

	input:
		[in] Hashtable of Symbols
		[in] Hashtable of Symbols
		[in] Hashtable of Symbols
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Number that represents the length of the important_file_lines array
		[in] Array of strings that represent the valuable lines in the input file.
		[in] Number that represents the length of the line_parts array
		[in] Array of strings that represent the current input file line parts

	Output: None.

	Remarks: The only dynamiclly alocated memory that is left is the array of input files.
*/
void CleanMemory(Symbol* Extrn[], Symbol* Entry[], Symbol* Ordinary[],
	LinkedListMaster* IC, LinkedListMaster* DC,
	int number_of_important_lines, important_line** important_file_lines, int line_parts_counter, char** line_parts);


#endif // !FINISHING_H_INCLUDED