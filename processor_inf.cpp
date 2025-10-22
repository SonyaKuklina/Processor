#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "processor_inf.h"
#include "stack_processing.h"
#include "struct_processor.h"
#include "enum_processor.h"
#include "stack_add.h"

#define CANARY_USE 1

void StackInformation(Stack_t* stack_all, const char* file, int line) {

    printf("Stack[%p]\n", stack_all);
    printf("{                   \n");
    printf("    size = %zu      \n", (stack_all -> size_stack));
    printf("    capacity = %zu  \n", (stack_all -> capacity));
    printf("    data [%p]       \n", (stack_all -> data));
    printf("    {               \n");
    for (size_t index = 0; index < (stack_all -> size_stack); index++) {
        printf("        *[%lld] = %g\n", index, stack_all -> data[index]);
    }
    for (size_t index = (stack_all -> size_stack);
                    index < (stack_all -> capacity); index++) {
        printf("         [%lld] = %g\n", index, stack_all -> data[index]);
    }
    printf("    }             \n");
    printf("}\n");

}

void StackReturnInformation(Stack_ret* stack_ret_all, const char* file, int line) {

    printf("Stack_ret[%p]\n", stack_ret_all);
    printf("{                   \n");
    printf("    size = %zu      \n", (stack_ret_all -> size_stack_return));
    printf("    capacity = %zu  \n", (stack_ret_all -> capacity_stack_return));
    printf("    stack_return [%p]       \n", (stack_ret_all -> stack_return));
    printf("    {               \n");
    for (size_t index = 0; index < (stack_ret_all -> size_stack_return); index++) {
        printf("        *[%lld] = %g\n", index, stack_ret_all -> stack_return[index]);
    }
    for (size_t index = (stack_ret_all -> size_stack_return);
                    index < (stack_ret_all -> capacity_stack_return); index++) {
        printf("         [%lld] = %g\n", index, stack_ret_all -> stack_return[index]);
    }
    printf("    }             \n");
    printf("}\n");

}

void ProcessorInformation(Processor* prcs, const char* file, int line) {

    assert(file != NULL);

    fprintf(stderr, "ProcessorInformation called from %s: %d\n", file, line);
    printf("code[%p]\n", (prcs -> code));
    printf("programm_counter = %d\n", (prcs -> programm_counter));
    printf("size_code = %d\n", (prcs -> size_code));
    printf("processors registres:\n");
    for (int i_reg = 0; i_reg < REGS_SIZE; i_reg++) {
        printf("%lf ", prcs -> regs[i_reg]);
    }
    printf("\n");
    StackInformation(&(prcs -> stack_all), file, line);
    StackReturnInformation(&(prcs -> stack_ret_all), file, line);

}

void PrintErrors(ErrorType error) {

    if ((error & NULL_POINTER_PRCS) != 0) {

        printf("ERROR: null pointer to processor\n");

    }

    if ((error & PROGRAMM_CODE_ERR) != 0) {

        printf("ERROR: invalid value of programm_code\n");

    }

    if ((error & NULL_POINTER_DATA) != 0) {

        printf("ERROR: null pointer to data in stack_all\n");

    }

    if ((error & CANARY_LEFT) != 0) {

        printf("ERROR: stack attacked from the left\n");

    }

    if ((error & CANARY_RIGHT) != 0) {

        printf("ERROR: stack attacked from the right\n");

    }

    if ((error & MEMORY_ALLOC_ERR) != 0) {

        printf("ERROR: memory not allocated\n");

    }

    if ((error & STACK_EMPTY) != 0) {

        printf("ERROR: not take an element from an empty stack.\n");
    }

}

