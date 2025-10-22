#ifndef PROCESSOR_FUNC
#define PROCESSOR_FUNC

#include "struct_processor.h"


ErrorType ProcessorInit(Processor* prcs, size_t capacity, size_t capacity_ret, int code_size);

ErrorType ProcessorVerify(Processor* prcs);

int ReadByteCode(FILE* byte_code, Processor* prcs);

ErrorType ExecutionPrCommand(Processor* prcs, int code_size);

ErrorType ProcessorDestroy(Processor* prcs);

#endif


