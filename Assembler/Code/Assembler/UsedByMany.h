#ifndef USEDBYMANY_H_INCLUDED
#define USEDBYMANY_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define LINE_MAX_SIZE 81*sizeof(char)


#define Increment_2_ObjectsByOne(x, y) (++y, ++x)
#define Increment_3_ObjectsByOne(x, y, z) (++y, ++x, ++z)

#define NUMBER_OF_ITERATIONS 2

/*
	Does a string represents a valid number.

	input:
		[in] String to check.

	Output: If the string represents a valid number return the integer equvilent of the string.

	Remarks: + - signs are taken into considiration. 
*/
int IsValidNumber(char* line);


/*
	Checks if a string length is longer then a number.

	input:
		[in] String to check.
		[in] Number that represents max length.

	Output: Boolean that represents the answer.

	Remarks:None.
*/
int IsStringLongerThenNumber(char* string, int number);


/*
	Checks if this is the first iteration. 

	input:
		[in] Number that represents the iteration.

	Output: Boolean that represents the answer.

	Remarks:None.
*/
int IsFirstIteration(int iteration_number);


/*
	Checks if the specified string ends with the specified character.

	input:
		[in] String that is under check.
		[in] Character that the string should end with.

	Output: Boolean that represents the answer.

	Remarks:None.
*/
int DoesStringEndsWithCharacter(char* string, char character);


/*
	Function that checks if the commas in the line are in the correct positions and amount.

	input:
		[in] Line to check the commas in.

	Output: Boolean that if the comma's in the line are in the correct amount and place.

	Remarks:None.
*/
int CheckComma(char* line);

#endif // !USEDBYMANY_H_INCLUDED