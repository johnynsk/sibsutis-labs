#include "../lib/memory.h"
#include <stdint.h>

void check_mem()
{
    printf("memory tests--\n");
    int16_t tmp = 0;
    sc_memoryInit();
    if (!sc_memorySet(15, 15)) {
        printf("Set pass\n");
        if (!sc_memoryGet(15, &tmp) && tmp == 15) {
            printf("Get pass\n");
            if (!sc_memorySave("mda")) {
                printf("Save pass\n");
                if (!sc_memoryLoad("mda") && memory[15] == 15) {
                    printf("Load pass\n**MEMTEST DONE**\n");
                } else
                    printf("Wrong loaded value\n");
            }
        } else
            printf("Wrong get value\n");
    }
    return;
}

void check_reg()
{
    printf("\n--REGISTER CHECK--\n");
    sc_regInit();
    int16_t tmp = 0;
    printf("test regSet()\n");
    if (!sc_regSet(FLAG_OVERFLOW, 1)) {
        printf("passed:\n");
        printf("%d\n", sc_register.flag);
        printf("test sc_regGet()\n");
        if (!sc_regGet(FLAG_OVERFLOW, &tmp) && tmp == 1) {
            printf("%d\n", tmp);
            printf("passed\n");
            printf("test accumulating flags:\n");
            sc_regSet(FLAG_MEMORY_ERROR, 1);
            if (sc_register.flag == FLAG_OVERFLOW | FLAG_MEMORY_ERROR) {
                printf("flags accumulated true");
                printf("**REGISTER OK\n");
                return;
            }
        }
    }

    printf("REGISTER FAILED\n");
    return;
}

void check_command()
{
    printf("\n--ENCODE/DECODE CHECK--\n");
    int value = 0, command = 15, operand = 24;
    printf("encode: command %d, operand %d\n", command, operand);
    if (!sc_commandEncode(command, operand, &value)) {
        command = operand = 0;
            if (!sc_commandDecode(value, &command, &operand)) {
                printf("decoded: command = %d, operand = %d\n", command, operand);
                if (command == 15 && operand == 24)
                    printf("**ENCODE/DECODE OK**\n");
            }
    }
    return;
}

int main()
{
    check_mem();
    check_reg();
    check_command();
    return 0;
}
