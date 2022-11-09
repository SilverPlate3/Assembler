#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "UsedByMany.h"

int TwoConsecutiveComma(char* line);


int IsValidNumber(char* line)
{
	int flag_number_is_zero = FALSE;
	char* endptr = 0;

	if (strlen(line) == 0)
	{
		strcpy_s(line, LINE_MAX_SIZE, "Parameter is empty");
		return NULL;
	}


	if ((strlen(line) == 1) && (line[0] == '0'))
		flag_number_is_zero = TRUE;

	else
	{
		for (int i = 0; line[i] != '\0'; i++)
		{
			// If not digit, is it +/- in position 0
			if (isdigit(line[i]) == FALSE)
				if ((i == 0 && (line[i] == 45 || line[i] == 43)) == FALSE)
				{
					strcpy_s(line, LINE_MAX_SIZE, "Parameter is not a valid number");
					return NULL;
				}
		}
	}

	int num = atoi(line);
	if ((num != 0) || flag_number_is_zero)
	{
		return num;
	}
	else
	{
		strcpy_s(line, LINE_MAX_SIZE, "Parameter is not a valid number");
		return NULL;
	}
}



int IsStringLongerThenNumber(char* string, int number)
{
	if (strlen(string) > number)
		return TRUE;

	else
		return FALSE;
}



int IsFirstIteration(int iteration_number)
{
	return iteration_number ? FALSE : TRUE;
}



int CheckComma(char* line)
{
	if (DoesStringEndsWithCharacter(line, ','))
	{
		strcpy_s(line, LINE_MAX_SIZE, "line part ending with a ,   Missing a parameter");
		return FALSE;
	}

	else if (TwoConsecutiveComma(line))
	{
		strcpy_s(line, LINE_MAX_SIZE, "Two consecutive commas were found");
		return FALSE;
	}

	return TRUE;
}



int DoesStringEndsWithCharacter(char * string, char character)
{
	return (string[strlen(string) - 1] == character) ? TRUE : FALSE;
}



int TwoConsecutiveComma(char* line)
{
	for (int i = 1; i < strlen(line); i++)
	{
		if ((line[i - 1] == line[i]) && (line[i] == ','))
			return TRUE;
	}

	return FALSE;
}








