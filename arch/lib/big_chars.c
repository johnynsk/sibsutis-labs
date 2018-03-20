#include "big_chars.h"

int * bc_copy(int * bchar)
{
    vtrace;
    int * to = malloc(sizeof(int) * 64);
    for (int i = 0; i < 64; i++) {
        to[i] = bchar[i];
    }
}

int bc_printA(char *str)
{
//    vtrace;
    ssize_t len = strlen(str) * sizeof(char);
    write(STDOUT_FILENO, GRAPH_SMACS, 3);
    if (write(STDOUT_FILENO, str, len) != len) {
        return -1;
    }

    write(STDOUT_FILENO, GRAPH_RMACS, 3);
    return 0;
}

int bc_box(int x, int y, int width, int height)
{
    vtrace;
    int exitcode = 0;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            exitcode = mt_gotoXY(x + i, y + j);

            if (exitcode) {
                break;
            }

            if (i == 0 && j == 0) {
                exitcode = bc_printA(GRAPH_CORNER_LEFT_TOP);
            } else if (i == 0 && j == height - 1) {
                bc_printA(GRAPH_CORNER_LEFT_BOTTOM);
            } else if (i == width - 1 && j == 0) {
                bc_printA(GRAPH_CORNER_RIGHT_TOP);
            } else if (i == width - 1 && j == height - 1) {
                bc_printA(GRAPH_CORNER_RIGHT_BOTTOM);
            } else if ((i == 0 || i == width - 1) && (j > 0 && j < height)) {
                bc_printA(GRAPH_LINE_HORIZON);
            } else if ((i > 0 && i < width) && (j == 0 || j == height - 1)) {
                bc_printA(GRAPH_LINE_VERTICAL);
            } else {
                write(STDOUT_FILENO, " ", sizeof(char));
            }

            if (exitcode) {
                break;
            }
        }
    }

    return exitcode;
}

int bc_printbigchar(int *big, int x, int y, enum colors fgcolor, enum colors bgcolor)
{
    vtrace;
    mt_setbgcolor(bgcolor);
    mt_setfgcolor(fgcolor);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            mt_gotoXY(x + i, y + j);
            short value;
            bc_getbigcharpos(big, i, j, &value);

            if (!value) {
                write(STDOUT_FILENO, " ", sizeof(char));
            } else {
                bc_printA(GRAPH_CKBOARD);
            }
        }

        write(STDOUT_FILENO, "\n", sizeof(char));
    }

    mt_resetcolor();
}

int bc_setbigcharpos(int *big, int x, int y, short int value)
{
    vtrace;
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return GRAPH_BTEXT_OVERPOS;
    } else if (value > 1 || value < 0) {
        return GRAPH_BTEXT_WRONGVAL;
    }

    int part = x / 4;
    x %= 4;

    if (value) {
        big[part] |= (1 << (8 * x + y));
    } else {
        big[part] &= ~(1 << (8 * x + y));
    }

    return GRAPH_SUCCESS_CODE;
}

int bc_getbigcharpos(int * big, int x, int y, short int *value)
{
    vtrace;
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return GRAPH_BTEXT_OVERPOS;

    short int part;
    part = y;
    part <<= 3;
    part += x;

    *value = 0;
    if (big[part]) {
        *value = 1;
    }

    return GRAPH_SUCCESS_CODE;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
    vtrace;
    for (int i = 0; i < count * 64; i++)
        if (write(fd, &big[i], sizeof(int)) == -1)
            return 1;
    return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
    vtrace;
    for (*count = 0; (*count < need_count * 64); *count += 1)
        if (read(fd, &big[*count], sizeof(int)) == -1)
            return 1;
    return 0;
}
