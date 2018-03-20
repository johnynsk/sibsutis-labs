#include "registers.h"

int sc_regInit()
{
    vtrace;
    sc_register.accum = 0;
    sc_register.count = 0;
    sc_register.flag = 0;

    return 0;
}

int sc_regSet(int register_id, int value)
{
    vtrace;
    if (value != 1 && value != 0) {
        return ERROR_WRONG_REGISTER_VALUE; //TODO
    }

    log_debug(sformat("register %d value %d", register_id, value));
    log_debug(sformat("before %d", sc_register.flag));

    switch (register_id) {
        case FLAG_OVERFLOW:
        case FLAG_DIVISION_BY_ZERO:
        case FLAG_MEMORY_ERROR:
        case FLAG_TICK_IGNORE:
        case FLAG_WRONG_COMMAND:
            if (value) {
                sc_register.flag |= register_id;
                log_debug(sformat("after %d", sc_register.flag));
                return 0;
            }

            sc_register.flag &= ~register_id;
            log_debug(sformat("after %d", sc_register.flag));
            return 0;
    }

    return ERROR_WRONG_REGISTER_SELECTED;
}

int sc_regGet(int register_id, int *value)
{
    vtrace;
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

int sc_accumGet(int *value)
{
    vtrace;
    *value = sc_register.accum;
    return 0;
}

int sc_accumSet(int value)
{
    vtrace;
    if (value > 127 || value < -128)
        return -1;
    sc_register.accum = value;
    return 0;
}

int sc_instGet(int *value)
{
    vtrace;
    *value = sc_register.count;
    return 0;
}

int sc_instSet(int value)
{
    vtrace;
    if (value >= 100)
        return -1;
    sc_register.count = value;
    return 0;
}


