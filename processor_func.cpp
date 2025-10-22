#include <stdio.h>
#include <cstdint>
#include <assert.h>
#include <math.h>
#include "stack_processing.h"
#include "struct_processor.h"
#include "enum_processor.h"
#include "stack_add.h"
#include "enum_command_code.h"
#include "processor_func.h"
#include "processor_inf.h"

#define PROCESSOR_INFORMATION(x) ProcessorInformation((x), __FILE__, __LINE__)

ErrorType ProcessorInit(Processor* prcs, size_t capacity, size_t capacity_ret, int code_size) {

    assert(prcs != NULL);

    ErrorType error = SUCCESS;

    StackInit(&(prcs -> stack_all), capacity, &error);
    StackReturnInit(&(prcs -> stack_ret_all), capacity_ret, &error);

    (prcs -> programm_counter)     = 0;
    (prcs -> size_code)            = code_size;
    memset((prcs -> regs), 0, REGS_SIZE * sizeof(type_el_code));
    memset((prcs -> RAM), 0, RAM_SIZE * sizeof(int));

    return error;

}

ErrorType ProcessorVerify(Processor* prcs) {

    assert(prcs != NULL);

    ErrorType error = SUCCESS;

    if (prcs == NULL)

        error |= NULL_POINTER_PRCS;

    if ((prcs -> programm_counter) > (prcs -> size_code))

        error |= PROGRAMM_CODE_ERR;

    ErrorType error_stack = StackVerify(&(prcs -> stack_all));
    error |= error_stack;

    return error;

}

ErrorType ProcessorDestroy(Processor* prcs) {

    assert(prcs != NULL);

    ErrorType error = ProcessorVerify(prcs);

    error = StackDestroy(&(prcs -> stack_all));

    ERROR;

    free(prcs -> code);

    (prcs -> code)             = NULL;
    (prcs -> programm_counter) = NAN;
    (prcs -> size_code)        = NAN;

    for (int i = 0; i < REGS_SIZE; i++)
        (prcs -> regs[i]) = NAN;

    return error;

}

int ReadByteCode(FILE* byte_code, Processor* prcs) {

    assert(byte_code != NULL);
    assert(prcs      != NULL);

    int code_size = 0;
    fscanf(byte_code, "%d", &code_size);

    (prcs -> code) = (type_stack*)calloc(code_size, sizeof(type_el_code));

    assert((prcs -> code) != NULL);

    int index = 0;

    while (index < code_size) {

          fscanf(byte_code, "%lf", ((prcs -> code) + index));
          index++;

    }

    return code_size;

}

ErrorType ExecutionPrCommand(Processor* prcs, int code_size) {

     assert(prcs != NULL);

     if ((code_size <= 0) || ((prcs -> code) == NULL)) {

        return CODE_ERROR;

     }

     int index = (prcs -> programm_counter);
     ErrorType error = SUCCESS;
     bool not_hlt = true;

     while (index < code_size) {

         CommandCode command_now = (CommandCode)(prcs -> code[index]);
         index++;
         (prcs -> programm_counter)++;

         switch (command_now) {

         case PUSH:  error = PushToStack(prcs, index);
                     index++;
                     (prcs -> programm_counter)++;
                     break;

         case ADD:   error = AddToStack(prcs);
                     break;

         case MUL:   error = MulToStack(prcs);
                     break;

         case SUB:   error = SubToStack(prcs);
                     break;

         case SQRT:  error = SqrtToStack(prcs);
                     break;

         case DIV:   error = DivToStack(prcs);
                     break;

         case IN:    error = InToStack(prcs);
                     break;

         case OUT:   error = OutToStack(prcs);
                     break;

         case PUSHR: error = PushRToStack(prcs, index);
                     index++;
                     (prcs -> programm_counter)++;
                     break;

         case POPR:  error = PopRToStack(prcs, index);
                     index++;
                     (prcs -> programm_counter)++;
                     break;

         case JB:    error = JBToStack(prcs, &index);
                     (prcs -> programm_counter) = index;
                     break;

         case JE:    error = JEToStack(prcs, &index);
                     (prcs -> programm_counter) = index;
                     break;

         case JA:    error = JAToStack(prcs, &index);
                     (prcs -> programm_counter) = index;
                     break;

         case CALL:  error = CallToStack(prcs, &index);
                     (prcs -> programm_counter) = index;
                     break;

         case RET:   error = RetToStack(prcs, &index);
                     (prcs -> programm_counter) = index;
                     break;

         case PUSHM: error = PushmToStack(prcs, index);
                     index++;
                     (prcs -> programm_counter)++;
                     break;

         case POPM:  error = PopmToStack(prcs, index);
                     index++;
                     (prcs -> programm_counter)++;
                     break;

         case HLT:   not_hlt = false;
                     break;

         default:   assert(0);

         } ;

         if (!not_hlt)
            break;

         //PROCESSOR_INFORMATION(prcs);

    }

    return error;
}


