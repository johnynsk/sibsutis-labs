#include "registers.h"

sc_reg_t sc_register;

int sc_regInit()
{
    sc_register.accum = 0;
    sc_register.count = 0;
    sc_register.flag = 0;

    return 0;
}

int sc_regSet(int8_t register_id, int8_t value)
{
    if (value != 1 && value != 0) {
        return ERROR_WRONG_REGISTER_VALUE; //TODO
    }

    switch (register_id) {
        case FLAG_OVERFLOW:
        case FLAG_DIVISION_BY_ZERO:
        case FLAG_MEMORY_ERROR:
        case FLAG_TICK_IGNORE:
        case FLAG_WRONG_COMMAND:
            if (value) {
                sc_register.flag |= register_id;
                return 0;
            }

            sc_register.flag &= register_id;
            return 0;
    }

    return ERROR_WRONG_REGISTER_SELECTED;
}

int sc_regGet(int8_t register_id, int8_t *value)
{
    switch (register_id)
    {
        case FLAG_OVERFLOW:
        case FLAG_DIVISION_BY_ZERO:
        case FLAG_MEMORY_ERROR:
        case FLAG_TICK_IGNORE:
        case FLAG_WRONG_COMMAND:
            *value = (sc_register.flag & register_id) > 0 ? 1 : 0;
            return 0;
    }

    return ERROR_WRONG_REGISTER_SELECTED;
}
