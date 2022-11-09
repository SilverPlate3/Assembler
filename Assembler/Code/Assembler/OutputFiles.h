#ifndef OUTPUTFILES_H_INCLUDED
#define OUTPUTFILES_H_INCLUDED

#include "DataAccumulater.h" 

#define EXTERN_OUTPUT_FILE_EXTENSTION ".ext"
#define ENTRY_OUTPUT_FILE_EXTENSTION ".ent"
#define OBJECT_OUTPUT_FILE_EXTENSTION ".ob"

extern char input_file[_MAX_PATH];

/*
	 Adds an .extern symbol name and the corresponding value to the .ext output file.

	 Input:
		[in] string that represents symbol name
		[in] int that represents the value that it should get in the .ext output file 

	 Output: None

	 Remarks: Many instances of the same symbol can be added to the file. The value is calculated: value = {IC after adding it binary equivalent} + DC.counter + 100
*/
void AddToExternOutputFile(char* symbol_name, int symbol_value);


/*
	 Adds an .entry symbol name and the corresponding value to the entry output file.

	 Input:
		[in] string that represents symbol name
		[in] int that represents the value that it should get in the .ext output file

	 Output: None

	 Remarks: Only one instance of the same symbol can be added to the file. The value is calculated: value = {IC after adding it binary equivalent} + DC.counter + 100
*/
void AddToEntryOutputFile(char* symbol_name, int symbol_value);


/*
	 Deletes the .ext output file

	 Input:None

	 Output: None

	 Remarks: None 
*/
void DeleteExtFile();


/*
	 Deletes the rnt output file

	 Input:None

	 Output: None

	 Remarks: None
*/
void DeleteEntFile();


/*
	 Calculates the base 64 that the .ob output file should hold and writes it.

	 Input:N
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.

	 Output: None

	 Remarks: Will only be created if the two assembler iterations work. 
*/
void CreateObOutputfile(LinkedListMaster* IC, LinkedListMaster* DC);

#endif //!OUTPUTFILES_H_INCLUDED