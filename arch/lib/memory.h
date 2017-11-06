#ifndef ARCH_LIB_MEMORY_H
#define ARCH_LIB_MEMORY_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "registers.h"

#define MEMSIZE 100
int16_t memory[MEMSIZE];

int sc_memoryInit();
int sc_memorySet(int8_t address, int16_t value);
int sc_memoryGet(int8_t address, int16_t * value);
int sc_memorySave(char * filename);
int sc_memoryLoad(char * filename);


#define ERROR_ILLEGAL_ADDRESS 1
#define ERROR_IO_FILE 2

#endif
