#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

#define BASE64_NUMBER_OF_CHARACTERS 64
char* BASE64_CHARACTERS[BASE64_NUMBER_OF_CHARACTERS];

#define BINARY_LENGTH 12
#define SHORT_BINARY_LENGTH 6



/*
	Converts a decimal number to a 12 bit binary number

	input: 
		[in] Number to converte 
		[out] Buffer that will get the binary representation 

	Output: 

	Remarks: 
*/
void DecimalToBinaryString(int decimal, char binary_string[]);



/*
	Converts a 12 bit binary string into 2 decimal numbers

	input:
		[in] char array that represents a 12 bit binary.
		[out] Pointer that will be refrenced to the first decimal number 
		[out] Pointer that will be refrenced to the second decimal number

	Output:

	Remarks: The binary string is cut in the middle. Each half is converted to a decimal number.
*/
void BinaryStringToTwoDecimals(char binary_string[], int* first_part, int* second_part);


#endif //!BASE64_H_INCLUDED