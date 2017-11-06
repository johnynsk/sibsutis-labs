#ifndef ARCH_LIB_BIGCHARS_H
#define ARCH_LIB_BIGCHARS_H

#include "term.h"
#include <stdlib.h>

int * bc_copy(int * from);
int bc_printA(char *str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int *big, int x, int y, enum colors fgcolor, enum colors bgcolor);
int bc_setbigcharpos(int *big, int x, int y, short int value);
int bc_getbigcharpos(int *big, int x, int y, short int *value);
int bc_bigcharwrite(int fd, int *big, int count);
int bc_bigcharread(int fd, int *big, int need_count, int *count);

#define GRAPH_LINE_VERTICAL "q"
#define GRAPH_LINE_HORIZON "x"

#define GRAPH_CORNER_LEFT_TOP "l"
#define GRAPH_CORNER_RIGHT_TOP "k"
#define GRAPH_CORNER_RIGHT_BOTTOM "j"
#define GRAPH_CORNER_LEFT_BOTTOM "m"

#define GRAPH_CKBOARD "a"

#define GRAPH_SMACS "\E(0"
#define GRAPH_RMACS "\E(B"

#define GRAPH_BTEXT_OVERPOS -1
#define GRAPH_BTEXT_WRONGVAL -1
#define GRAPH_SUCCESS_CODE 0

#endif

