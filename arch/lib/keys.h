#ifndef ARCH_LIB_KEYS_H
#define ARCH_LIB_KEYS_H

#include "log.h"
#include <termios.h>

struct termios def;
struct termios custom;

enum keys {
    up, down, left, right, f5, f6, f7, f9, q, l, s, i, t, r, enter, none
} keys;

int rk_readkey(enum keys *key);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif
