#include "command.h"

int sc_commandEncode(int command, int operand, int * value)
{
    trace;
    if (command < 0
        || (command > 0 && command < 10)
        || (command > 11 && command < 20)
        || (command > 21 && command < 30)
        || (command > 43 && command < 51)
        || command > 76
    ) {
        sc_regSet(FLAG_WRONG_COMMAND, 1);
        return COMMAND_ERROR;
    }

    int tmp = 0;
    tmp |= command;
    tmp <<= 7;
    tmp |= operand;
    tmp |= 0 << 14;
    *value = tmp;
    return 0;
}

int sc_commandDecode(int value, int * result_command, int * result_operand)
{
    trace;
    int operand;
    int command;
    int command_flag;

    command_flag = 1 << 14;
    value &= ~command_flag;

    command = (value >> 7) & 255;
    operand = value & (~(command << 7)) & 255;
//    log_debug(sformat("command_flag %s; command = %d; operand = %d", command_flag ? "true": "false", command, operand));
    *result_command = (int)command;
    *result_operand = (int)operand;

    if (command < 10
//        || (command > 0 && command < 10)
        || (command > 11 && command < 20)
        || (command > 21 && command < 30)
        || (command > 43 && command < 51)
        || command > 76
    ) {
//        sc_regSet(FLAG_WRONG_COMMAND, 1);
        return COMMAND_ERROR;
    }

    if (operand < -128 || operand > 127) {
        //sc_regSet(FLAG_OVERFLOW, 1);
        //return COMMAND_ERROR;
    }

    return 0;
}

const char available_commands[77][8] = {
    [0 ... 9] = "",

    [10] = "READ",
    [11] = "WRITE",

    [12 ... 19] = "",

    [20] = "LOAD",
    [21] = "STORE",

    [22 ... 29] = "",

    [30] = "ADD",
    [31] = "SUB",
    [32] = "DIVIDE",
    [33] = "MUL",

    [34 ... 39] = "",

    [40] = "JUMP",
    [41] = "JNEG",
    [42] = "JZ",
    [43] = "HALT",

    [44 ... 50] = "",

    [51] = "NOT",
    [52] = "AND",
    [53] = "OR",
    [54] = "XOR",
    [55] = "JNS", //jump positive value
    [56] = "JC", //jump overflow
    [57] = "JNC",
    [58] = "JP", //jump if acc % 2 == 0
    [59] = "JNP", //jump if acc % 2 != 0

    [60] = "CHL", //logical move left
    [61] = "SHR", //logical move right
    [62] = "RCL", //cycle move left
    [63] = "RCR", //cycle move right
    [64] = "NEG", //negative = equals ~ operator
    [65] = "ADDC", //add to accumulator from memory cell
    [66] = "SUBC", //same as ADDC
    [67] = "LOGLC", //logical move left from memory cell to acc
    [68] = "LOGRC", //logical move right from memory cell to acc
    [69] = "RCCL", //cycle logical move left from memory cell to acc

    [70] = "RCCR", //cycle logical move right from mem to acc
    [71] = "MOVA", //move from memory cell to memory address in acc
    [72] = "MOVR", //move from memory address located in acc to memory cell in operand
    [73] = "MOVCA", //move from memory cell to another memory cell which address located in memory cell address located in acc
    [74] = "MOVCR", //move to memory memory cell contents from another cell which address stored in acc
    [75] = "ADDC", //same as 65
    [76] = "SUBC" // same as 66
};

const char * command_name(int command) {
    trace;
    log_debug(sformat("command %d", command));
    if (command < 0 || command > 76) {
        return "";
    }

    return available_commands[command];
}

int command_id(char * command_name) {
    trace;
//    command_name[strlen(command_name) - 1] = '\0';
    char *nline;
    nline = strstr(command_name, "\n");
    if (nline) {
        nline[0] = '\0';
    }

    const char * upper_name = stoupper(command_name);
    for (int i = 0; i < 77; i++) {
        if (!strcmp(upper_name, available_commands[i])) {
            return i;
        }
    }

    return 0;
}

