#include "keys.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

enum keys rk_parsekey(char * keycode)
{
    trace;
    if (!strcmp(keycode,  "q")) {
        return q;
    } else if (!strcmp(keycode, "l")) {
        return l;
    } else if (!strcmp(keycode, "s")) {
        return s;
    } else if (!strcmp(keycode, "i")) {
        return i;
    } else if (!strcmp(keycode, "t")) {
        return t;
    } else if (!strcmp(keycode, "r")) {
        return r;
    } else if (!strcmp(keycode, "\E[15~")) {
        return f5;
    } else if (!strcmp(keycode, "\E[17~")) {
        return f6;
    } else if (!strcmp(keycode, "\E[18~")) {
        return f7;
    } else if (!strcmp(keycode, "\E[20~")) {
        return f9;
    } else if (!strcmp(keycode, "\E[A")) {
        return up;
    } else if (!strcmp(keycode, "\E[B")) {
        return down;
    } else if (!strcmp(keycode, "\E[C")) {
        return right;
    } else if (!strcmp(keycode, "\E[D")) {
        return left;
    } else if (!strcmp(keycode, "\n")) {
        return enter;
    }

    return none;
}

int rk_readkey(enum keys *key)
{
    trace;
    if (tcgetattr(1, &def)) {
        return -1;
    }

    if (rk_mytermregime(0, 0, 1, 0, 1)) {
        return -1;
    }

    char keycode[10] = "\0";
    read(1, keycode, 10);

    *key = rk_parsekey(keycode);
    if (tcsetattr(1, TCSANOW, &def))
        return -1;
    return 0;
}

int rk_mytermsave()
{
    trace;
    return tcsetattr(1, TCSANOW, &custom);
}

int rk_mytermrestore()
{
    trace;
    return tcsetattr(1, TCSANOW, &def);
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    trace;
    if (tcgetattr(1, &custom))
        return -1;

    if (regime) {
        custom.c_lflag |= ICANON;
    } else {
        custom.c_lflag &= ~ICANON;
    }

    if (echo) {
        custom.c_lflag |= ECHO;
    } else {
        custom.c_lflag &= ~ECHO;
    }

    if (sigint) {
        custom.c_lflag |= ISIG;
    } else {
        custom.c_lflag &= ~ISIG;
    }

    custom.c_cc[VTIME] = vtime;
    custom.c_cc[VMIN] = vmin;
    return rk_mytermsave();
}

