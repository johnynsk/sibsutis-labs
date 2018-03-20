#ifndef ARCH_LIB_COMMAND_H
#define ARCH_LIB_COMMAND_H
#include "registers.h"

#define COMMAND_ERROR 1

int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);


#endif
