#ifndef ARCH_LIB_UI_H
#define ARCH_LIB_UI_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "big_chars.h"
#include "command.h"
#include "registers.h"
#include "memory.h"
#include "term.h"
#include "keys.h"
#include "units.h"
#include "log.h"
int coordX, coordY;

int ui_readvalue(int address);
int ui_printvalue(int address);
void print_mem();
void print_accum();
void print_instcnt();
void print_operation();
void print_flg();
void print_membc();
void print_keys();
void load_mem();
void load_mem();
void save_mem();
void set_accum();
void set_instcnt();
void set_mem();
void step(int * x, int * y);
void init();
void refresh();
void key_handler();
void interface(int x, int y);
void main_loop();

#endif
