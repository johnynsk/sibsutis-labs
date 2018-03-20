#include "./memory.h"

int sc_memoryInit()
{
    trace;
    memset(memory, 0, MEMSIZE * sizeof(memory[0]));
    return 0;
}

int sc_memorySet(int address, int value)
{
    trace;
    log_debug(sformat("address %d value %d", address, value));
    if (address < 100 && address >= 0) {
        memory[address] = value;
        return 0;
    }

    sc_regSet(FLAG_MEMORY_ERROR, 1);
    return ERROR_ILLEGAL_ADDRESS;
}

int sc_memoryGet(int address, int * value)
{
    trace;
    if (address < 100 && address >= 0) {
        *value = memory[address];
        return 0;
    }
    log_debug(sformat("address %d value %d", address, *value));

    sc_regSet(FLAG_MEMORY_ERROR, 1);
    return ERROR_ILLEGAL_ADDRESS;
}

int sc_memorySave(char *filename)
{
    trace;
    FILE *f = fopen(filename, "wb");
    print_on_screen(filename);
    if (f == NULL) {
        return ERROR_IO_FILE;
    }

    fwrite((void*)memory, sizeof(memory[0]), MEMSIZE, f);
    fclose(f);
    return 0;
}

int sc_memoryLoad(char *filename)
{
    trace;
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return ERROR_IO_FILE;
    }

    fread(memory, sizeof(memory[0]), MEMSIZE, f);
    fclose(f);
    return 0;
}
