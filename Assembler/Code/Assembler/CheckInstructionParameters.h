#ifndef CHECKINSTRUCTIONPARAMETERS_H_INCLUDED
#define CHECKINSTRUCTIONPARAMETERS_H_INCLUDED

#include "DataAccumulater.h"
#include "SymbolRelated.h"

enum Instructions { DOT_DATA = 1, DOT_STRING, DOT_ENTRY, DOT_EXTERN, OTHER };


/*
	Calling the correct function for handling the current guiding instruction. 

	Input: [in, out] Doubly linked list that holds the numerical equvilents of the guiding instruction parameters.
		   [in, out] Pointer to a Hashtable that holds instances of Symbol 
		   [in, out] Pointer to a Hashtable that holds instances of Symbol
		   [in, out] Counter of the doubly linked list. 
		   [in]	     Line that holds the parameters 
		   [in]		 Type of guiding instruction.
		   [in]      Number that represents the assembler iteration number.

	Output: Indication if sub functions worked or not.

	Remarks: The function that will eventually be called to handle the guiding instruction line, is chosen by iteration_number & type_of_guiding_instruction.
*/

int GuidingInstructionFactory(LinkedListMaster* DC, Symbol* Extrn[], Symbol* Entry[], char* line, int type_of_guiding_instruction, int iteration_number);



/*
	Checks the Guiding instruction type.

	input: string that represents the guiding instruction. 

	output: number that represents a guiding instruction.

	Remarks: returns an enum instance called "OTHER" if it isn't a valid guiding instruction. 
*/
int GetGuidingInstructionType(char* line);



#endif // !CHECKINSTRUCTIONPARAMETERS_H_INCLUDED