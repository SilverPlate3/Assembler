#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Base64.h"

void PositiveNumbers(int decimal, char binary_string[]);
void NegativeNumbers(int decimal, char binary_string[]);
void DivideBinaryStringToTwo(char binary_string[], char first_part[], char second_part[]);
void FillShortBinary(char binary[], char short_binary[]);



char* BASE64_CHARACTERS[BASE64_NUMBER_OF_CHARACTERS] = 
{ 
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};



void DecimalToBinaryString(int decimal, char binary_string[])
{
    if (decimal >= 0)
        PositiveNumbers(decimal, binary_string);
    else
        NegativeNumbers(decimal, binary_string);
}



void PositiveNumbers(int decimal, char binary_string[])
{
    for (int i = BINARY_LENGTH - 1; i >= 0; i--)
    {
        binary_string[i] = decimal % 2 ? '1' : '0';
        decimal = decimal / 2;
    }
}



void NegativeNumbers(int decimal, char binary_string[])
{
    decimal += 1;

    for (int i = BINARY_LENGTH - 1; i >= 0; i--)
    {
        binary_string[i] = decimal % 2 ? '0' : '1';
        decimal = decimal / 2;
    }
}



void BinaryStringToTwoDecimals(char binary_string[], int * first_part, int* second_part)
{
    char binary_first_part[SHORT_BINARY_LENGTH + 1] = { 0 };
    char binary_second_part[SHORT_BINARY_LENGTH + 1] = { 0 };

    DivideBinaryStringToTwo(binary_string, binary_first_part, binary_second_part);
    
    *first_part = (int)strtol(binary_first_part, NULL, 2);
    *second_part = (int)strtol(binary_second_part, NULL, 2);
}



void DivideBinaryStringToTwo(char binary_string[], char first_part[], char second_part[])
{
    FillShortBinary(binary_string, first_part);
    FillShortBinary(binary_string + SHORT_BINARY_LENGTH, second_part);
}



void FillShortBinary(char binary_string[], char short_binary[])
{
    for (int i = 0; i < SHORT_BINARY_LENGTH; i++)
        short_binary[i] = binary_string[i];
}