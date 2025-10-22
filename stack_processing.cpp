#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include <cstdint>
#include "stack_processing.h"
#include "struct_processor.h"
#include "enum_processor.h"
#include "processor_inf.h"
#include "stack_add.h"
#include "enum_command_code.h"
#define STACK_INFORMATION(x) StackInformation((x), __FILE__, __LINE__)
#define CANARY_USE 1


void StackInit(Stack_t* stack_all, size_t capacity, ErrorType* error) {

    assert(stack_all != NULL);
    assert(error     != NULL);

    if (capacity == 0) {

        *error |= INVAILED_CAPACITY_DATA;
         return;
    }

    #if CANARY_USE

    type_stack* new_memory = (type_stack*)calloc(capacity + TWO_CANARY, sizeof(type_stack));

    if (new_memory == NULL)
        *error |= MEMORY_ALLOC_ERR;

    (stack_all -> data)               = new_memory + 1;
   *((stack_all -> data) - 1 )        = LEFT_CANARY;
   *((stack_all -> data) + capacity)  = RIGHT_CANARY;

    #else

    type_stack* new_memory = (type_stack*)calloc(capacity, sizeof(type_stack));

    if (new_memory == NULL)
        *error |= MEMORY_ALLOC_ERR;

    (stack_all -> data) = new_memory;

    #endif

    (stack_all -> capacity)   = capacity;
    (stack_all -> size_stack) = 0;


}

void StackReturnInit(Stack_ret* stack_ret_all, size_t capacity_ret, ErrorType* error) {

    assert(stack_ret_all != NULL);
    assert(error         != NULL);

    if (capacity_ret == 0) {

        *error |= INVAILED_CAPACITY_RET;
         return;
    }

    int* new_ret_memory = (int*)calloc(capacity_ret, sizeof(int));

    if (new_ret_memory == NULL) {

        *error |= MEMORY_ALLOC_ERR;
         return;
    }

    (stack_ret_all -> stack_return) = new_ret_memory;

    (stack_ret_all -> capacity_stack_return)   = capacity_ret;
    (stack_ret_all -> size_stack_return) = 0;

}

ErrorType StackPush(Stack_t* stack_all, type_stack value) {

    assert(!IsNAN(value));

    ErrorType error = StackVerify(stack_all);

    ERROR;

    if ((stack_all -> size_stack) >= (stack_all -> capacity)) {

        error = StackExpansion(stack_all);
        ERROR;

    }

    (stack_all -> data[(stack_all -> size_stack)]) = value;
    (stack_all -> size_stack)++;

    return error;

}

ErrorType StackReturnPush(Stack_ret* stack_ret_all, int value) {

    assert(!IsNAN(value));

    ErrorType error = StackReturnVerify(stack_ret_all);

    ERROR;

    if ((stack_ret_all -> size_stack_return) >= (stack_ret_all -> capacity_stack_return)) {

        error = StackReturnExpansion(stack_ret_all);
        ERROR;

    }

    (stack_ret_all -> stack_return[(stack_ret_all -> size_stack_return)]) = value;
    (stack_ret_all -> size_stack_return)++;

    return error;

}

ErrorType StackDestroy(Stack_t* stack_all) {

    ErrorType error = StackVerify(stack_all);
    ERROR;

    #if CANARY_USE
    free(stack_all -> data - 1);
    #else
    free(stack_all -> data);
    #endif

    (stack_all -> data)       = NULL;
    (stack_all -> size_stack) = NAN;
    (stack_all -> capacity)   = NAN;

    return error;

}

ErrorType StackReturnDestroy(Stack_ret* stack_ret_all) {

    ErrorType error = StackReturnVerify(stack_ret_all);
    ERROR;

    free(stack_ret_all -> stack_return);

    (stack_ret_all -> stack_return)          = NULL;
    (stack_ret_all -> size_stack_return)     = NAN;
    (stack_ret_all -> capacity_stack_return) = NAN;

    return error;

}

ErrorType StackPop(Stack_t* stack_all, type_stack* last_element) {


    assert(stack_all    != NULL);
    assert(last_element != NULL);

    ErrorType error = StackVerify(stack_all);

    if ((stack_all -> size_stack) == 0) {
        error |= STACK_EMPTY;
        return error;
    }

    *last_element = (stack_all -> data[(stack_all -> size_stack) - 1]);
    (stack_all -> data[(stack_all -> size_stack) - 1]) = 0;
    (stack_all -> size_stack)--;

    return error;

}

ErrorType StackReturnPop(Stack_ret* stack_ret_all, int* last_element) {


    assert(stack_ret_all != NULL);
    assert(last_element  != NULL);

    ErrorType error = StackReturnVerify(stack_ret_all);

    if ((stack_ret_all -> size_stack_return) == 0) {
        error |= STACK_EMPTY;
        return error;
    }

    *last_element = (stack_ret_all -> stack_return[(stack_ret_all -> size_stack_return) - 1]);
    (stack_ret_all -> stack_return[(stack_ret_all -> size_stack_return) - 1]) = 0;
    (stack_ret_all -> size_stack_return)--;

    return error;

}

static ErrorType StackExpansion(Stack_t* stack_all) {

     assert(stack_all != NULL);

     size_t capacity_t   = (stack_all -> capacity);
     size_t size_stack_t = (stack_all -> size_stack);

     #if CANARY_USE

     type_stack* old_data_ptr = (stack_all -> data) - 1;

     assert(old_data_ptr != NULL);

     type_stack* new_data_ptr = (type_stack*)realloc(old_data_ptr,
                                (capacity_t * 2 + TWO_CANARY) * sizeof(type_stack));

     if (new_data_ptr == NULL) {

        free(old_data_ptr);
        return MEMORY_ALLOC_ERR;

     }

     old_data_ptr = new_data_ptr;

     for (size_t index = capacity_t + 1; index < capacity_t * 2 + 1; index++)
         *(old_data_ptr + index) = 0;

     capacity_t *= 2;
     (stack_all -> data)                 = old_data_ptr + 1;
    *((stack_all -> data) + capacity_t)  = RIGHT_CANARY;
    *((stack_all -> data) - 1)           = LEFT_CANARY;
     (stack_all -> capacity)             = capacity_t;

     #else

     type_stack* old_data_ptr = (stack_all -> data);

     assert(old_data_ptr != NULL);

     type_stack* new_data_ptr = (type_stack*)realloc(old_data_ptr,
                                (capacity_t * 2) * sizeof(type_stack));

     if (new_data_ptr == NULL) {

        free(old_data_ptr);
        return MEMORY_ALLOC_ERR;

     }

     old_data_ptr = new_data_ptr;

     for (size_t index = capacity_t; index < capacity_t * 2; index++)
         *(old_data_ptr + index) = 0;

     capacity_t *= 2;
     (stack_all -> data)     = old_data_ptr;
     (stack_all -> capacity) = capacity_t;


     #endif

     return SUCCESS;

}

static ErrorType StackReturnExpansion(Stack_ret* stack_ret_all) {

     assert(stack_ret_all != NULL);

     size_t capacity_t   = (stack_ret_all -> capacity_stack_return);
     size_t size_stack_t = (stack_ret_all -> size_stack_return);

     int* old_stack_ptr = (stack_ret_all -> stack_return);

     assert(old_stack_ptr != NULL);

     int* new_stack_ptr = (int*)realloc(old_stack_ptr,
                                (capacity_t * 2) * sizeof(int));

     if (new_stack_ptr == NULL) {

        free(old_stack_ptr);
        return MEMORY_ALLOC_ERR;

     }

     old_stack_ptr = new_stack_ptr;

     for (size_t index = capacity_t; index < capacity_t * 2; index++)
         *(old_stack_ptr + index) = 0;

     capacity_t *= 2;
     (stack_ret_all -> stack_return)          = old_stack_ptr;
     (stack_ret_all -> capacity_stack_return) = capacity_t;

     return SUCCESS;

}


ErrorType StackVerify(Stack_t* stack_all) {

    assert(stack_all != NULL);

    ErrorType error_stack = SUCCESS;

    if ((stack_all -> data) == NULL)

        error_stack |= NULL_POINTER_DATA;

    if ((stack_all -> size_stack) > (stack_all -> capacity))

        error_stack |= SIZE_LARGER_CAPACITY_DATA;

    #if CANARY_USE

    if (!CompareSuccess(*((stack_all -> data) - 1) , LEFT_CANARY)) {

        error_stack |= CANARY_LEFT;

    }

    if (!CompareSuccess(*((stack_all -> data) + (stack_all -> capacity)), RIGHT_CANARY)) {

        error_stack |= CANARY_RIGHT;

    }

    #endif

    return error_stack;


}

ErrorType StackReturnVerify(Stack_ret* stack_ret_all) {

    assert(stack_ret_all != NULL);

    ErrorType error_ret_stack = SUCCESS;

    if ((stack_ret_all -> stack_return) == NULL)

        error_ret_stack |= NULL_POINTER_STACK_RETURN;

    if ((stack_ret_all -> size_stack_return) > (stack_ret_all -> capacity_stack_return))

        error_ret_stack |= SIZE_LARGER_CAPACITY_RET;

    return error_ret_stack;

}

ErrorType PushToStack(Processor* prcs, int index) {

      assert(prcs != NULL);
      type_stack element = (prcs -> code[index]);
      ErrorType error = StackPush(&(prcs -> stack_all), element);
      return error;

}

ErrorType AddToStack(Processor* prcs) {

      assert(prcs != NULL);

      type_stack element_1 = 0, element_2 = 0;
      ErrorType error = StackPop(&(prcs -> stack_all), &element_1);

      ERROR;

      error = StackPop(&(prcs -> stack_all), &element_2);

      ERROR;

      error = StackPush(&(prcs -> stack_all), element_1 + element_2);

      return error;

}

ErrorType MulToStack(Processor* prcs) {

      assert(prcs != NULL);

      type_stack element_1 = 0, element_2 = 0;
      ErrorType error = StackPop(&(prcs -> stack_all), &element_1);

      ERROR;

      error = StackPop(&(prcs -> stack_all), &element_2);

      ERROR;

      error = StackPush(&(prcs -> stack_all), element_1 * element_2);

      return error;
}

ErrorType SubToStack(Processor* prcs) {

      assert(prcs != NULL);

      type_stack element_1 = 0, element_2 = 0;
      ErrorType error = StackPop(&(prcs -> stack_all), &element_1);

      ERROR;

      error = StackPop(&(prcs -> stack_all), &element_2);

      ERROR;

      error = StackPush(&(prcs -> stack_all), element_2 - element_1);

      return error;

}

ErrorType SqrtToStack(Processor* prcs) {

      assert(prcs != NULL);

      type_stack element_1 = 0;
      ErrorType error = StackPop(&(prcs -> stack_all), &element_1);

      ERROR;

      type_stack sqrt_last_el = sqrt(element_1 * 1e6) / 1e3;

      error = StackPush(&(prcs -> stack_all), sqrt_last_el);

      return error;
}

ErrorType DivToStack(Processor* prcs) {

      assert(prcs != NULL);

      type_stack element_1 = 0, element_2 = 0;
      ErrorType error = StackPop(&(prcs -> stack_all), &element_1);

      ERROR;

      error = StackPop(&(prcs -> stack_all), &element_2);

      ERROR;

      if (CompareSuccess(element_1, 0)) {

            return DIV_BY_ZERO;

      } else {

            error = StackPush(&(prcs -> stack_all), element_2 / element_1);
      }

      return error;

}

ErrorType InToStack(Processor* prcs) {

    assert(prcs != NULL);

    type_stack element = 0;
    scanf("%lf", &element);
    ErrorType error = StackPush(&(prcs -> stack_all), element);
    return error;

}

ErrorType OutToStack(Processor* prcs) {

    assert(prcs != NULL);

    type_stack element = 0;
    ErrorType error = StackPop(&(prcs -> stack_all), &element);
    ERROR;
    printf("%lf\n", element);
    return error;

}

ErrorType PushRToStack(Processor* prcs, int index) {

    assert(prcs != NULL);

    int index_reg = (int)(prcs -> code[index]);

    if (index_reg < 0 || index_reg >= REGS_SIZE) {
        return INVAILED_REG;
    }

    type_stack reg_el = (prcs -> regs[index_reg]);
    ErrorType error = StackPush(&(prcs -> stack_all), reg_el);
    return error;

}

ErrorType PopRToStack(Processor* prcs, int index) {

    assert(prcs != NULL);

    type_stack element = 0;
    int index_reg = (int)(prcs -> code[index]);

    if (index_reg < 0 || index_reg >= REGS_SIZE) {
        return INVAILED_REG;
    }

    ErrorType error = StackPop(&(prcs -> stack_all), &element);
    ERROR;
    (prcs -> regs[index_reg]) = element;
    return error;

}

ErrorType JBToStack(Processor* prcs, int* index) {

    assert(prcs  != NULL);
    assert(index != NULL);

    type_stack element_1 = 0, element_2 = 0;
    ErrorType error = StackPop(&(prcs -> stack_all), &element_1);

    ERROR;

    error = StackPop(&(prcs -> stack_all), &element_2);

    ERROR;

    if (El_1_Less_El_2(element_2, element_1)) {

         int jump_add = (int)(prcs -> code[*index]);
         *index = jump_add;

    } else {

        *index += 1;
    }

    return error;

}

ErrorType JEToStack(Processor* prcs, int* index) {

    assert(prcs  != NULL);
    assert(index != NULL);

    type_stack element_1 = 0, element_2 = 0;
    ErrorType error = StackPop(&(prcs -> stack_all), &element_1);

    ERROR;

    error = StackPop(&(prcs -> stack_all), &element_2);

    ERROR;

    if (CompareSuccess(element_1, element_2)) {

         int jump_add = (int)(prcs -> code[*index]);
         *index = jump_add;

    } else {

         *index += 1;
    }

    return error;

}

ErrorType JAToStack(Processor* prcs, int* index) {

    assert(prcs  != NULL);
    assert(index != NULL);

    type_stack element_1 = 0, element_2 = 0;
    ErrorType error = StackPop(&(prcs -> stack_all), &element_1);

    ERROR;

    error = StackPop(&(prcs -> stack_all), &element_2);

    ERROR;

    if (El_1_More_El_2(element_2, element_1)) {

         int jump_add = (int)(prcs -> code[*index]);
         *index = jump_add;

    } else {

        *index += 1;
    }

    return error;

}

ErrorType CallToStack(Processor* prcs, int* index) {

    assert(prcs  != NULL);
    assert(index != NULL);

    int address_return = *index + 1;
    ErrorType error = StackReturnPush(&(prcs -> stack_ret_all), address_return);

    ERROR;

    int jump_add = (int)(prcs -> code[*index]);
    *index = jump_add;

    return error;

}

ErrorType RetToStack(Processor* prcs, int* index) {

    assert(prcs  != NULL);
    assert(index != NULL);

    int element_ret = 0;
    ErrorType error = StackReturnPop(&(prcs -> stack_ret_all), &element_ret);

    ERROR;

    *index = element_ret;

    return error;

}

ErrorType PushmToStack(Processor* prcs, int index) {

    assert(prcs != NULL);

    int index_reg = (int)(prcs -> code[index]);

    if (index_reg < 0 || index_reg >= REGS_SIZE) {
        return INVAILED_REG;
    }

    int ram_address = (int)(prcs->regs[index_reg]);

    if (ram_address < 0 || ram_address >= RAM_SIZE) {
        return INVAILED_RAM_ADDRESS;
    }

    int ram_el = (prcs -> RAM[(int)(prcs -> regs[index_reg])]);
    ErrorType error = StackPush(&(prcs -> stack_all), (type_stack)ram_el);
    return error;

}

ErrorType PopmToStack(Processor* prcs, int index) {

    assert(prcs != NULL);

    type_stack element = 0;
    ErrorType error = StackPop(&(prcs -> stack_all), &element);

    int index_reg = (int)(prcs -> code[index]);

    if ((index_reg < 0) || (index_reg >= REGS_SIZE)) {
        return INVAILED_REG;
    }

    int ram_address = (int)(prcs -> regs[index_reg]);

    if ((ram_address < 0) || (ram_address >= RAM_SIZE)) {
        return INVAILED_RAM_ADDRESS;
    }

    (prcs -> RAM[(int)(prcs -> regs[index_reg])]) = (int)element;
    return error;

}


