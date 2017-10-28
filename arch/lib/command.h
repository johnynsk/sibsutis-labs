#ifndef ARCH_LIB_COMMAND_H
#define ARCH_LIB_COMMAND_H
#include "registers.h"

#define COMMAND_ERROR 1

int sc_commandEncode(int8_t command, int8_t operand, int16_t *value);
int sc_commandDecode(int16_t value, int8_t *command, int8_t *operand);


#endif
