#ifndef ARCH_LIB_MEMORY_H
#define ARCH_LIB_MEMORY_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "registers.h"
#include "term.h"
#include "ui.h"


#define MEMSIZE 100
int memory[MEMSIZE];

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int * value);
int sc_memorySave(const char * filename);
int sc_memoryLoad(const char * filename);


#define ERROR_ILLEGAL_ADDRESS 1
#define ERROR_IO_FILE 2

#endif
