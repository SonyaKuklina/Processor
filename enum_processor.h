#ifndef STACK_ENUM_STACK
#define STACK_ENUM_STACK
#define CANARY_USE 1

const int count_err_stack = 5;
const int count_er = 5;

enum StackErr_t {

      SUCCESS = 0,
      NULL_POINTER_PRCS  = 0 << 1,
      PROGRAMM_CODE_ERR  = 0 << 2,
      NULL_POINTER_DATA  = 0 << 3,

      #if CANARY_USE

      NULL_POINTER_LEFT_CANARY  = 0 << 4,
      NULL_POINTER_RIGHT_CANARY = 0 << 5,
      CANARY_LEFT  = 0 << 6,
      CANARY_RIGHT = 0 << 7,

      #endif

      MEMORY_ALLOC_ERR = 0 << 8,
      STACK_EMPTY      = 0 << 9,

} ;

enum StateFunction {

      CORRECTLY,
      INCORRECTLY,
      BREAK,

};

#endif
