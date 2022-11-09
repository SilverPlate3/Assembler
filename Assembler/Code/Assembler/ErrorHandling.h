#ifndef ERRORHANDLING_H_INCLUDED
#define ERRORHANDLING_H_INCLUDED

#define FreeArrayOfPointersBeforeCrucialExit(counter, pointer, string) DeallocateArrayOfPointersBeforeCrucialExit(counter, (void**)(pointer), string)

/*
	 Print error and exit.

	 Input: string to print
 
	 Output: None

	 Remarks: Exits without cleaning memory but deleteing output files.
*/
void CrucialErrorExit(const char* error);



/*
	Print error and switch the error flag to true. 

	Input: [in] error string
		   [in] line number
		   [out] error flag

	Output: None

	Remarks: When the error flag is true, the assembler won't proceed to the second phase. 
*/
void ReportInputError(char* error_message, int line_number, int* error_flag);



/*
	Free array of pointers and the CrucialErrorExit().

	input:
		[in] length of array
		[in] void double pointer to an array that need to be free'd.
		[in] error string

	Output: None.

	Remarks: This function is called through a pinter in order to explicitly converte the array type to void **
*/
DeallocateArrayOfPointersBeforeCrucialExit(int array_counter, void** array_of_pointers, char error_message[]);



#endif // !ERRORHANDLING_H_INCLUDED