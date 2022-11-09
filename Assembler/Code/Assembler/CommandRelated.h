#ifndef COMMANDRELATED_H_INCLUDED
#define COMMANDRELATED_H_INCLUDED

#define NUMBER_OF_ZERO_OPERANDS_COMMANDS 2
#define NUMBER_OF_ONE_OPERANDS_COMMANDS 9
#define NUMBER_OF_TWO_OPERANDS_COMMANDS 5

char* ZERO_OPERANDS_COMMANDS[NUMBER_OF_ZERO_OPERANDS_COMMANDS];
char* ONE_OPERANDS_COMMANDS[NUMBER_OF_ONE_OPERANDS_COMMANDS];
char* TWO_OPERANDS_COMMANDS[NUMBER_OF_TWO_OPERANDS_COMMANDS];

enum command_type {
	ILLIGAL_COMMAND,
	ZERO_OPERAND_COMMAND,
	ONE_OPERAND_COMMAND, 
	TWO_OPERAND_COMMAND
	};


enum commnad_argumnet_type
{
	REGISTER = 1,
	NUMBER,
	SYMBOL
};



/*
	Checks if the arguments of the command are valid. 

	input:
		[in] number of line parts. 
		[in] array of strings that represents the line parts.

	Output: boolean.

	Remarks: The function checks the number and type of the command arguments.
*/
int IsCommandArguments(int line_parts_counter, char** line_parts);



/*
	Find the command type. Command type is specified by the amount of arguments the command is uses.

	input:
		[in] string that represents the command. 

	Output: enum that represents the type of command. 

	Remarks:
*/
int FindCommandType(char* command);



/*
	Checks the type of a specific command argumet.

	input:
		[in] string that represents the argument. 

	Output: enum that represents the type of argument. 

	Remarks: The argument must be one of: register, symbol, number
*/
int WhatCommadArgument(char* argument);



/*
	Checks if both command argumets are registers.

	input:
		[in] string that represents the argument. 
		[in] string that represents the argument. 

	Output: boolean.

	Remarks: 
*/
int AreBothOperandsRegisters(char* argument1, char* argument2);


#endif //!COMMANDRELATED_H_INCLUDED