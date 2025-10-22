#ifndef STACK_STACK_ERRORS
#define STACK_STACK_ERRORS
#include "struct_processor.h"
#include "stack_processing.h"

void StackInformation(Stack_t* stack_all, const char* file, int line);

void StackReturnInformation(Stack_ret* stack_ret_all, const char* file, int line);

void ProcessorInformation(Processor* prcs,
                          const char* file, int line);

void PrintErrors(ErrorType error);

#endif
