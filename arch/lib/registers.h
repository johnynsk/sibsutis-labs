#ifndef ARCH_LIB_REGISTERS_H
#define ARCH_LIB_REGISTERS_H
#include <stdint.h>
#include <stdlib.h>
#include "log.h"

#define ERROR_WRONG_REGISTER_SELECTED 1
#define ERROR_WRONG_REGISTER_VALUE 2


typedef enum {
    FLAG_OVERFLOW = 1,
    FLAG_DIVISION_BY_ZERO = 2,
    FLAG_MEMORY_ERROR = 4,
    FLAG_TICK_IGNORE = 8,
    FLAG_WRONG_COMMAND = 16
} sc_flag_t;

typedef struct {
    int accum;
    int count;
    int flag;
} sc_reg_t;
sc_reg_t sc_register;

int sc_regInit();
int sc_regSet(int register_id, int value);
int sc_regGet(int register_id, int * value);
int sc_accumGet(int * value);
int sc_accumSet(int value);
int sc_instGet(int * value);
int sc_instSet(int value);
#endif
