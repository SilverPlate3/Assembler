#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ErrorHandling.h"
#include "UsedByMany.h"
#include "AssemblyKeyWords.h"
#include "CommandRelated.h"
#include "MachineCode.h"
#include "OutputFiles.h"

int HandleIfCommandHas2RegisterOperands(char** line_parts, LinkedListMaster* IC);
int CalculateFirstByte(char** line_parts);
int ArgumentSymbol(int index, char** line_parts, LinkedListMaster* IC, LinkedListMaster* DC, Symbol* Extrn[], Symbol* Ordinary[], int iteration_number);
int GetBinaryRepresentationOfZeroOperandCommand(char* command);
int GetBinaryRepresentationOfOneOperandCommand(char* command);
int GetBinaryRepresentationOfTwoOperandCommand(char* command);
int GetBinaryRepresentationOfDestinationOperand(char* operand);
int GetBinaryRepresentationOfSourceOperand(char* operand);
int GetOperandTypeRepresentation(char* operand);
int CalculateTwoRegistersOperands(char* source_operand, char* destination_operand);
int CalculateOperandByte(char* operand, int operand_number);
int CalculateRegisterOperand(char* operand, int operand_number);
int CalculateNumberOperand(char* operand);
void HandleExternOperand(LinkedListMaster* IC, int dc_counter, char* symbol_name);
int HandleOrdinarySymbolOperand(LinkedListMaster* IC, char symbol_name[], Symbol* Ordinary[]);



int MachineCodeFunctionsConductor(int line_parts_counter, char** line_parts, LinkedListMaster* IC, LinkedListMaster* DC, Symbol* Extrn[], Symbol* Ordinary[], int iteration_number)
{
	AddValueToEnd(IC, CalculateFirstByte(line_parts));

	if (HandleIfCommandHas2RegisterOperands(line_parts, IC))
		return TRUE;

	for (int i = 1; i < line_parts_counter; i++)
	{
		if (IsValidSymbol__ArgumentSymbol(line_parts[i], FALSE))
			return ArgumentSymbol(i, line_parts, IC, DC, Extrn, Ordinary, iteration_number);

		else
			AddValueToEnd(IC, CalculateOperandByte(line_parts[i], i));
	}

	return TRUE;
}



int CalculateFirstByte(char** line_parts)
{
	int command_type = FindCommandType(line_parts[0]);

	if (command_type == ZERO_OPERAND_COMMAND)
		return GetBinaryRepresentationOfZeroOperandCommand(line_parts[0]);

	else if (command_type == ONE_OPERAND_COMMAND)
		return GetBinaryRepresentationOfOneOperandCommand(line_parts[0]) + GetBinaryRepresentationOfDestinationOperand(line_parts[1]);

	else
		return GetBinaryRepresentationOfTwoOperandCommand(line_parts[0]) + GetBinaryRepresentationOfSourceOperand(line_parts[1]) + GetBinaryRepresentationOfDestinationOperand(line_parts[2]);
}



int HandleIfCommandHas2RegisterOperands(char** line_parts, LinkedListMaster* IC)
{
	if (FindCommandType(line_parts[0]) == TWO_OPERAND_COMMAND)
	{
		if (AreBothOperandsRegisters(line_parts[1], line_parts[2]))
		{
			AddValueToEnd(IC, CalculateTwoRegistersOperands(line_parts[1], line_parts[2]));
			return TRUE;
		}
	}

	return FALSE;
}




int ArgumentSymbol(int index, char** line_parts, LinkedListMaster* IC, LinkedListMaster* DC, Symbol* Extrn[], Symbol* Ordinary[], int iteration_number)
{
	if (IsSymbolNameInTable(line_parts[index], Extrn))
		HandleExternOperand(IC, DC->counter, line_parts[index]);

	else if (IsSymbolNameInTable(line_parts[index], Ordinary))
		HandleOrdinarySymbolOperand(IC, line_parts[index], Ordinary);

	else
	{
		if (IsFirstIteration(iteration_number))
			AddValueToEnd(IC, UNINITIALIZED_SYMBOL);
		else
			return NULL;
	}

	return TRUE;
}



int GetBinaryRepresentationOfZeroOperandCommand(char* command)
{
	int base = NUMBER_OF_TWO_OPERANDS_COMMANDS + NUMBER_OF_ONE_OPERANDS_COMMANDS;

	for (int i = 0; i < NUMBER_OF_ZERO_OPERANDS_COMMANDS; i++)
	{
		if (strcmp(ZERO_OPERANDS_COMMANDS[i], command) == 0)
		{
			base += i;
			break;
		}
	}

	return base << COMMAND_BIT_BASE;
}



int GetBinaryRepresentationOfOneOperandCommand(char* command)
{
	int base = NUMBER_OF_TWO_OPERANDS_COMMANDS;

	for (int i = 0; i < NUMBER_OF_ONE_OPERANDS_COMMANDS; i++)
	{
		if (strcmp(ONE_OPERANDS_COMMANDS[i], command) == 0)
		{
			base += i;
			break;
		}
	}

	return base << COMMAND_BIT_BASE;
}



int GetBinaryRepresentationOfTwoOperandCommand(char* command)
{
	int base = 0;

	for (int i = 0; i < NUMBER_OF_TWO_OPERANDS_COMMANDS; i++)
	{
		if (strcmp(TWO_OPERANDS_COMMANDS[i], command) == 0)
		{
			base += i;
			break;
		}
	}

	return base << COMMAND_BIT_BASE;
}



int GetBinaryRepresentationOfDestinationOperand(char* operand)
{
	int base = GetOperandTypeRepresentation(operand);
	return base << DESTINATION_OPERAND_BIT_BASE;
}



int GetBinaryRepresentationOfSourceOperand(char* operand)
{
	int base = GetOperandTypeRepresentation(operand);
	return base << SOURCE_OPERAND_BIT_BASE;
}



int GetOperandTypeRepresentation(char* operand)
{
	switch (WhatCommadArgument(operand))
	{
	case(REGISTER):
		return REGISTER_TYPE_OPERAND_BINARY_REPRESENTATION;

	case(SYMBOL):
		return SYMBOL_TYPE_OPERAND_BINARY_REPRESENTATION;

	case(NUMBER):
		return NUMBER_TYPE_OPERAND_BINARY_REPRESENTATION;

	default:
		CrucialErrorExit("Not valid arument. Logically, this should never be called. ");
	}
}



int CalculateTwoRegistersOperands(char* source_operand, char* destination_operand)
{
	int destination_register_number = GetRegisterNumber(destination_operand);
	int source_register_number = GetRegisterNumber(source_operand);

	int destination_operand_value = destination_register_number << DESTINATION_OPERAND_BIT_BASE;
	int source_operand_value = source_register_number << SOURCE_OPERAND_WHEN_TWO_REGISTERS_BIT_BASE;

	return source_operand_value + destination_operand_value;
}



int CalculateOperandByte(char* operand, int operand_number)
{
	switch (WhatCommadArgument(operand))
	{
	case(REGISTER):
		return CalculateRegisterOperand(operand, operand_number);

	case(NUMBER):
		return CalculateNumberOperand(operand);

	default:
		CrucialErrorExit("Not valid arument. Logically, this should never be called. ");
	}
}



int CalculateRegisterOperand(char* operand, int operand_number)
{
	if (operand_number == 1)
		return GetRegisterNumber(operand) << SOURCE_OPERAND_WHEN_TWO_REGISTERS_BIT_BASE;
	
	return GetRegisterNumber(operand) << DESTINATION_OPERAND_BIT_BASE;
}



int CalculateNumberOperand(char* operand)
{
	return atoi(operand) << DESTINATION_OPERAND_BIT_BASE;
}



void HandleExternOperand(LinkedListMaster * IC, int dc_counter, char * symbol_name)
{
	int value_of_symbol = IC->counter + dc_counter + BASE_ADDRESS;
	AddToExternOutputFile(symbol_name, value_of_symbol);

	AddValueToEnd(IC, 1);
}



int HandleOrdinarySymbolOperand(LinkedListMaster* IC, char symbol_name[], Symbol* Ordinary[])
{
	int symbol_value = GetSymbolValueByName(symbol_name, Ordinary);
	int value_to_add = symbol_value << DESTINATION_OPERAND_BIT_BASE;
	value_to_add += ARE_RELOCATABLE;

	AddValueToEnd(IC, value_to_add);
}



int GetCurrentMemoryAddress(LinkedListMaster* IC, LinkedListMaster* DC)
{
	return IC->counter + DC->counter + BASE_ADDRESS;
}