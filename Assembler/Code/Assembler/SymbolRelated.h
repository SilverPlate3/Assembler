#ifndef SYMBOLRELATED_H_INCLUDED
#define SYMBOLRELATED_H_INCLUDED

#include "DataAccumulater.h"

#define MAX_SYMBOL_SIZE 32
#define TABLE_SIZE 2000
#define UNINITIALIZED_SYMBOL -1

typedef struct {
	char* name;
	int value;
}Symbol;



/*
	Adds a symbol to the hashtable, if possible.

	input: 
		[in] Hashtable 
		[in] Symbol to add to the Hashtable.

	Output: indication if worked.

	Remarks: It will exit the script if we calculate the hash of the symbol, to an index which alredy stores a differet symbol.
*/
int AddSymbol(Symbol* table[], Symbol* symbol);



/*
	Creates a Symbol instance

	input: 
		[in] address of a char array that will initiate the Symbol name attributre.
		[in] address of a integer that will initiate the Symbol value attributre.

	Output: Pointer to a dynamically allocated Symbol.

	Remarks: The value attribute might need to change in the future.
*/
Symbol* CreateSymbol(char * line, int value);


/*
	Checks if a string has the structure of a valid symbol, that is the first word of a line.

	input:
		[in] String that will be checked.
		[in] integer that tells the function to copy the error message if an error occurs. 

	Output: Boolean that indicates if the string is structure like a valid first word symbol. 

	Remarks: None.
*/
int IsValidSymbol__FirstWordSymbol(char* symbol_name, int* get_error_message);


/*
	Checks if a string has the structure of a valid symbol, that isn't the first word of the line.

	input:
		[in] String that will be checked.
		[in] integer that tells the function to copy the error message if an error occurs.

	Output: Boolean that indicates if the string is structure like a valid non first word symbol.

	Remarks: None.
*/
int IsValidSymbol__ArgumentSymbol(char* symbol_name, int get_error_message);


/*
	Checks if a symbol is in a table 

	input:
		[in] Needle 
		[in] Haystack

	Output: Boolean that indicates if the symbol is in the table.

	Remarks: None.
*/
int IsSymbolInTable(Symbol* symbol, Symbol* table[]);


/*
	Checks if a table contains a symbol with that name.

	input:
		[in] Needle
		[in] Haystack

	Output: Boolean that indicates if the table contains a symbol with that name.

	Remarks: None.
*/
int IsSymbolNameInTable(char* symbol_name, Symbol* table[]);


/*
	Sets the value of the specified symbol in a specified table.

	input:
		[in] Hashtable that hold the symbol.
		[in] Symbol that its value should be set.
		[in] Integer value that will be set. 

	Output: Value that indicates if the operation was succesfull.

	Remarks: None.
*/
int SetSymbolValue(Symbol* table[], Symbol* symbol, int value);


/*
	Checks if a two tables contain the same symbol. 

	input:
		[in] Hashtable.
		[in] Hashtable.
		[in] Symbol to search. 

	Output: value taht indicates if the symbol is in both values.  

	Remarks: None.
*/
int IsSymbolNameInBothTables(Symbol* table_1[], Symbol* table_2[], char* line);


/*
	Free a dynamically allocated symbol.

	input:
		[in] Symbol to free.

	Output: None.

	Remarks: None.
*/
void FreeSymbol(Symbol* symbol);


/*
	Search a symbol value by its name.

	input:
		[in] Name of symbol to search.
		[in] HashTable to search in.

	Output: The integer value of the symbol is the specified table.

	Remarks: None.
*/
int GetSymbolValueByName(char* symbol_name, Symbol* table[]);


/*
	Process a new symbol that should go to the ordinary symbols table. 

	input:
		[in] Symbol to process
		[in] .extern symbols Hashtable.
		[in] Ordinary symbols HashTable.
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.
		[in] Pointer to a struct that holds pointers to the Head and Tail nodes of a doubly linked list.

	Output: Value that indicates if the operation was succesfull.

	Remarks: If the operation faild, the symbol is free'd.
*/
int HandleNewOrdinarySymbol(Symbol* symbol, Symbol* Extrn[], Symbol* Ordinary[], LinkedListMaster* IC, LinkedListMaster* DC);


/*
	Fills the Enrty Hashtable values, and writes the values to the .ent output file.

	input:
		[in] .entry symbols Hashtable.
		[in] Ordinary symbols HashTable.

	Output: The integer value of the symbol is the specified table.

	Remarks: Throws an error if an uninitilized Entry symbol name isn't fount in the Ordinary HashTable.
*/
int EntrySymbolsConclusion(Symbol* Entry[], Symbol* Ordinary[]);

#endif //	!SYMBOLRELATED_H_INCLUDED