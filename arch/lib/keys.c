#include "keys.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int rk_readkey(enum keys *key)
{
    if (tcgetattr(1, &def))
        return -1;
    if (rk_mytermregime(0, 0, 1, 0, 1))
        return -1;
    char tmp[10] = "\0";
    read(1, tmp, 10);
    if (!strcmp(tmp, "q"))
        *key = q;
    if (!strcmp(tmp, "l"))
        *key = l;
    if (!strcmp(tmp, "s"))
        *key = s;
    if (!strcmp(tmp, "i"))
        *key = i;
    if (!strcmp(tmp, "t"))
        *key = t;
    if (!strcmp(tmp, "r"))
        *key = r;
    if (!strcmp(tmp, "\E[15~"))
        *key = f5;
    if (!strcmp(tmp, "\E[17~"))
        *key = f6;
    if (!strcmp(tmp, "\E[A"))
        *key = up;
    if (!strcmp(tmp, "\E[B"))
        *key = down;
    if (!strcmp(tmp, "\E[C"))
        *key = right;
    if (!strcmp(tmp, "\E[D"))
        *key = left;
    if (!strcmp(tmp, "\n"))
        *key = enter;
    if (tcsetattr(1, TCSANOW, &def))
        return -1;
    return 0;
}

int rk_mytermsave()
{
    return tcsetattr(1, TCSANOW, &custom);
}

int rk_mytermrestore()
{
    return tcsetattr(1, TCSANOW, &def);
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    if (tcgetattr(1, &custom))
        return -1;
    if (regime)
        custom.c_lflag |= ICANON;
    else
        custom.c_lflag &= ~ICANON;
    if (echo)
        custom.c_lflag |= ECHO;
    else
        custom.c_lflag &= ~ECHO;
    if (sigint)
        custom.c_lflag |= ISIG;
    else
        custom.c_lflag &= ~ISIG;
    custom.c_cc[VTIME] = vtime;
    custom.c_cc[VMIN] = vmin;
    return rk_mytermsave();
}
