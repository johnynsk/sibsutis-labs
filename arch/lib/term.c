#include "term.h"

int mt_getscreensize(int *rows, int *cols)
{
    struct winsize ws;
    if (ioctl(1, TIOCGWINSZ, &ws)) {
        return -1;
    }

    *rows = ws.ws_row;
    *cols = ws.ws_col;

    return 0;
}

int mt_clrscr(void)
{
    char *clear;
    clear = "\E[H\E[2J";
    ssize_t len = strlen(clear) * sizeof(char);

    if (write(STDOUT_FILENO, clear, strlen(clear)) < len) {
        return -1;
    }
    return 0;
}

int mt_gotoXY(int x, int y)
{
    char go[30];
    sprintf(go, "\E[%d;%dH", y, x);
    ssize_t len = strlen(go) * sizeof(char);

    if (write(STDOUT_FILENO, go, len) < len) {
        return -1;
    }
    return 0;
}

int mt_setfgcolor(enum colors color)
{
    char fg[30];
    sprintf(fg, "\e[38;5;%dm", color);
    ssize_t len = strlen(fg) * sizeof(char);

    if (write(STDOUT_FILENO, fg, strlen(fg)) < len) {
        return -1;
    }
    return 0;
}

int mt_setbgcolor(enum colors color)
{
    char bg[30];
    sprintf(bg, "\e[48;5;%dm", color);
    ssize_t len = strlen(bg) * sizeof(char);

    if (write(STDOUT_FILENO, bg, strlen(bg)) < len) {
        return -1;
    }
    return 0;
}
