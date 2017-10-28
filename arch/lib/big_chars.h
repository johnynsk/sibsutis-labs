#include "big_chars.h"

int bc_printA(char *str)
{
    ssize_t len = strlen(str) * sizeof(char);
    write(STDOUT_FILENO, "\E(0", 3);
    if (write(STDOUT_FILENO, str, len) != len)
    {
        return -1;
    }
    write(STDOUT_FILENO, "\E(B", 3);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
    for (int i = 0; i < x2; i++)
    {
        for (int j = 0; j < y2; j++)
        {
            mt_gotoXY(x1 + i, y1 + j);

            //corners
            if (i == 0 && j == 0)
                bc_printA("l");
            else if (i == 0 && j == y2 - 1)
                bc_printA("k\n");
            else if (i == x2 - 1 && j == 0)
                bc_printA("m");
            else if (i == x2 - 1 && j == y2 - 1)
                bc_printA("j\n");
            else if ((i == 0 || i == x2 - 1) && (j > 0 && j < y2)) // horizontal line
                bc_printA("q");
            else if ((i > 0 && i < x2) && (j == 0 || j == y2 - 1)) // vertical line
                bc_printA("x");
            else
                write(STDOUT_FILENO, " ", sizeof(char));
        }
    }
    return 0;
}

int bc_printbigchar(int *big, int x, int y, enum colors fgcolor, enum colors bgcolor)
{
    mt_setbgcolor(bgcolor);
    mt_setfgcolor(fgcolor);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            mt_gotoXY(x + i, y + j);
            short value;
            bc_getbigcharpos(big, i, j, &value);
            if (!value)
                write(STDOUT_FILENO, " ", sizeof(char));
            else
                bc_printA("a");
        }
        write(STDOUT_FILENO, "\n", sizeof(char));
    }
    mt_setbgcolor(GREY);
    mt_setfgcolor(LIGHT_GREY);
}

int bc_setbigcharpos(int *big, int x, int y, short int value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7 || value > 1 || value < 0)
        return 1;
    int part = x / 4;
    x %= 4;
    if (value)
        big[part] |= (1 << (8 * x + y));
    else
        big[part] &= ~(1 << (8 * x + y));
    return 0;
}

int bc_getbigcharpos(int *big, int x, int y, short int *value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return -1;
    short int part = x / 4;
    x %= 4;
    if (big[part] & (1 << (8 * x + y)))
    {
        *value = 1;
    }
    else
        *value = 0;
    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
    for (int i = 0; i < count * 2; i++)
        if (write(fd, &big[i], sizeof(int)) == -1)
            return 1;
    return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
    for (*count = 0; (*count < need_count * 2); *count += 1)
        if (read(fd, &big[*count], sizeof(int)) == -1)
            return 1;
    return 0;
}
