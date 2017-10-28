#ifndef ARCH_LIB_REGISTERS_H
#define ARCH_LIB_REGISTERS_H
#include <stdint.h>

#define ERROR_WRONG_REGISTER_SELECTED 1
#define ERROR_WRONG_REGISTER_VALUE 2

typedef enum {
    FLAG_OVERFLOW = 1,
    FLAG_DIVISION_BY_ZERO = 2,
    FLAG_MEMORY_ERROR = 3,
    FLAG_TICK_IGNORE = 4,
    FLAG_WRONG_COMMAND = 5
} sc_flag_t;

typedef struct {
    int16_t accum;
    int8_t count;
    int8_t flag;
} sc_reg_t;

int sc_regInit();
int sc_regSet(int8_t register_id, int8_t value);
int sc_regGet(int8_t register_id, int8_t * value);

#endif
