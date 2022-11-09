#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ErrorHandling.h"
#include "OutputFiles.h"
#include "Base64.h"

void AddToOutputFile(char* symbol_name, int symbol_value, char* output_file_extenstion);
void DeleteOutputFile(char* output_file_extenstion);
void WriteObFileHeader(FILE* fp, int IC_length, int DC_length);
void WriteLinkedListValuesInBase64(FILE* fp, LinkedListMaster* LinkedList);

char input_file[_MAX_PATH] = { 0 };


void AddFileTypeExtension(char ext_output_file[], char file_type_extention[])
{
	strcpy_s(ext_output_file, _MAX_PATH, input_file);
	strcat_s(ext_output_file, _MAX_PATH, file_type_extention);
}



void AddToExternOutputFile(char * symbol_name, int symbol_value)
{
	AddToOutputFile(symbol_name, symbol_value, EXTERN_OUTPUT_FILE_EXTENSTION);
}



void AddToEntryOutputFile(char* symbol_name, int symbol_value)
{
	AddToOutputFile(symbol_name, symbol_value, ENTRY_OUTPUT_FILE_EXTENSTION);
}



void AddToOutputFile(char* symbol_name, int symbol_value, char* output_file_extenstion)
{
	if (!strcmp(input_file, ""))
		return;

	char output_file[_MAX_PATH] = { 0 };
	AddFileTypeExtension(output_file, output_file_extenstion);

	FILE* fp;
	if (fopen_s(&fp, output_file, "a") != 0)
		CrucialErrorExit("\nCan't open %s....", output_file);

	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s %d\n", symbol_name, symbol_value);
	fclose(fp);
}



void DeleteExtFile()
{
	DeleteOutputFile(EXTERN_OUTPUT_FILE_EXTENSTION);
}



void DeleteEntFile()
{
	DeleteOutputFile(ENTRY_OUTPUT_FILE_EXTENSTION);
}



void DeleteOutputFile(char* output_file_extenstion)
{
	char output_file[_MAX_PATH] = { 0 };
	AddFileTypeExtension(output_file, output_file_extenstion);

	remove(output_file);
}



void CreateObOutputfile(LinkedListMaster * IC, LinkedListMaster* DC)
{
	char obj_output_file[_MAX_PATH] = { 0 };
	AddFileTypeExtension(obj_output_file, OBJECT_OUTPUT_FILE_EXTENSTION);

	FILE* fp;
	if (fopen_s(&fp, obj_output_file, "a") != 0)
		CrucialErrorExit("\nCan't open .ext file.....");

	WriteObFileHeader(fp, IC->counter, DC->counter);
	WriteLinkedListValuesInBase64(fp, IC);
	WriteLinkedListValuesInBase64(fp, DC);
}



void WriteObFileHeader(FILE* fp, int IC_length, int DC_length)
{
	fprintf(fp, "%d %d\n", IC_length, DC_length);
}



void WriteLinkedListValuesInBase64(FILE* fp, LinkedListMaster* LinkedList)
{
	char binary_representation[BINARY_LENGTH + 1] = { 0 };
	int first_part_of_binary = 0;
	int Second_part_of_binary = 0;

	Node* current_node = LinkedList->Head;
	while (current_node != NULL)
	{
		DecimalToBinaryString(current_node->value, binary_representation);
		BinaryStringToTwoDecimals(binary_representation, &first_part_of_binary, &Second_part_of_binary);
		fprintf(fp, "%c%c\n", (char)BASE64_CHARACTERS[first_part_of_binary], (char)BASE64_CHARACTERS[Second_part_of_binary]);
		
		current_node = current_node->next;
	}
}