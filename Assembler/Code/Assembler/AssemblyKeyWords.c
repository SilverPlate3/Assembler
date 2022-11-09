#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AssemblyKeyWords.h"
#include "UsedByMany.h"
#include "CheckInstructionParameters.h"


char * ALL_COMMANDS[NUMBER_OF_COMMANDS] =
{
	"mov",
	"cmp",
	"add",
	"sub",
	"not",
	"clr",
	"lea",
	"inc",
	"dec",
	"jmp",
	"bne",
	"red",
	"prn",
	"jsr",
	"rts",
	"stop"
};


char* REGISTERS[NUMBER_OF_REGISTERS] =
{
	"@r0",
	"@r1",
	"@r2",
	"@r3",
	"@r4",
	"@r5",
	"@r6",
	"@r7"
};



char* GUIDING_INSTRUCTIONS[NUMBER_OF_GUIDING_INSTRUCTIONS] =
{
	".data",
	".string",
	".entry",
	".extern"
};



int IsBuiltInKeyword(char* line)
{
	if (IsCommand(line))
		return TRUE;

	else if (IsRegister(line))
		return TRUE;

	else if (IsGuidingInstruction(line))
		return TRUE;

	else
		return FALSE;
}


int IsCommand(char* line)
{
	for (int i = 0; i < NUMBER_OF_COMMANDS; i++)
	{
		if (strcmp(ALL_COMMANDS[i], line) == 0)
			return TRUE;
	}

	return FALSE;
}



int IsRegister(char* line)
{
	for (int i = 0; i < NUMBER_OF_REGISTERS; i++)
	{
		if (strcmp(REGISTERS[i], line) == 0)
			return TRUE;
	}

	return FALSE;
}



int IsGuidingInstruction(char* line)
{
	for (int i = 0; i < NUMBER_OF_GUIDING_INSTRUCTIONS; i++)
	{
		if (strcmp(GUIDING_INSTRUCTIONS[i], line) == 0)
			return TRUE;
	}

	return FALSE;
}



int GetRegisterNumber(char * line)
{
	for (int i = 0; i < NUMBER_OF_REGISTERS; i++)
	{
		if (strcmp(REGISTERS[i], line) == 0)
			return i;
	}
}