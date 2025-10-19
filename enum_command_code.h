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
    CALL = 70,
    RET = 71,
};

enum CommandStatus {

    ON_JB = 0,
    ON_METKA,
    METKA_BEFORE,
    METKA_AFTER,
    JB_FIND_METKA,
    JB_NOT_FIND_METKA,
    ERROR_LABELS,

};

#endif
