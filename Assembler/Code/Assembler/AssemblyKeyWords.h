#ifndef ASSEMBLYKEYWORDS_H_INCLUDED
#define ASSEMBLYKEYWORDS_H_INCLUDED

#define NUMBER_OF_COMMANDS 16
#define NUMBER_OF_REGISTERS 8
#define NUMBER_OF_GUIDING_INSTRUCTIONS 4


char* ALL_COMMANDS[NUMBER_OF_COMMANDS];
char* REGISTERS[NUMBER_OF_REGISTERS];
char* GUIDING_INSTRUCTIONS[NUMBER_OF_GUIDING_INSTRUCTIONS];


/*
	Checks if the passed string is an assembly built in keyword

	input: pointer to a char array

	Output: boolean

	Remarks: Built in keywords are: commands, registers, guiding instructions
*/
int IsBuiltInKeyword(char* line);



/*
	Checks if the passed string is a built in assembly command

	input: pointer to a char array

	Output: Boolean

	Remarks: The 16 commands specified at ALL_COMMANDS
*/
int IsCommand(char* line);



/*
	Checks if the passed string is a built in assembly register

	input: pointer to a char array

	Output: Boolean

	Remarks: The 8 registers specified at REGISTERS
*/
int IsRegister(char* line);



/*
	Checks if the passed string is a built in assembly guiding instruction 

	input: pointer to a char array

	Output: Boolean

	Remarks: The 4 guiding instructions specified at GUIDING_INSTRUCTIONS
*/
int IsGuidingInstruction(char* line);



/*
	Gets the register number

	input: pointer to a char array that represent a register name.

	Output: number of the register

	Remarks: Each register has a number withing its name.
*/
int GetRegisterNumber(char* line);


#endif // !ASSEMBLYKEYWORDS_H_INCLUDED