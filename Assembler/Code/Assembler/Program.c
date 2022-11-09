#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

#include "HandleCommandLine.h"
#include "ErrorHandling.h"
#include "ParsingFiles.h"
#include "UsedByMany.h"
#include "DataAccumulater.h"
#include "CheckInstructionParameters.h"
#include "AssemblyKeyWords.h"
#include "SymbolRelated.h"
#include "CommandRelated.h"
#include "MachineCode.h"
#include "OutputFiles.h"
#include "MemoryRelatedFunctions.h"
#include "Finishing.h"
#include "Base64.h"


int main(int argc, char** argv)
{
	char** files_list = CreateFilesListFromCommandLine(argc, argv);

	for (int i = 0; i < argc - 1; i++)
	{
		LinkedListMaster* DC = CreateLinkedListMaster();
		LinkedListMaster* IC = CreateLinkedListMaster();
		Symbol* Extrn[TABLE_SIZE] = { 0 };
		Symbol* Entry[TABLE_SIZE] = { 0 };
		Symbol* Ordinary[TABLE_SIZE] = { 0 };

		int error_flag = FALSE;
		int number_of_important_lines = 0;
		int line_parts_counter = 0;
		char** line_parts = NULL;
		strcpy_s(input_file, _MAX_PATH, "");

		important_line** important_file_lines = ReadImportantLines(files_list[i], &number_of_important_lines);
		if (important_file_lines == NULL)
		{
			ReportInputError("File contains a line longer then allowed", number_of_important_lines, &error_flag);
			continue;
		}

		for (int k = 0; k < NUMBER_OF_ITERATIONS; k++)
		{
			for (int j = 0; j < number_of_important_lines; j++)
			{
				char first_character_of_the_line = (important_file_lines[j]->line)[0];
				int character_type = CheckWhatTheLineStartWith(first_character_of_the_line);
				if (character_type == NULL)
				{
					ReportInputError("First character is illigal", important_file_lines[j]->line_number, &error_flag);
					continue;
				}

				int type_of_guiding_instruction = 0;
				line_parts_counter = 0;
				line_parts = SplitLineToParts(important_file_lines[j]->line, &line_parts_counter, " ");
				if (line_parts == NULL)
					FreeArrayOfPointersBeforeCrucialExit(number_of_important_lines, important_file_lines, "SplitLineToParts failed due to memory operations, exiting..... ");

				if (character_type == STARTS_WITH_DOT)
				{
					type_of_guiding_instruction = GetGuidingInstructionType(line_parts[0]);

					if (line_parts_counter != 2)
						ReportInputError("Line doesn't have correct amount of values", important_file_lines[j]->line_number, &error_flag);

					else if (type_of_guiding_instruction == OTHER)
						ReportInputError(line_parts[0], important_file_lines[j]->line_number, &error_flag);

					else if (GuidingInstructionFactory(DC, Extrn, Entry, line_parts[1], type_of_guiding_instruction, k) == NULL)
						ReportInputError(line_parts[1], important_file_lines[j]->line_number, &error_flag);
				}

				else if (character_type == STARTS_WITH_LETTER)
				{
					char line_first_part[LINE_MAX_SIZE] = { 0 };
					strcpy_s(line_first_part, LINE_MAX_SIZE, line_parts[0]);

					if (IsValidSymbol__FirstWordSymbol(line_first_part, FALSE))
					{
						Symbol* symbol = NULL;
						if (IsFirstIteration(k))
						{
							line_first_part[strlen(line_first_part) - 1] = '\0';
							symbol = CreateSymbol(line_first_part, UNINITIALIZED_SYMBOL);
						}

						if (IsFirstIteration(k))
						{
							if (IsSymbolInTable(symbol, Extrn))
							{
								ReportInputError("Symbol is already in .extern table", important_file_lines[j]->line_number, &error_flag);
								FreeSymbol(symbol);
								continue;
							}

							else if (IsSymbolInTable(symbol, Entry))
							{
								if (SetSymbolValue(Entry, symbol, GetCurrentMemoryAddress(IC, DC)) == NULL)
								{
									ReportInputError("Symbol is already in .entry table and its value is initialized", important_file_lines[j]->line_number, &error_flag);
									FreeSymbol(symbol);
									continue;
								}
							}
						}

						if (IsGuidingInstruction(line_parts[1]))
						{
							type_of_guiding_instruction = GetGuidingInstructionType(line_parts[1]);

							if (line_parts_counter != 3)
								ReportInputError("Line doesn't have correct amount of values", important_file_lines[j]->line_number, &error_flag);

							else
							{
								if (IsFirstIteration(k))
								{
									if (type_of_guiding_instruction == DOT_DATA || type_of_guiding_instruction == DOT_STRING)
									{
										if (!HandleNewOrdinarySymbol(symbol, Extrn, Ordinary, IC, DC))
											ReportInputError("Symbol exists already!", important_file_lines[j]->line_number, &error_flag);
									}

									else // .entry and .extern
										printf("\nWarning:  Line %d.  Symbol before %s keyword", important_file_lines[j]->line_number, GUIDING_INSTRUCTIONS[type_of_guiding_instruction - 1]);
								}
							
								if (GuidingInstructionFactory(DC, Extrn, Entry, line_parts[2], type_of_guiding_instruction, k) == NULL)
									ReportInputError(line_parts[2], important_file_lines[j]->line_number, &error_flag);
							}
						}

						else if (IsCommand(line_parts[1]))
						{
							line_parts = SplitLineForCommand(line_parts, &line_parts_counter, important_file_lines[j]->line);

							char** line_parts_without_symbol = &line_parts[1];
							int line_parts_counter_without_symbol = line_parts_counter - 1;

							if (!IsCommandArguments(line_parts_counter_without_symbol, line_parts_without_symbol))
							{
								ReportInputError(line_parts_without_symbol[0], important_file_lines[j]->line_number, &error_flag);
								FreeSymbol(symbol);
							}

							else
							{
								if(IsFirstIteration(k))
									if (!HandleNewOrdinarySymbol(symbol, Extrn, Ordinary, IC, DC))
										ReportInputError("Symbol exists already!", important_file_lines[j]->line_number, &error_flag);

								if(MachineCodeFunctionsConductor(line_parts_counter_without_symbol, line_parts_without_symbol, IC, DC, Extrn, Ordinary, k) == NULL)
									ReportInputError("Uninitilized symbol found in the second iteration", important_file_lines[j]->line_number, &error_flag);
							}
						}

						else
						{
							FreeSymbol(symbol);
							ReportInputError("Word after the symbol is invalid", important_file_lines[j]->line_number, &error_flag);
						}
					}

					else if (IsCommand(line_first_part))
					{
						line_parts = SplitLineForCommand(line_parts, &line_parts_counter, important_file_lines[j]->line);

						if (!IsCommandArguments(line_parts_counter, line_parts))
							ReportInputError(line_parts[0], important_file_lines[j]->line_number, &error_flag);

						else
							if(MachineCodeFunctionsConductor(line_parts_counter, line_parts, IC, DC, Extrn, Ordinary, k) == NULL)
								ReportInputError("Uninitilized symbol found in the second iteration", important_file_lines[j]->line_number, &error_flag);
					}

					else
						ReportInputError("First word is illigal", important_file_lines[j]->line_number, &error_flag);
				}

				else
					ReportInputError("Line starts with an illegal character", important_file_lines[j]->line_number, &error_flag);

				FreeArrayOfPointers(line_parts_counter, line_parts);
				line_parts = NULL;
			}

			if(IsFirstIteration(k))
			{
				strcpy_s(input_file, _MAX_PATH, argv[i + 1]);
				
				if (!EntrySymbolsConclusion(Entry, Ordinary))
					ReportInputError("Symbol value cannot be found! Compiler's second iteration is cancelled", 0, &error_flag);

				ResetLinkedLists(&IC, &DC);
			}

			if (error_flag)
			{
				CleanAll(Extrn, Entry, Ordinary,
					IC, DC,
					number_of_important_lines, important_file_lines, line_parts_counter, line_parts);
				break;
			}
		}

		if (!error_flag)
		{
			CreateObOutputfile(IC, DC);
			CleanMemory(Extrn, Entry, Ordinary,
				IC, DC,
				number_of_important_lines, important_file_lines, line_parts_counter, line_parts);
		}
	}

	FreeArrayOfPointers(argc - 1 , files_list);

	_CrtDumpMemoryLeaks(); // Only in debug mode - Check if there are memory leaks.  FYI - There none ;)  
}
