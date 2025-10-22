#ifndef ENUM_COMMAND_CODE
#define ENUM_COMMAND_CODE

enum CommandCode {
    PUSH = 1,
    ADD,
    MUL,
    SUB,
    SQRT,
    DIV,
    OUT,
    HLT,
    IN,
    PUSHR = 33,
    POPR = 42,
    JB = 50,
    JE,
    JA,
    CALL = 70,
    RET = 71,
    PUSHM = 80,
    POPM = 81,

};

#endif
