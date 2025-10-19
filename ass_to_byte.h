#ifndef ASS_TO_BYTE
#define ASS_TO_BYTE

#include "enum_command_code.h"
#include "ass_common.h"

const int SIZE_CODE = 30;
const int LEN_COMMAND = 20;
const int LEN_STRING = 100;
const int LEN_REG_NAME = 5;
const int ONE_ARG = 1;
const int TWO_ARG = 2;

typedef double type_el_code;

void ReadAssemblerFile(type_el_code* code, int* labels);

bool SyntaxErrorReg(char* reg_num);

bool StringAnalysis(char* file_command_str, FILE* byte_code,
                     const char* file_name, int file_line,
                     type_el_code* code_ptr, int* current_index, int* labels,
                     PendingAddress *pending_add, int* count_pend);

bool GetCommand_2_Args(char* command, type_el_code element,
                       const char* file_name, int file_line,
                       type_el_code* code_ptr, int* current_index);

bool GetCommand_1_Args(char* command,
                       const char* file_name, int file_line,
                       type_el_code* code_ptr, int* current_index,
                       int* labels,
                       PendingAddress *pending_add, int* count_pend);

bool GetCommand_2_Args_Str(char* command, char* second_str,
                           const char* file_name, int file_line,
                           type_el_code* code_ptr, int* current_index,
                           int* labels,
                           PendingAddress *pending_add, int* count_pend);

void WriteToFile(FILE* byte_code, type_el_code* code_ptr, int current_index);

bool CorrectNum(char* command, long int* num_metka);

CommandStatus FunctionJB(long int num_metka, CommandStatus status, int* current_index, int* labels,
                         type_el_code* code_ptr);

#endif
