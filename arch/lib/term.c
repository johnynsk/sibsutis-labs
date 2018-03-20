#include "term.h"

int mt_getscreensize(int *rows, int *cols)
{
    vtrace;
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
    vtrace;
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
//    vtrace;
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
    vtrace;
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
    vtrace;

    char bg[30];
    sprintf(bg, "\e[48;5;%dm", color);
    ssize_t len = strlen(bg) * sizeof(char);

    if (write(STDOUT_FILENO, bg, strlen(bg)) < len) {
        return -1;
    }
    return 0;
}

void print_on_screen(const char * string)
{
    vtrace;
    print_on_screen_stream(string, 1);
}

void print_on_screen_stream(const char * string, int stream_id)
{
    vtrace;
    write(stream_id, string, strlen(string));
}

void mt_resetcolor()
{
    vtrace;
    print_on_screen("\e[0m");
}
