#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>

#include "ErrorHandling.h"
#include "UsedByMany.h"
#include "CheckInstructionParameters.h"
#include "AssemblyKeyWords.h"

int GuidingInstructionFirstIteration(LinkedListMaster* DC, Symbol* Extrn[], Symbol* Entry[], char* line, int type_of_guiding_instruction);
int GuidingInstructionSecondIteration(LinkedListMaster* DC, char* line, int type_of_guiding_instruction);
int HandleDotData(LinkedListMaster* DC, char* line);
int HandleDotString(LinkedListMaster* DC, char* line);
int HandleDotEntry(Symbol* Extrn[], char* line);
int HandleDotExtern(Symbol* Extrn[], char* line);
int WhatGuidingInstruction(char* line);


int GuidingInstructionFactory(LinkedListMaster* DC, Symbol* Extrn[], Symbol* Entry[], char* line, int type_of_guiding_instruction, int iteration_number)
{
	int result = 0;

	if (IsFirstIteration(iteration_number))
		return  GuidingInstructionFirstIteration(DC, Extrn, Entry, line, type_of_guiding_instruction);

	else
		return GuidingInstructionSecondIteration(DC, line, type_of_guiding_instruction);
}



int GuidingInstructionFirstIteration(LinkedListMaster* DC, Symbol* Extrn[], Symbol* Entry[], char* line, int type_of_guiding_instruction)
{
	char line_copy[LINE_MAX_SIZE] = {0};
	strcpy_s(line_copy, LINE_MAX_SIZE, line);

	int result = 0;

	if(type_of_guiding_instruction == DOT_DATA)
		result = HandleDotData(DC, line_copy);

	else if(type_of_guiding_instruction == DOT_STRING)
		result = HandleDotString(DC, line_copy);

	else
	{
		if (type_of_guiding_instruction == DOT_ENTRY)
			result = HandleDotEntry(Entry, line_copy);

		else
			result = HandleDotExtern(Extrn, line_copy);

		if (result != NULL)
			if (IsSymbolNameInBothTables(Entry, Extrn, line_copy))
				result = NULL;
	}

	if(result == NULL)
		strcpy_s(line, LINE_MAX_SIZE, line_copy);

	return result;
}



int GuidingInstructionSecondIteration(LinkedListMaster* DC, char* line, int type_of_guiding_instruction)
{
	int result = 0;
	char line_copy[LINE_MAX_SIZE] = { 0 };
	strcpy_s(line_copy, LINE_MAX_SIZE, line);

	if (type_of_guiding_instruction == DOT_DATA)
		result = HandleDotData(DC, line_copy);

	else if (type_of_guiding_instruction == DOT_STRING)
		result = HandleDotString(DC, line_copy);

	else
		return 1;

	if (result == NULL)
		strcpy_s(line, LINE_MAX_SIZE, line_copy);

	return result;
}



int HandleDotData(LinkedListMaster* DC, char *line)
{
	if (!CheckComma(line))
		return NULL;

	char delimiters[] = ",";
	char* next_token = NULL;
	char* token = strtok_s(line, delimiters, &next_token);

	int number = 0;
	while (token != NULL)
	{
		char temp_token[LINE_MAX_SIZE] = { 0 };
		strcpy_s(temp_token, LINE_MAX_SIZE, token);

		if ((strlen(temp_token) == 1) && (temp_token[0] == '0'))
			number = 0;

		else
		{
			number = IsValidNumber(temp_token);
			if (number == NULL)
			{
				strcpy_s(line, LINE_MAX_SIZE, temp_token);
				return NULL;
			}

		}

		AddValueToEnd(DC, number);

		token = strtok_s(NULL, delimiters, &next_token);
		if (token == NULL)
			break;
	}
	return 1;
}



int HandleDotString(LinkedListMaster* DC, char* line)
{
	int i = 0;
	if (line[i] == '"')
	{
		i++;
		while (i < strlen(line))
		{
			if (i == strlen(line) - 1)
			{
				i++;

				if (!DoesStringEndsWithCharacter(line, '"'))
				{
					strcpy_s(line, LINE_MAX_SIZE, "String doesn't end with \" ");
					return NULL;
				}
			}

			else if (isprint(line[i]))
			{
				AddValueToEnd(DC, line[i]);
				i++;
			}
			else
			{
				strcpy_s(line, LINE_MAX_SIZE, "Parameter is not a ASCII character");
				return NULL;
			}
		}
		AddValueToEnd(DC, 0);
	}

	else
	{
		strcpy_s(line, LINE_MAX_SIZE, "String doesn't start with \"");
		return NULL;
	}

	return 1;
}



int HandleDotExtern(Symbol* Extrn[], char* line)
{
	if (IsValidSymbol__ArgumentSymbol(line, TRUE) == NULL)
		return NULL;

	Symbol* symbol = CreateSymbol(line, UNINITIALIZED_SYMBOL);

	if (AddSymbol(Extrn, symbol) == NULL)
	{
		strcpy_s(line, LINE_MAX_SIZE, symbol->name);
		return NULL;
	}

	return 1;
}



int HandleDotEntry(Symbol* Entry[], char * line)
{
	if (IsValidSymbol__ArgumentSymbol(line, TRUE) == NULL)
		return NULL;
	
	Symbol * symbol = CreateSymbol(line, UNINITIALIZED_SYMBOL);

	if (AddSymbol(Entry, symbol) == NULL)
	{
		strcpy_s(line, LINE_MAX_SIZE, symbol->name);
		return NULL;
	}

	return 1;
}



int GetGuidingInstructionType(char* line)
{
	int type_of_guiding_instruction = WhatGuidingInstruction(line);
	
	if (type_of_guiding_instruction != NULL)
		return type_of_guiding_instruction;

	else
	{
		strcpy_s(line, LINE_MAX_SIZE, "Illegal Guiding instruction");
		return OTHER;
	}
}



int WhatGuidingInstruction(char* line)
{
	if (IsGuidingInstruction(line) == FALSE)
		return NULL;

	for (int i = 0; i < NUMBER_OF_GUIDING_INSTRUCTIONS; i++)
	{
		if (strcmp(GUIDING_INSTRUCTIONS[i], line) == 0)
			return i + 1; // Look at "enum Instructions"
	}
}







