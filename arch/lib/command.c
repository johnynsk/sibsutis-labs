#include "command.h"

int sc_commandEncode(int8_t command, int8_t operand, int16_t *value)
{
    if ((operand > 11 && operand < 20) || (operand > 21 && operand < 30) || (operand > 43 && operand < 51) || operand > 76) {
        sc_regSet(FLAG_WRONG_COMMAND, 1);
        return COMMAND_ERROR;
    }

    int16_t tmp = 0;
    tmp |= command;
    tmp <<= 7;
    tmp |= operand;
    tmp |= 0 << 14;
    *value = tmp;
    return 0;
}

int sc_commandDecode(int16_t value, int8_t *command, int8_t *operand)
{
    if ((value & (1 << 14)) != 0) {
        sc_regSet(FLAG_WRONG_COMMAND, 1);
        return COMMAND_ERROR;
    }

    *operand = (int8_t) (value);
    *operand &= ~(1 << 7);
    *command = (int8_t) (value >> 7);
    return 0;
}
