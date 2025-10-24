#ifndef STACK_STACK_PROCESSING
#define STACK_STACK_PROCESSING
#include "struct_processor.h"
#define CANARY_USE 1
#define ERROR if (error) return error
#include <cstdint>
#include <string.h>

typedef uint32_t ErrorType;

#if CANARY_USE

const int TWO_CANARY = 2;
const type_stack LEFT_CANARY = 0x8BADF00D;
const type_stack RIGHT_CANARY = 0x1BADB002;

#endif

void StackInit(Stack_t* stack_all, size_t capacity, ErrorType* error);

void StackReturnInit(Stack_ret* stack_ret_all, size_t capacity_ret, ErrorType* error);

ErrorType StackPush(Stack_t* stack_all, type_stack value);

ErrorType StackReturnPush(Stack_ret* stack_ret_all, int value);

ErrorType StackDestroy(Stack_t* stack_all);

ErrorType StackReturnDestroy(Stack_ret* stack_ret_all);

ErrorType StackPop(Stack_t* stack_all, type_stack* last_element);

ErrorType StackReturnPop(Stack_ret* stack_ret_all, int* last_element);

static ErrorType StackExpansion(Stack_t* stack_all);

static ErrorType StackReturnExpansion(Stack_ret* stack_ret_all);

ErrorType StackVerify(Stack_t* stack_all);

ErrorType StackReturnVerify(Stack_ret* stack_ret_all);

ErrorType PushToStack(Processor* prcs, int* index);

ErrorType AddToStack(Processor* prcs);

ErrorType MulToStack(Processor* prcs);

ErrorType SubToStack(Processor* prcs);

ErrorType SqrtToStack(Processor* prcs);

ErrorType DivToStack(Processor* prcs);

ErrorType InToStack(Processor* prcs);

ErrorType OutToStack(Processor* prcs);

ErrorType HltToStack(Processor* prcs);

ErrorType PushRToStack(Processor* prcs, int* index);

ErrorType PopRToStack(Processor* prcs, int* index);

ErrorType JBToStack(Processor* prcs, int* index);

ErrorType JEToStack(Processor* prcs, int* index);

ErrorType JAToStack(Processor* prcs, int* index);

ErrorType CallToStack(Processor* prcs, int* index);

ErrorType RetToStack(Processor* prcs, int* index);

ErrorType PushmToStack(Processor* prcs, int* index);

ErrorType PopmToStack(Processor* prcs, int* index);

#endif
