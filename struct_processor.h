#ifndef STACK_STRUCT_STACK
#define STACK_STRUCT_STACK
#include "enum_processor.h"
typedef double type_stack;
typedef double type_el_code;
const int START_CAPACITY = 5;
const int REGS_SIZE = 16;
const int START_RET_CAPACITY = 10;
const int RAM_SIZE = 100;

struct Stack_t {

    type_stack* data;
    size_t size_stack;
    size_t capacity;

    };

struct Stack_ret {

    int* stack_return;
    size_t size_stack_return;
    size_t capacity_stack_return;

    };

struct Processor {

    Stack_t stack_all;
    type_el_code* code;
    int programm_counter;
    int size_code;
    type_el_code regs[REGS_SIZE];
    Stack_ret stack_ret_all;
    int RAM[RAM_SIZE];

    };

#endif
