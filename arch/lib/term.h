#ifndef ARCH_LIB_TERM_H
#define ARCH_LIB_TERM_H
#include <sys/ioctl.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "log.h"
enum colors
{
    COLOR_LIGHT_GREY = 16, //247,
    COLOR_WHITE = 255,
    COLOR_GREY = 237,
    COLOR_BLACK = 16,
    COLOR_RED = 124,
    COLOR_GREEN = 41,
    COLOR_BLUE = 20,
    COLOR_YELLOW = 184,
    COLOR_DEFAULT = 16,
    COLOR_DEFAULT_TEXT = 255,
};

int mt_clrscr(void);
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);
void mt_resetcolor();
void print_on_screen_stream(const char * string, int stream_id);
void print_on_screen(const char * string);

#endif
