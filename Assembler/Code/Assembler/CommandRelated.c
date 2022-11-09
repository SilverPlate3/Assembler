#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "UsedByMany.h"
#include "AssemblyKeyWords.h"
#include "CommandRelated.h"
#include "SymbolRelated.h"
#include "CheckInstructionParameters.h"

int IsNumberOfCommandArgumentsCorrect__WithoutSymbol(char* command, int line_parts);
int AreCommandArgumentsValid(int line_parts_counter, char** line_parts);
int GetExpectedNumberOfCommandArguments(int command_type);
int IsZeroOperandsCommand(char* command);
int IsOneOperandsCommand(char* command);
int IsTwoOperandsCommand(char* command);


char* ZERO_OPERANDS_COMMANDS[NUMBER_OF_ZERO_OPERANDS_COMMANDS] =
{
	"rts",
	"stop"
};

char* ONE_OPERANDS_COMMANDS[NUMBER_OF_ONE_OPERANDS_COMMANDS] =
{
	"not",
	"clr",
	"inc",
	"dec",
	"jmp",
	"bne",
	"red",
	"prn",
	"jsr"
};

char* TWO_OPERANDS_COMMANDS[NUMBER_OF_TWO_OPERANDS_COMMANDS] =
{
	"mov",
	"cmp",
	"add",
	"sub",
	"lea"
};



int IsCommandArguments(int line_parts_counter, char** line_parts)
{
	if (!IsNumberOfCommandArgumentsCorrect__WithoutSymbol(line_parts[0], line_parts_counter))
	{
		strcpy_s(line_parts[0], LINE_MAX_SIZE, "Wrong number of command arguments");
		return FALSE;
	}

	if(!AreCommandArgumentsValid(line_parts_counter, line_parts))
	{
		strcpy_s(line_parts[0], LINE_MAX_SIZE, "Command argument is illigal");
		return FALSE;
	}

	return TRUE;
}



int IsNumberOfCommandArgumentsCorrect__WithoutSymbol(char* command, int line_parts)
{
	int command_part = 1;

	int command_type = FindCommandType(command);
	int expected_number_of_arguments = GetExpectedNumberOfCommandArguments(command_type);

	int expected_line_parts = command_part + expected_number_of_arguments;
	return (expected_line_parts == line_parts) ? TRUE : FALSE;
}



int AreCommandArgumentsValid(int line_parts_counter, char** line_parts)
{
	for (int i = 1; i < line_parts_counter; i++)
	{
		if (!WhatCommadArgument(line_parts[i]))
			return FALSE;
	}

	return TRUE;
}



int FindCommandType(char* command)
{
	if (IsZeroOperandsCommand(command))
		return ZERO_OPERAND_COMMAND;

	else if (IsOneOperandsCommand(command))
		return ONE_OPERAND_COMMAND;

	else
		return TWO_OPERAND_COMMAND;
}



int GetExpectedNumberOfCommandArguments(int command_type)
{
	switch (command_type)
	{
		case(ZERO_OPERAND_COMMAND):
			return 0;

		case(ONE_OPERAND_COMMAND):
			return 1;

		case(TWO_OPERAND_COMMAND):
			return 2;
	}
}



int WhatCommadArgument(char* argument)
{
	if (IsRegister(argument))
		return REGISTER;

	else if (IsValidSymbol__ArgumentSymbol(argument, FALSE))
		return SYMBOL;

	else if (IsValidNumber(argument))
		return NUMBER;

	else
		return NULL;
}



int IsZeroOperandsCommand(char* command)
{
	for (int i = 0; i < NUMBER_OF_ZERO_OPERANDS_COMMANDS; i++)
	{
		if (strcmp(ZERO_OPERANDS_COMMANDS[i], command) == 0)
			return TRUE;
	}

	return FALSE;
}



int IsOneOperandsCommand(char* command)
{
	for (int i = 0; i < NUMBER_OF_ONE_OPERANDS_COMMANDS; i++)
	{
		if (strcmp(ONE_OPERANDS_COMMANDS[i], command) == 0)
			return TRUE;
	}

	return FALSE;
}



int IsTwoOperandsCommand(char* command)
{
	for (int i = 0; i < NUMBER_OF_TWO_OPERANDS_COMMANDS; i++)
	{
		if (strcmp(TWO_OPERANDS_COMMANDS[i], command) == 0)
			return TRUE;
	}

	return FALSE;
}



int AreBothOperandsRegisters(char* argument1, char* argument2)
{
	if (IsRegister(argument1) && IsRegister(argument2))
		return TRUE;

	else
		return FALSE;
}

