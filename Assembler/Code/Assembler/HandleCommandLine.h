#ifndef HANDLECOMMANDLINE_H_INCLUDED
#define HANDLECOMMANDLINE_H_INCLUDED

/*
	Check the arguments given to the app.
	Manages other functions in the corresponding .c file

	input: The original argc & argv

	output: Array of iput .as files for our assembler.

	Remarks: If this function finishes without errors, it means all the aruments given are existing .as files.
*/
char** CreateFilesListFromCommandLine(int argc, char** argv);

#endif // !HANDLECOMMANDLINE_H_INCLUDED