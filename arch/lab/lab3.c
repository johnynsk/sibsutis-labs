#include "../lib/big_chars.h"
#include "../lib/term.h"
#include "../char.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int *alph = NULL;

void mock_print_mem()
{
    bc_box(1, 1, 61, 12);
    mt_gotoXY(30, 0);
    char tmp[] = " Memory ";
    write(1, tmp, sizeof(tmp));
    for (int i = 0; i < 100; i++) {
        mt_gotoXY(2 + 6 * (i / 10), 2 + (i % 10));
        char tmp1[] = "+0000";
        write(1, tmp1, sizeof(tmp1));
    }
}

void mock_print_accum()
{
    bc_box(62, 1, 22, 3);
    mt_gotoXY(66, 1);
    char tmp[] = " accumulator ";
    write(1, tmp, sizeof(tmp));
    mt_gotoXY(71, 2);
    char tmp1[] = "+9999";
    write(1, tmp1, sizeof(tmp1));
}

void mock_print_instcnt()
{
    bc_box(62, 4, 22, 3);
    mt_gotoXY(63, 4);
    char tmp[] = " instructionCounter ";
    write(1, tmp, sizeof(tmp));
    mt_gotoXY(71, 5);
    char tmp1[] = "+0000";
    write(1, tmp1, sizeof(tmp1));
}

void mock_print_operation()
{
    bc_box(62, 7, 22, 3);
    mt_gotoXY(68, 7);
    char tmp[] = " Operation ";
    write(1, tmp, sizeof(tmp));
    char tmp1[] = "+00 : 00";
    mt_gotoXY(69, 8);
    write(1, tmp1, sizeof(tmp1));
}

void mock_print_flg()
{
    bc_box(62, 10, 22, 3);
    mt_gotoXY(69, 10);
    char tmp[] = " Flags ";
    write(1, tmp, strlen(tmp));
    char tmp1[] = "O Z M F C";
    mt_gotoXY(67, 11);
    write(1, tmp1, strlen(tmp1));
}

void mock_print_membc()
{
    bc_box(1, 13, 50, 10);
    bc_printbigchar(char_plus(), 2, 14, COLOR_YELLOW, COLOR_GREY);
    for (int i = 0; i < 4; i++) {
        bc_printbigchar(char_3(), 2 + 10 * (i + 1), 14, COLOR_BLUE, COLOR_GREEN);
    }
}

void mock_print_keys()
{
    bc_box(51, 13, 33, 10);
    mt_gotoXY(52, 13);
    char tmp[] = " Keys: ";
    write(1, tmp, strlen(tmp));
    char *tmp1[] = {"l - load", "s - save", "r - run", "t - step", "i - reset",
        "F5 - accumulator", "F6 - instructionCounter"};
    for (int i = 0; i < 7; i++) {
        mt_gotoXY(52, 14 + i);
        write(1, tmp1[i], strlen(tmp1[i]));
    }
}

int main()
{
    int fd = open("font", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int cnt = 0;
    alph = (int*) malloc(sizeof(int) * 64 * 18);
    if (bc_bigcharread(fd, alph, 18, &cnt) == -1)
        return -1;

    mt_clrscr();
    mock_print_mem();
    mock_print_accum();
    mock_print_instcnt();
    mock_print_operation();
    mock_print_flg();
    mock_print_membc();
    mock_print_keys();
    printf("\n");
    printf("\n");
    printf("\n");
//    mt_setfgcolor(BLACK);
    return 0;
}
