#ifndef STACK_ENUM_STACK
#define STACK_ENUM_STACK
#define CANARY_USE 1
const int count_err_stack = 5;
const int count_er = 5;

enum Err_t {

      SUCCESS = 0,
      NULL_POINTER_PRCS         = 1 << 0,
      PROGRAMM_CODE_ERR         = 1 << 1,
      NULL_POINTER_DATA         = 1 << 2,
      INVAILED_CAPACITY_DATA    = 1 << 3,
      INVAILED_CAPACITY_RET     = 1 << 4,
      SIZE_LARGER_CAPACITY_DATA = 1 << 5,
      SIZE_LARGER_CAPACITY_RET  = 1 << 6,

      #if CANARY_USE

      CANARY_LEFT  = 1 << 7,
      CANARY_RIGHT = 1 << 8,

      #endif

      MEMORY_ALLOC_ERR          = 1 << 9,
      STACK_EMPTY               = 1 << 10,
      NULL_POINTER_STACK_RETURN = 1 << 11,
      DIV_BY_ZERO               = 1 << 12,
      INVAILED_REG              = 1 << 13,
      INVAILED_RAM_ADDRESS      = 1 << 14,
      CODE_ERROR                = 1 << 15,

} ;

enum StateFunction {

    CORRECTLY,
    INCORRECTLY,
    BREAK,

};

#endif
