#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ErrorHandling.h"
#include "ParsingFiles.h"
#include "AssemblyKeyWords.h"
#include "MemoryRelatedFunctions.h"

int IsLineEmptyOrComment(char line[]);
int CheckWhatTheLineStartWith(char first_character_of_line);
char* RemoveUnwantedSpaces(char line[], int line_length);
char** SplitLineToParts(char line[], int* pLine_parts_counter);
int IsLineLength(FILE* fpr);
void AddImportantLine(important_line*** pImportant_file_lines, int* pNumber_of_important_lines, char line[], int line_number_counter);
void SkipWhiteSpacesAtStartOfLine(char** line, int* pLine_counter);
int InitilizeLinePart(char*** pLine_parts, int line_parts_counter);
int StrtokWrapper(char*** pLine_parts, int line_parts_counter, char line[], char delimiters[]);


important_line** ReadImportantLines(char* input_file, int* pnumber_of_important_lines)
{
	int number_of_important_lines = 0;
	int line_number_counter = 1;

	important_line** important_file_lines = (important_line**)AllocateArrayOfPointers(number_of_important_lines);

	FILE* fpr;
	errno_t result;
	result = fopen_s(&fpr, input_file, "r");
	if (result != 0)
		FreeArrayOfPointersBeforeCrucialExit(number_of_important_lines, important_file_lines, "Can't open input file that surley exists. Exiting....");

	while (TRUE)
	{
		char line[LINE_MAX_SIZE] = { 0 };
		if (!IsLineLength(fpr))
		{
			FreeArrayOfPointers(number_of_important_lines, important_file_lines);
			*pnumber_of_important_lines = line_number_counter;
			return NULL;
		}
		else
			fgets(line, LINE_MAX_SIZE, fpr);


		if (IsLineEmptyOrComment(line) == FALSE)
			AddImportantLine(&important_file_lines, &number_of_important_lines, line, line_number_counter);

		if (feof(fpr))
			break;

		line_number_counter++;
	}

	fclose(fpr);
	*pnumber_of_important_lines = number_of_important_lines;
	return important_file_lines;
}



int IsLineLength(FILE* fpr)
{
	int file_cursor_index = ftell(fpr);
	int is_legal_length = TRUE;
	char line_size_checker[10000] = { 0 };

	fgets(line_size_checker, sizeof(line_size_checker), fpr);
	if (strlen(line_size_checker) > LINE_MAX_SIZE)
		is_legal_length = FALSE;

	fseek(fpr, file_cursor_index, SEEK_SET);
	return is_legal_length;
}



int IsLineEmptyOrComment(char pLine[])
{
	while (*pLine != '\0') {
		if (isspace(*pLine) == 0)
		{
			if (*pLine == ';')
				return TRUE;
			
			else
				return FALSE;
		}
		pLine++;
	}
	return TRUE;
}



void AddImportantLine(important_line*** pImportant_file_lines, int * pNumber_of_important_lines, char line[], int line_number_counter)
{
	important_line** important_file_lines = *pImportant_file_lines;
	int number_of_important_lines = *pNumber_of_important_lines;

	important_file_lines = (important_line**)ReallocationPointerOfPointer(important_file_lines, ++number_of_important_lines);
	if (important_file_lines == NULL)
		FreeArrayOfPointersBeforeCrucialExit(number_of_important_lines, important_file_lines, "ReallocationPointerOfPointer failed, exiting..... ");

	important_file_lines[number_of_important_lines - 1] = (important_line*)calloc(1, sizeof(important_line));
	if (important_file_lines[number_of_important_lines - 1] == NULL)
		FreeArrayOfPointersBeforeCrucialExit(number_of_important_lines, important_file_lines, "Calloc failed... ");

	important_file_lines[number_of_important_lines - 1]->line_number = line_number_counter;
	strcpy_s(important_file_lines[number_of_important_lines - 1]->line, LINE_MAX_SIZE, RemoveUnwantedSpaces(line, strlen(line)));

	*pNumber_of_important_lines = number_of_important_lines;
	*pImportant_file_lines = important_file_lines;
}



char * RemoveUnwantedSpaces(char line[], int line_length)
{
	char new_line[LINE_MAX_SIZE] = { 0 };
	int new_line_counter = 0;
	int line_counter = 0;
	int was_previous_character_a_space = FALSE;
	int was_previous_character_a_comma = FALSE;
	
	SkipWhiteSpacesAtStartOfLine(&line, &line_counter);

	while (line_counter <= line_length)
	{
		// If character is a space  &  the previous character wasn't a space or comma
		if ((*line == ' ' || *line == '\t') && (was_previous_character_a_space == FALSE) && (was_previous_character_a_comma == FALSE))
		{		

			// If the next character isn't a comma
			if (*(line+1) != ',')
			{
				new_line[new_line_counter] = ' ';
				was_previous_character_a_space = TRUE;
			}
			else
			{
				Increment_2_ObjectsByOne(line, line_counter);
				continue;
			}
		}

		// If the character isn't a space
		else if (*line != ' ' && *line != '\t')
		{

			// If the character is a comma & the prvios character was a space
			if (*line == ',' && was_previous_character_a_space)
			{
				new_line[new_line_counter-1] = *line;
				was_previous_character_a_space = FALSE;
				Increment_2_ObjectsByOne(line, line_counter);
				was_previous_character_a_comma = TRUE;
				continue;
			}

			new_line[new_line_counter] = *line;
			was_previous_character_a_space = FALSE;

			// If the character is a comma 
			if(*line == ',')
				was_previous_character_a_comma = TRUE;
			else
				was_previous_character_a_comma = FALSE;
		}

		// If the character is a space, but the previous character was a space or comma
		else
		{
			Increment_2_ObjectsByOne(line, line_counter);
			continue;
		}
		Increment_3_ObjectsByOne(line, line_counter, new_line_counter);
	}
	new_line[strcspn(new_line, "\n")] = 0;
	return new_line;
}



void SkipWhiteSpacesAtStartOfLine(char** line, int* pLine_counter)
{
	while (**line == ' ' || **line == '\t')
	{
		Increment_2_ObjectsByOne(*line, *pLine_counter);
	}
}



int CheckWhatTheLineStartWith(char first_character_of_line)
{
	if (first_character_of_line == '.')
		return STARTS_WITH_DOT;

	else if (isalpha(first_character_of_line))
		return STARTS_WITH_LETTER;

	else
		return NULL;
}



char** SplitLineForCommand(char ** current_line_parts, int * line_parts_counter, char line_to_split[])
{
	FreeArrayOfPointers(*line_parts_counter, current_line_parts);
	
	char ** line_parts =  SplitLineToParts(line_to_split, line_parts_counter, COMMANDS_LINE_DELEMETERS);
	if (line_parts == NULL)
		CrucialErrorExit("\SplitLineToParts failed due to memory operations, exiting..... ");

	return line_parts;
}



char** SplitLineToParts(char line[], int * pLine_parts_counter, char delimiters[])
{
	char line_copy[LINE_MAX_SIZE] = {0};
	strcpy_s(line_copy, LINE_MAX_SIZE, line);

	int line_parts_counter = 0;
	char**  line_parts = (char**)calloc(line_parts_counter, sizeof(char*));
	if (line_parts == NULL)
	{
		printf("\ncalloc failed.... Not error with .as file");
		return NULL;
	}

	line_parts_counter = StrtokWrapper(&line_parts, line_parts_counter, line, delimiters);
	if (line_parts_counter == NULL)
		return NULL;

	*pLine_parts_counter = line_parts_counter;
	return line_parts;
}



int StrtokWrapper(char*** pLine_parts, int line_parts_counter, char line[], char delimiters[])
{
	char** line_parts = *pLine_parts;
	char line_copy[LINE_MAX_SIZE] = { 0 };
	strcpy_s(line_copy, LINE_MAX_SIZE, line);

	char* next_token = NULL;
	char* token = strtok_s(line_copy, delimiters, &next_token);
	line_parts_counter++;

	while (token != NULL)
	{
		line_parts = (char**)ReallocationPointerOfPointer(line_parts, line_parts_counter);
		if (line_parts == NULL)
		{
			printf("\ReallocationPointerOfPointer failed.... Not error with .as file");
			return NULL;
		}

		if (InitilizeLinePart(&line_parts, line_parts_counter) == NULL)
			return NULL;

		strcpy_s(line_parts[line_parts_counter - 1], LINE_MAX_SIZE, token);

		token = strtok_s(NULL, delimiters, &next_token);
		if (token == NULL || !strcmp(token, "\n"))
			break;

		line_parts_counter++;
	}

	*pLine_parts = line_parts;
	return line_parts_counter;
}



int InitilizeLinePart(char *** pLine_parts, int line_parts_counter)
{
	char** line_parts = *pLine_parts;

	line_parts[line_parts_counter - 1] = (char*)calloc(1, LINE_MAX_SIZE);
	if (line_parts[line_parts_counter - 1] == NULL)
	{
		printf("\ncalloc failed.... Not error with .as file");
		FreeArrayOfPointers(line_parts_counter, line_parts);
		return NULL;
	}

	*pLine_parts = line_parts;
	return TRUE;
}

