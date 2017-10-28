#ifndef ARCH_LIB_TERM_H
#define ARCH_LIB_TERM_H

enum colors
{
    LIGHT_GREY = 247,
    GREY = 237,
    BLACK = 16,
    RED = 124,
    GREEN = 41,
    BLUE = 20,
    YELLOW = 184,
};

int mt_clrscr(void);
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);

#endif
