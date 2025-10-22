#include <stdio.h>
#include <string.h>
#include <cassert>
#include "ass_to_byte.h"
#include "enum_command_code.h"
#include "ass_common.h"
#include "struct_for_file.h"

void ReadAssemblerFile (type_el_code* code_ptr, int* labels) {

    assert(code_ptr != NULL);
    assert(labels   != NULL);

    FILE* file = fopen("assembler_code.ASM", "r");
    FILE* byte_code = fopen("byte_code.txt", "w");

    assert(file      != NULL);
    assert(byte_code != NULL);

    char file_string[LEN_STRING];
    char* file_command_str = file_string;
    int size_command_str = LEN_COMMAND;

    PendingAddress pending_add[SIZE_PENDING];//массив для запоминания номера метки и позиции массива code, куда нужно записать её адрес
    int count_pend = 0;

    assert(file_command_str != NULL);

    const char* file_name = "assembler_code.ASM";
    int file_line = 1;
    int current_index = 0;

    assert(file_name != NULL);

    while (fgets(file_command_str, size_command_str, file) != NULL) {

        if (!StringAnalysis(file_command_str, byte_code,
                            file_name, file_line,
                            code_ptr, &current_index, labels,
                            pending_add, &count_pend))
            break;

        file_line++;

    }

    code_ptr[current_index] = current_index;

    WriteToFile(byte_code, code_ptr, current_index);

    fclose(file);
    fclose(byte_code);

}

bool SyntaxErrorReg(char* second_str) {

    assert(second_str != NULL);

    if ((strlen(second_str) > 3) && (second_str[3] == ';')) {

          return false;

    }

    return !(((second_str[1] - 'A') < 16) && (strlen(second_str) == 3) &&
            (second_str[0] == 'R') && (second_str[2] == 'X'));

}

bool StringAnalysis(char* file_command_str, FILE* byte_code,
                     const char* file_name, int file_line,
                     type_el_code* code_ptr, int* current_index, int* labels,
                     PendingAddress *pending_add, int* count_pend) {

    assert(file_command_str != NULL);
    assert(file_name        != NULL);
    assert(code_ptr         != NULL);
    assert(current_index    != NULL);
    assert(labels           != NULL);
    assert(byte_code        != NULL);
    assert(pending_add      != NULL);
    assert(count_pend       != NULL);

    char command[LEN_COMMAND];
    type_el_code element = 0;
    char second_str[LEN_REG_NAME];

    if (sscanf(file_command_str, "%s %lf", command, &element) == 2) {

        if (!GetCommand_2_Args(command, element,
                          file_name, file_line,
                          code_ptr, current_index))

                     return false;

    } else if (sscanf(file_command_str, "%s %s", command, second_str) == 2) {

        if (!GetCommand_2_Args_Str(command, second_str,
                                   file_name, file_line,
                                   code_ptr, current_index,
                                   labels,
                                   pending_add, count_pend))

                     return false;

    } else if (sscanf(file_command_str, "%s ", command) == 1) {

        if (!GetCommand_1_Args(command,
                               file_name, file_line,
                               code_ptr, current_index,
                               labels,
                               pending_add, count_pend))

                     return false;

    } else {


    }

    return true;

}

bool GetCommand_2_Args(char* command, type_el_code element,
                  const char* file_name, int file_line,
                  type_el_code* code_ptr, int* current_index) {

    assert(command          != NULL);
    assert(file_name        != NULL);
    assert(code_ptr         != NULL);
    assert(current_index    != NULL);

    if (strcmp(command, "PUSH") == 0) {

        *(code_ptr + *current_index) = PUSH;
         (*current_index)++;
        *(code_ptr + *current_index) = element;
         (*current_index)++;

    } else if (command[0] == ';') {

         return true;

    } else {

        printf("file %s, line %d invailed command\n", file_name, file_line);
        return false;

    }

    return true;

}

bool GetCommand_1_Args(char* command,
                  const char* file_name, int file_line,
                  type_el_code* code_ptr, int* current_index,
                  int* labels,
                  PendingAddress *pending_add, int* count_pend) {

    assert(command          != NULL);
    assert(file_name        != NULL);
    assert(code_ptr         != NULL);
    assert(current_index    != NULL);
    assert(labels           != NULL);
    assert(pending_add      != NULL);
    assert(count_pend       != NULL);

    if (strcmp(command, "ADD") == 0) {

        *(code_ptr + *current_index) = ADD;
         (*current_index)++;

    } else if (strcmp(command, "MUL") == 0) {

        *(code_ptr + *current_index) = MUL;
         (*current_index)++;

    } else if (strcmp(command, "SUB") == 0) {

        *(code_ptr + *current_index) = SUB;
         (*current_index)++;

    } else if (strcmp(command, "SQRT") == 0) {

        *(code_ptr + *current_index) = SQRT;
         (*current_index)++;

    } else if (strcmp(command, "DIV") == 0) {

        *(code_ptr + *current_index) = DIV;
         (*current_index)++;

    } else if (strcmp(command, "IN") == 0) {

        *(code_ptr + *current_index) = IN;
         (*current_index)++;

    } else if (strcmp(command, "OUT") == 0) {

        *(code_ptr + *current_index) = OUT;
         (*current_index)++;

    } else if (strcmp(command, "HLT") == 0) {

        *(code_ptr + *current_index) = HLT;
         (*current_index)++;

    } else if (strcmp(command, "RET") == 0) {

        *(code_ptr + *current_index) = RET;
         (*current_index)++;

    } else if (command[0] == ':') {

        if (!CheckSecondStrMetka(code_ptr, current_index,
                                 command, labels,
                                 pending_add, count_pend))

                                 return false;

    } else if (command[0] == ';') {

        return true;

    } else {

        printf("file %s, line %d invailed command\n", file_name, file_line);
        return false;

    }

    return true;

}

bool GetCommand_2_Args_Str(char* command, char* second_str,
                           const char* file_name, int file_line,
                           type_el_code* code_ptr, int* current_index,
                           int* labels,
                           PendingAddress *pending_add, int* count_pend) {

    assert(command       != NULL);
    assert(second_str    != NULL);
    assert(file_name     != NULL);
    assert(code_ptr      != NULL);
    assert(current_index != NULL);
    assert(pending_add   != NULL);
    assert(count_pend    != NULL);

    if (strcmp(command, "PUSHR") == 0) {

        *(code_ptr + *(current_index)) = PUSHR;
         (*current_index)++;

    } else if (strcmp(command, "POPR") == 0) {

        *(code_ptr + *(current_index)) = POPR;
         (*current_index)++;

    } else if ((strcmp(command, "JB") == 0) || (strcmp(command, "CALL") == 0)) {

         if (!CheckSecondStrJB(code_ptr, current_index,
                            command, second_str,
                            labels,
                            pending_add, count_pend))

                            return false;

    } else if (strcmp(command, "PUSHM") == 0) {

        *(code_ptr + *(current_index)) = PUSHM;
         (*current_index)++;
         if ((second_str[0] == '[') && (second_str[4] == ']')) {

            char* pushm_reg = second_str + 1;
            pushm_reg[3] = '\0';

            if (!SyntaxErrorReg(pushm_reg)) {

                *(code_ptr + *current_index) = (pushm_reg[1] - 'A');
                 (*current_index)++;

            } else {

                return false;

            }

         } else {

            return false;

         }

    } else if (strcmp(command, "POPM") == 0) {

        *(code_ptr + *(current_index)) = POPM;
         (*current_index)++;
         if ((second_str[0] == '[') && (second_str[4] == ']')) {

            char* pushm_reg = second_str + 1;
            pushm_reg[3] = '\0';

            if (!SyntaxErrorReg(pushm_reg)) {

                *(code_ptr + *current_index) = (pushm_reg[1] - 'A');
                 (*current_index)++;

            } else {

                return false;

            }

         } else {

            return false;

         }

    } else if (command[0] == ';') {

        return true;

    } else {

        printf("file %s, line %d invailed command\n", file_name, file_line);
        return false;

    }

    if ((command[0] != 'J') && (!SyntaxErrorReg(second_str))) {

        *(code_ptr + *current_index) = (second_str[1] - 'A');
         (*current_index)++;

    }

    return true;

}

void WriteToFile(FILE* byte_code, type_el_code* code_ptr, int current_index) {

    assert(byte_code != NULL);
    assert(code_ptr  != NULL);

    int index = 0;
    fprintf(byte_code, "%d ", current_index);

    while (index < current_index) {

        fprintf(byte_code, "%.0lf ", code_ptr[index]);
        index++;

    }

}

bool CorrectNum(char* command, long int* num_metka) {

    assert(command   != NULL);
    assert(num_metka != NULL);

    char* command_ch = command + 1;
    char* ptr_end_str1 = strlen(command) + command;
    char* ptr_end_str2 = 0;

    assert(command_ch   != NULL);
    assert(ptr_end_str1 != NULL);

    if (strtol(command_ch, &ptr_end_str2, 10) != 0) {

        if (ptr_end_str2 != ptr_end_str1) {

            return false;

        } else {

            *num_metka = strtol(command_ch, &ptr_end_str2, 10);
            return true;

        }

    }

    return false;

}

CommandStatus FunctionJB(long int num_metka, CommandStatus status, int* current_index, int* labels,
                         type_el_code* code_ptr) {

    assert(current_index != NULL);
    assert(code_ptr      != NULL);
    assert(labels        != NULL);

    if (status == ON_METKA) {

        if (labels[num_metka] == -1) {

            labels[num_metka] = *current_index;
            return METKA_BEFORE;

        }  else if (labels[num_metka] == -2) {

            labels[num_metka] = *current_index;
            return METKA_AFTER;

        } else {

            printf("invalid array labels element value\n");
            return ERROR_LABELS;


        }

    } else {

        if (labels[num_metka] >= 0) {

            *(code_ptr + *(current_index)) = labels[num_metka];
             (*current_index)++;
             return JB_FIND_METKA;


        } else if (labels[num_metka] == -1) {

             labels[num_metka] = -2;
             return JB_NOT_FIND_METKA;

        } else if (labels[num_metka] == -2) {

             return JB_NOT_FIND_METKA;

        }

    }

}

bool CheckSecondStrJB(type_el_code* code_ptr, int* current_index,
                    char* command, char* second_str,
                    int* labels,
                    PendingAddress *pending_add, int* count_pend) {

    CommandCode cmd = (strcmp(command, "JB") == 0) ? JB : CALL;
   *(code_ptr + *(current_index)) = cmd;
    (*current_index)++;

    if (second_str[0] == ':') {

        long int num_metka = 0;
        CommandStatus status = ON_JB;

        if (CorrectNum(second_str, &num_metka)) {

            if (num_metka < 0 || num_metka >= SIZE_LABELS) {

                printf("Invalid label number, expand the array labels");
                return false;

            }

            CommandStatus result = FunctionJB(num_metka, status, current_index, labels, code_ptr);

            if (result == JB_NOT_FIND_METKA) {

                if (*count_pend < SIZE_PENDING) {

                    pending_add[*count_pend].label_num = num_metka;
                    pending_add[*count_pend].code_pos  = *current_index;

                }

                (*current_index)++;
                (*count_pend)++;

            }
        }
    }

    return true;
}

bool CheckSecondStrMetka(type_el_code* code_ptr, int* current_index,
                         char* command, int* labels,
                         PendingAddress *pending_add, int* count_pend) {

    long int num_metka = 0;
    CommandStatus status = ON_METKA;

    if (CorrectNum(command, &num_metka)) {

        CommandStatus result = FunctionJB(num_metka, status, current_index, labels, code_ptr);

        if (result != ERROR_LABELS) {

            for (int i = 0; i < *count_pend; i++) {

                if (pending_add[i].label_num == num_metka)

                    code_ptr[pending_add[i].code_pos] = labels[num_metka];

            }

        } else {

            return false;
        }

    }

    return true;

}

