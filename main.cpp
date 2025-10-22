#include <stdio.h>
#include <string.h>
#include <cassert>
#include "ass_to_byte.h"
#include "enum_command_code.h"
#include "enum_processor.h"
#include "struct_for_file.h"
#include "read_ass_code.h"

int main(void) {

    Sizes size_par = {};

    char* bufer = CorrectReadAndSizeFile(&size_par);

    //type_el_code code[SIZE_CODE]; ///
    //memset(code, 0, sizeof(code));

    int labels[SIZE_LABELS];
    memset(labels, -1, sizeof(labels));

    //type_el_code* code_ptr = code;

    //assert(code_ptr != NULL);

    //ReadAssemblerFile(code_ptr, labels);

    return 0;
}



