#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "ErrorHandling.h"
#include "SymbolRelated.h"
#include "UsedByMany.h"
#include "AssemblyKeyWords.h"
#include "CommandRelated.h"
#include "MachineCode.h"
#include "OutputFiles.h"
#include "MemoryRelatedFunctions.h"

int FindNoneAlphaNumeric(char* line);
int IsValidSymbol__Main(char* symbol_name);
int GetValueOfSymbolFromTable(Symbol* symbol, Symbol* table[]);
int CopySymbolValueFromOrdinaryTable(Symbol* symbol, Symbol* Ordinary[]);
int IsSymbolInOneOfTables(Symbol* symbol, Symbol* table1[], Symbol* table2[]);
int HashSymbol(Symbol* symbol);
int IsSymbolValue(Symbol* table[], int index);



Symbol* CreateSymbol(char * line, int value)
{
	Symbol* symbol = (Symbol*)calloc(1, sizeof(Symbol));
	if (symbol == NULL)
		CrucialErrorExit("Calloc failed....");

	char* str = (char*)calloc(MAX_SYMBOL_SIZE, sizeof(char));
	if (str == NULL)
		CrucialErrorExit("Calloc failed....");
	strcpy_s(str, MAX_SYMBOL_SIZE, line);

	symbol->name = str;
	symbol->value = value;

	return symbol;
}



int AddSymbol(Symbol* table[], Symbol* symbol)
{
	int index = HashSymbol(symbol);
	if (IsSymbolInTable(symbol, table))
	{
		strcpy_s(symbol->name, MAX_SYMBOL_SIZE, "Symbol exists already!");
		return NULL;
	}

	else
	{
		table[index] = symbol;
		return TRUE;
	}
}



int IsSymbolInTable(Symbol* symbol, Symbol* table[])
{
	int index = HashSymbol(symbol);

	if (table[index] == NULL)
		return FALSE;

	else if (strcmp(symbol->name, table[index]->name) == 0)
		return TRUE;

	else
		CrucialErrorExit("Hashtable navigation error! Not related to input file");
}



int IsSymbolNameInTable(char* symbol_name, Symbol* table[])
{
	Symbol* symbol = CreateSymbol(symbol_name, UNINITIALIZED_SYMBOL);

	int result = IsSymbolInTable(symbol, table);
	FreeSymbol(symbol);
	return result;
}



int IsSymbolInOneOfTables(Symbol* symbol, Symbol* table1[], Symbol* table2[])
{
	if (IsSymbolInTable(symbol, table1) || IsSymbolInTable(symbol, table2))
		return TRUE;

	return FALSE;
}



int HashSymbol(Symbol* symbol)
{
	// Hashing algorythm 
	int length = strlen(symbol->name);
	unsigned int hash_value = 0;
	for (int i = 0; i < length; i++)
	{
		hash_value += symbol->name[i];
		hash_value *= symbol->name[i];
		hash_value += (symbol->name[i] + 0);
		hash_value *= (symbol->name[i] + 0);
	}

	return (hash_value % TABLE_SIZE);
}



int IsValidSymbol__FirstWordSymbol(char* symbol_name, int* get_error_message)
{
	char symbol_name_copy[LINE_MAX_SIZE];
	strcpy_s(symbol_name_copy, LINE_MAX_SIZE, symbol_name);
	int symbol_name_is_valid = TRUE;

	if (!IsValidSymbol__Main(symbol_name_copy))
		symbol_name_is_valid = FALSE;

	else if (FindNoneAlphaNumeric(symbol_name_copy) != (strlen(symbol_name_copy) - 1))
	{
		strcpy_s(symbol_name_copy, LINE_MAX_SIZE, "Symbol contains none-alphanumeric characters");
		symbol_name_is_valid = FALSE;
	}

	else if (!DoesStringEndsWithCharacter(symbol_name_copy, ':'))
	{
		strcpy_s(symbol_name_copy, LINE_MAX_SIZE, "Symbol doesn't end with a colon");
		symbol_name_is_valid = FALSE;
	}

	if (get_error_message)
		strcpy_s(symbol_name, LINE_MAX_SIZE, symbol_name_copy);

	return symbol_name_is_valid;
}



int IsValidSymbol__ArgumentSymbol(char* symbol_name, int get_error_message)
{
	char symbol_name_copy[LINE_MAX_SIZE] = {0};
	strcpy_s(symbol_name_copy, LINE_MAX_SIZE, symbol_name);
	int symbol_name_is_valid = TRUE;

	if (!IsValidSymbol__Main(symbol_name_copy))
		symbol_name_is_valid = FALSE;

	else if (FindNoneAlphaNumeric(symbol_name_copy))
	{
		strcpy_s(symbol_name_copy, LINE_MAX_SIZE, "Symbol contains none-alphanumeric characters");
		symbol_name_is_valid = FALSE;
	}

	if (get_error_message)
		strcpy_s(symbol_name, LINE_MAX_SIZE, symbol_name_copy);

	return symbol_name_is_valid;
}



int IsValidSymbol__Main(char* symbol_name)
{
	if (IsStringLongerThenNumber(symbol_name, MAX_SYMBOL_SIZE))
		strcpy_s(symbol_name, LINE_MAX_SIZE, "Symbol is to long");

	else if (isalpha(symbol_name[0]) == 0)
		strcpy_s(symbol_name, LINE_MAX_SIZE, "Symbol doesn't start with an alphabet char");

	else if (IsBuiltInKeyword(symbol_name))
		strcpy_s(symbol_name, LINE_MAX_SIZE, "Symbol named after a built-in assembly keyword");

	else
		return TRUE;

	return FALSE;
}



int IsSymbolValue(Symbol* table[], int index)
{
	return (table[index]->value == UNINITIALIZED_SYMBOL) ? FALSE : TRUE;
}



int SetSymbolValue(Symbol* table[], Symbol* symbol, int value)
{
	int index = HashSymbol(symbol);

	if (IsSymbolValue(table, index) == FALSE)
	{
		table[index]->value = value;
		return TRUE;
	}
	
	return NULL;
}


int GetSymbolValueByName(char* symbol_name, Symbol* table[])
{
	Symbol* symbol = CreateSymbol(symbol_name, UNINITIALIZED_SYMBOL);
	int index = HashSymbol(symbol);
	FreeSymbol(symbol);

	return table[index]->value;
}


int IsSymbolNameInBothTables(Symbol* table_1[], Symbol* table_2[], char * line)
{
	if (IsSymbolNameInTable(line, table_1) && IsSymbolNameInTable(line, table_2))
	{
		strcpy_s(line, LINE_MAX_SIZE, "Symbol is in both tables");
		return TRUE;
	}

	return FALSE;
}



int FindNoneAlphaNumeric(char* line)
{
	int i = 0;
	while (line[i] != 0)
	{
		if (isalnum(line[i]) == 0)
		{
			return i;
		}

		i++;
	}

	return 0;
}



void FreeSymbol(Symbol* symbol)
{
	SafeFree(symbol->name);
	SafeFree(symbol);
}



int HandleNewOrdinarySymbol(Symbol* symbol, Symbol* Extrn[], Symbol* Ordinary[], LinkedListMaster* IC, LinkedListMaster* DC)
{
	if (!IsSymbolInOneOfTables(symbol, Extrn, Ordinary))
	{
		AddSymbol(Ordinary, symbol);
		SetSymbolValue(Ordinary, symbol, GetCurrentMemoryAddress(IC, DC));
		return TRUE;
	}
	else
	{
		FreeSymbol(symbol);
		return FALSE;
	}
}



int EntrySymbolsConclusion(Symbol* Entry[], Symbol* Ordinary[])
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (Entry[i] != NULL)
		{
			if (CopySymbolValueFromOrdinaryTable(Entry[i], Ordinary) == FALSE)
				return FALSE;

			AddToEntryOutputFile(Entry[i]->name, Entry[i]->value);
		}
	}
	return TRUE;
}



int CopySymbolValueFromOrdinaryTable(Symbol* symbol, Symbol* Ordinary[])
{
	if (symbol->value == UNINITIALIZED_SYMBOL)
	{
		int symbol_value = GetValueOfSymbolFromTable(symbol, Ordinary);
		if (symbol_value == FALSE)
			return FALSE;

		symbol->value = symbol_value;
	}

	return TRUE;
}



int GetValueOfSymbolFromTable(Symbol* symbol, Symbol* table[])
{
	if (!IsSymbolInTable(symbol, table))
		return FALSE;

	return table[HashSymbol(symbol)]->value;
}
