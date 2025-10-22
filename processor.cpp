#include <stdio.h>
#include <cstdint>
#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "stack_processing.h"
#include "struct_processor.h"
#include "enum_processor.h"
#include "stack_add.h"
#include "enum_command_code.h"
#include "processor_func.h"

int main(void) {

    Processor prcs = {};

    FILE* byte_code = fopen("C:\\Users\\Соня\\Desktop\\1\\Assembler_code\\byte_code.txt", "r");
    int code_size = ReadByteCode(byte_code, &prcs);

    ErrorType error = ProcessorInit(&prcs, START_CAPACITY, START_RET_CAPACITY, code_size);

    if (error)
        return INCORRECTLY;

    error = ExecutionPrCommand(&prcs, code_size);

    if (error)
        return INCORRECTLY;

    return CORRECTLY;

}
