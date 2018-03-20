#include "units.h"

void CU()
{
    trace;
    int tick_ignore;
    int current_instruction;
    int memory_contents;
    sc_instGet(&current_instruction);
    log_debug(sformat("current_instruction %d", current_instruction));
    sc_memoryGet(current_instruction, &memory_contents);

    int command;
    int operand;
    if (sc_commandDecode(memory_contents, &command, &operand)) {
        sc_regSet(FLAG_WRONG_COMMAND, 1);
        sc_regSet(FLAG_TICK_IGNORE, 1);
        return;
    }

    ALU(command, operand);
    int had_overflow;
    sc_regGet(FLAG_OVERFLOW, &had_overflow);
    if (had_overflow) {
        sc_regSet(FLAG_TICK_IGNORE, 1);
        return;
    }

    sc_regGet(FLAG_TICK_IGNORE, &tick_ignore);
    if (tick_ignore) {
        return;
    }

    int new_instruction;
    sc_instGet(&new_instruction);

    if (new_instruction != current_instruction) {
        return;
    }

    current_instruction++;

    if (current_instruction < 0 || current_instruction > 99) {
        sc_regSet(FLAG_TICK_IGNORE, 1);
        return;
    }

    sc_instSet(current_instruction);
}

int ALU(int command, int operand)
{
    trace;
    if (command == 10) {
        return command_read(operand);
    } else if (command == 11) {
        return command_write(operand);
    } else if (command == 20) {
        return command_load(operand);
    } else if (command == 21) {
        return command_store(operand);
    } else if (command == 30) {
        return command_add(operand);
    } else if (command == 31) {
        return command_sub(operand);
    } else if (command == 32) {
        return command_divide(operand);
    } else if (command == 33) {
        return command_mul(operand);
    } else if (command == 40) {
        return command_jump(operand);
    } else if (command == 41) {
        return command_jneg(operand);
    } else if (command == 42) {
        return command_jz(operand);
    } else if (command == 43) {
        return command_halt();
    } else if (command == 51) {
        return command_not(operand);
    } else if (command == 52) {
        return command_and(operand);
    } else if (command == 53) {
        return command_or(operand);
    } else if (command == 54) {
        return command_xor(operand);
    } else if (command == 55) {
        return command_jns(operand);
    } else if (command == 56) {
        return command_jc(operand);
    } else if (command == 57) {
        return command_jnc(operand);
    } else if (command == 58) {
        return command_jp(operand);
    } else if (command == 59) {
        return command_jnp(operand);
    } else if (command == 60) {
        return command_chl(operand);
    } else if (command == 61) {
        return command_shr(operand);
    } else if (command == 62) {
        return command_rcl(operand);
    } else if (command == 63) {
        return command_rcr(operand);
    } else if (command == 64) {
        return command_neg(operand);
    } else if (command == 65 || command == 75) {
        return command_addc(operand);
    } else if (command == 66 || command == 76) {
        return command_subc(operand);
    } else if (command == 67) {
        return command_loglc(operand);
    } else if (command == 68) {
        return command_logrc(operand);
    } else if (command == 69) {
        return command_rccl(operand);
    } else if (command == 70) {
        return command_rccr(operand);
    } else if (command == 71) {
        return command_mova(operand);
    } else if (command == 72) {
        return command_movr(operand);
    } else if (command == 73) {
        return command_movca(operand);
    } else if (command == 74) {
        return command_movcr(operand);
    }

    sc_regSet(COMMAND_ERROR, 1);
    return -1;
}

int command_read(int operand)
{
    trace;
    ui_readvalue(operand);
    return 0;
}

int command_write(int operand)
{
    trace;
    ui_printvalue(operand);
    return 0;
}

int command_load(int operand)
{
    trace;
    int value = 0;
    log_debug(sformat("current_instruction %d", operand));
    sc_memoryGet(operand, &value);
    sc_accumSet(value);
    return 0;
}

int command_store(int operand)
{
    trace;
    int a = 0;
    sc_accumGet(&a);
    sc_memorySet(operand, a);
    return 0;
}

int command_add(int operand)
{
    trace;
    int a = 0;
    sc_memoryGet(operand, &a);
    int b = 0;
    sc_accumGet(&b);
    b += a;
    sc_accumSet(b);
    return 0;
}

int command_sub(int operand)
{
    trace;
    int a = 0;
    sc_memoryGet(operand, &a);
    int b = 0;
    sc_accumGet(&b);
    log_info(sformat("%d - %d = %d", b, a, b-a));
    b -= a;
    sc_accumSet(b);
    return 0;
}

int command_divide(int operand)
{
    trace;
    int a = 0;
    sc_memoryGet(operand, &a);
    int b = 0;
    sc_accumGet(&b);
    if (a == 0) {
        sc_regSet(FLAG_DIVISION_BY_ZERO, 1);
        sc_accumSet(255);
        return -1;
    }

    b /= a;
    sc_accumSet(b);
    return 0;
}

int command_mul(int operand)
{
    trace;
    int a = 0;
    sc_memoryGet(operand, &a);
    int b = 0;
    sc_accumGet(&b);
    b *= a;
    sc_accumSet(b);
    return 0;
}

int command_jump(int operand)
{
    trace;
    sc_instSet(--operand);
    return 0;
}

int command_jneg(int operand)
{
    trace;
    int tmp = 0;
    sc_accumGet(&tmp);
    if (tmp <= 0)
        sc_instSet(--operand);
    return 0;
}

int command_jz(int operand)
{
    trace;
    int tmp = 0;
    sc_accumGet(&tmp);
    if (tmp == 0)
        sc_instSet(--operand);
    return 0;
}

int command_halt()
{
    trace;
    sc_regSet(FLAG_TICK_IGNORE, 1);
//    sc_instSet(0);
    return 0;
}

int command_not(int operand)
{
    trace;
    int a = 0;
    sc_accumGet(&a);
    int flg = 0;
    if (a < 0) {
        a *= -1;
        flg++;
    }
    int b = 0;
    for (int i = 0; i < 8; i++) {
        if (!(a & (1 << i)))
            b |= 1 << i;
    }
    if (flg)
        b *= -1;
    sc_commandEncode(0, b, &a);
    sc_memorySet(operand, a);
    return 0;
}

int command_and(int operand)
{
    trace;
    int a = 0;
    sc_accumGet(&a);
    int value = 0;
    sc_memoryGet(operand, &value);
    int b = 0,
        tmp = 0;
    sc_commandDecode(value, &tmp, &b);
    int c = 0;
    for (int i = 0; i < 8; i++)
        if ((a & (1 << i)) & (b & (1 << i)))
            c |= 1 << i;
    sc_accumSet(c);
    return 0;
}

int command_or(int operand)
{
    trace;
    int a = 0;
    sc_accumGet(&a);
    int value = 0;
    sc_memoryGet(operand, &value);
    int b = 0,
        tmp = 0;
    sc_commandDecode(value, &tmp, &b);
    int c = 0;
    for (int i = 0; i < 8; i++)
        if ((a & (1 << i)) | (b & (1 << i)))
            c |= 1 << i;
    sc_accumSet(c);
    return 0;
}

int command_xor(int operand)
{
    trace;
    int a = 0;
    sc_accumGet(&a);
    int value = 0;
    sc_memoryGet(operand, &value);
    int b = 0,
        tmp = 0;
    sc_commandDecode(value, &tmp, &b);
    int c = 0;
    for (int i = 0; i < 8; i++)
        if ((a & (1 << i)) ^ (b & (1 << i)))
            c |= 1 << i;
    sc_accumSet(c);
    return 0;
}

int command_jns(int operand)
{
    trace;
    int tmp = 0;
    sc_accumGet(&tmp);
    if (tmp > 0)
        sc_instSet(operand);
    return 0;
}

int command_jc(int operand)
{
    trace;
    int tmp = 0;
    sc_accumGet(&tmp);
    if (tmp > 127 || tmp < -127)
        sc_instSet(operand);
    return 0;
}

int command_jnc(int operand)
{
    trace;
    int tmp = 0;
    sc_accumGet(&tmp);
    if (tmp > -128 || tmp < 128)
        sc_instSet(operand);
    return 0;
}

int command_jp(int operand)
{
    trace;
    int tmp = 0;
    sc_accumGet(&tmp);
    if (!(tmp % 2))
        sc_instSet(operand);
    return 0;
}

int command_jnp(int operand)
{
    trace;
    int tmp = 0;
    sc_accumGet(&tmp);
    if (tmp % 2)
        sc_instSet(operand);
    return 0;
}

int command_chl(int operand)
{
    trace;
    return 0;
}

int command_shr(int operand)
{
    trace;
    return 0;
}

int command_rcl(int operand)
{
    trace;
    return 0;
}

int command_rcr(int operand)
{
    trace;
    return 0;
}

int command_neg(int operand)
{
    trace;
    int a = 0,
        tmp = 0,
        value = 0;
    sc_memoryGet(operand, &value);
    sc_commandDecode(value, &tmp, &a);
    sc_accumSet(!(a >= 0));
    return 0;
}

int command_addc(int operand)
{
    trace;
    return 0;
}

int command_subc(int operand)
{
    trace;
    return 0;
}

int command_loglc(int operand)
{
    trace;
    return 0;
}

int command_logrc(int operand)
{
    trace;
    return 0;
}

int command_rccl(int operand)
{
    trace;
    return 0;
}

int command_rccr(int operand)
{
    trace;
    return 0;
}

int command_mova(int operand)
{
    trace;
    int tmp = 0;
    sc_memoryGet(operand, &tmp);
    int dist = 0;
    sc_accumGet(&dist);
    sc_memorySet(dist, tmp);
    return 0;
}

int command_movr(int operand)
{
    trace;
    int from = 0;
    sc_accumGet(&from);
    int tmp = 0;
    sc_memoryGet(from, &tmp);
    sc_memorySet(operand, tmp);
    return 0;
}

int command_movca(int operand)
{
    trace;
    int dist1 = 0;
    sc_accumGet(&dist1);
    int dist2 = 0;
    sc_memoryGet(dist1, &dist2);
    int tmp = 0;
    sc_memoryGet(operand, &tmp);
    sc_memorySet(dist2, tmp);
    return 0;
}

int command_movcr(int operand)
{
    trace;
    int dist1 = 0;
    sc_accumGet(&dist1);
    int dist2 = 0;
    sc_memoryGet(dist1, &dist2);
    int tmp = 0;
    sc_memoryGet(dist2, &tmp);
    sc_memorySet(operand, tmp);
    return 0;
}

