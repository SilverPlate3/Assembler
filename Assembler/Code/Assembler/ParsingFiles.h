#ifndef PARSINGFILES_H_INCLUDED
#define PARSINGFILES_H_INCLUDED

#include "UsedByMany.h"

#define STARTS_WITH_DOT 1
#define STARTS_WITH_LETTER 2

#define COMMANDS_LINE_DELEMETERS " ,"


typedef struct {
	char line[LINE_MAX_SIZE];
	int line_number;
} important_line;


/*
	Starts parsing the input files.
	Using other functions in the corresponding .c file,  it checks each line, and treats it as needed.

	input: 
		[in] Input file path
		[out] number of important lines in file 

	output: array of structs. Each struct represents an useful line in the input file.

	Remarks: Only the "useful" line are inserted into this array.
*/
important_line** ReadImportantLines(char* input_file, int* pnumber_of_important_lines);



/*
	Checks the type of the first character of the line

	input: 
		[in] the first chracter of the line.

	output: number that represents the result.

	Remarks: None.

*/
int CheckWhatTheLineStartWith(char first_character_of_line);


/*
	Re-splits the line. This time its parsed so a "command handlers" can handle it. 

	input:
		[in] 2D dynamically allocated array that holds strings that represent the current line parts. 
		[in, out] Pointer to an number that represent the length of the 2D array.
		[in] Line we need to re-split.
*/
char** SplitLineForCommand(char** current_line_parts, int* line_parts_counter, char line_to_split[]);


/*
	splits the line to parts.

	input:
		[in] 2D dynamically allocated array that holds strings that represent the current line parts.
		[in, out] Pointer to an number that represent the length of the 2D array.
		[in] Delimiters that will be used to split the line.
*/
char** SplitLineToParts(char line[], int* pLine_parts_counter, char delimiters[]);



#endif // !HANDLECOMMANDLINE_H_INCLUDED