#include "./memory.h"

int8_t memory[MEMSIZE];

int sc_memoryInit()
{
    memset(memory, 0, MEMSIZE * sizeof(memory[0]));
    return 0;
}

int sc_memorySet(int8_t address, int16_t value)
{
    if (address < 100 && address >= 0) {
        memory[address] = value;
        return 0;
    }

    sc_regSet(FLAG_MEMORY_ERROR, 1);
    return ERROR_ILLEGAL_ADDRESS;
}

int sc_memoryGet(int8_t address, int16_t * value)
{
    if (address < 100 && address >= 0) {
        *value = memory[address];
        return 0;
    }

    sc_regSet(FLAG_MEMORY_ERROR, 1);
    return ERROR_ILLEGAL_ADDRESS;
}

int sc_memorySave(char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        return ERROR_IO_FILE;
    }

    fwrite(memory, sizeof(memory[0]), MEMSIZE, f);
    fclose(f);
    return 0;
}

int sc_memoryLoad(char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return ERROR_IO_FILE;
    }

    fread(memory, sizeof(memory[0]), MEMSIZE, f);
    fclose(f);
    return 0;
}
