#include "../lib/big_chars.h"
#include "../lib/memory.h"
#include "../lib/command.h"
#include "../lib/registers.h"
#include "../lib/keys.h"
#include "../char.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int *font = NULL;
char accum[6] = "00000";
char inst_cnt[6] = "00000";



void print_mem(int *x, int *y)
{
    for (int i = 0; i < 100; i++) {
        mt_gotoXY(2 + 6 * (i / 10), 2 + (i % 10));
        if (*x > 9)
            *x = 0;
        if (*x < 0)
            *x = 9;
        if (*y > 9)
            *y = 0;
        if (*y < 0)
            *y = 9;
        if (i / 10 == *y && i % 10 == *x)
            mt_setbgcolor(COLOR_RED);
        int8_t command, operand;
        int16_t value;
        sc_memoryGet(i, &value);
        sc_commandDecode(value, &command, &operand);
        char tmp1[10];
        if (command < 16 && operand < 16)
            sprintf(tmp1, "0%x:0%x", command, operand);
        else if (command < 16 && operand >= 16)
            sprintf(tmp1, "0%x:%x", command, operand);
        else if (command >= 16 && operand < 16)
            sprintf(tmp1, "%x:0%x", command, operand);
        else
            sprintf(tmp1, "%x:%x", command, operand);
        write(1, tmp1, strlen(tmp1));
        mt_setbgcolor(COLOR_DEFAULT);
    }

}

void print_accum()
{
    mt_gotoXY(71, 2);
    write(1, accum, strlen(accum));
}

void print_instcnt()
{
    mt_gotoXY(71, 5);
    write(1, inst_cnt, strlen(inst_cnt));
}

void print_operation()
{
    char tmp1[] = "+00 : 00";
    mt_gotoXY(69, 8);
    write(1, tmp1, sizeof(tmp1));
}

void print_flg()
{
    char tmp1[] = "OZMFC";
    mt_gotoXY(67, 11);
    for (int i = 0; i < 5; i++) {
        int8_t value;
        sc_regGet(1 << i, &value);
        if (value)
            mt_setfgcolor(COLOR_RED);
        char tmp2[3];
        sprintf(tmp2, "%c ", tmp1[i]);
        write(1, tmp2, strlen(tmp2));
        mt_setfgcolor(COLOR_DEFAULT);
    }
}

void print_membc(int x, int y)
{
    int16_t value;
    int8_t command, operand;
    sc_memoryGet(10 * y + x, &value);
    sc_commandDecode(value, &command, &operand);
    bc_printbigchar(&font[(command / 16) * 64], 2 + 10 * 0, 14, COLOR_WHITE, COLOR_DEFAULT);
    bc_printbigchar(&font[(command % 16) * 64], 2 + 10 * 1, 14, COLOR_WHITE, COLOR_DEFAULT);
    int sign = value < 0 ? 1 : 0;
    bc_printbigchar(&font[(16 + sign) * 64], 2 + 10 * 2, 14, COLOR_WHITE, COLOR_DEFAULT);
    bc_printbigchar(&font[(operand / 16) * 64], 2 + 10 * 3, 14, COLOR_WHITE, COLOR_DEFAULT);
    bc_printbigchar(&font[(operand % 16) * 64], 2 + 10 * 4, 14, COLOR_WHITE, COLOR_DEFAULT);
    mt_gotoXY(0, 24);
    mt_setfgcolor(COLOR_WHITE);
    mt_setbgcolor(COLOR_DEFAULT);
    char valbox[5];
    sprintf(valbox, "%d ", value);
    write(1, valbox, strlen(valbox));
    mt_setfgcolor(COLOR_LIGHT_GREY);

}

void print_keys()
{
    bc_box(51, 13, 33, 10);
    mt_gotoXY(52, 13);
    char tmp[] = " Keys: ";
    write(1, tmp, strlen(tmp));
    char *tmp1[] = {"l - load", "s - save", "r - run", "t - step",
        "i - reset", "F5 - accumulator", "F6 - instructionCounter"};
    for (int i = 0; i < 7; i++) {
        mt_gotoXY(52, 14 + i);
        write(1, tmp1[i], strlen(tmp1[i]));
    }
}

void refresh()
{
    bc_box(1, 1, 61, 12);
    mt_gotoXY(30, 0);
    char tmp[] = " Memory ";
    write(1, tmp, sizeof(tmp));
    bc_box(62, 1, 22, 3);
    mt_gotoXY(66, 1);
    char tmp1[] = " accumulator ";
    write(1, tmp1, sizeof(tmp1));
    bc_box(62, 4, 22, 3);
    mt_gotoXY(63, 4);
    char tmp2[] = " instructionCounter ";
    write(1, tmp2, sizeof(tmp2));
    bc_box(62, 7, 22, 3);
    mt_gotoXY(68, 7);
    char tmp3[] = " Operation ";
    write(1, tmp3, sizeof(tmp3));
    bc_box(62, 10, 22, 3);
    mt_gotoXY(69, 10);
    char tmp4[] = " Flags ";
    write(1, tmp4, strlen(tmp4));
    bc_box(1, 13, 50, 10);
    print_keys();
}

void load_mem()
{
    bc_box(20, 6, 20, 5);
    mt_gotoXY(24, 7);
    write(1, "Load\n", strlen("load\n"));
    char tmp[255] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 255);
    tmp[strlen(tmp) - 1] = '\0';
    if (sc_memoryLoad(tmp)) {
        bc_box(20, 6, 20, 5);
        mt_gotoXY(23, 7);
        write(1, "Failed to open\n", strlen("Failed to open\n"));
        mt_gotoXY(29, 9);
        mt_setbgcolor(COLOR_RED);
        write(1, "OK", strlen("OK"));
        mt_setbgcolor(COLOR_DEFAULT);
        mt_gotoXY(30, 9);
        read(1, tmp, 1);
    }
    refresh();
}

void save_mem()
{
    bc_box(20, 6, 20, 5);
    mt_gotoXY(23, 7);
    write(1, "Save to\n", strlen("Save to\n"));
    char tmp[255] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 255);
    tmp[strlen(tmp) - 1] = '\0';
    if (sc_memorySave(tmp)) {
        bc_box(20, 6, 20, 5);
        mt_gotoXY(23, 7);
        write(1, "Failed to save\n", strlen("Failed to open\n"));
        mt_gotoXY(29, 9);
        mt_setbgcolor(COLOR_RED);
        write(1, "OK", strlen("OK"));
        mt_setbgcolor(COLOR_DEFAULT);
        mt_gotoXY(30, 9);
        read(1, tmp, 1);
    }
    refresh();
}

void set_accum()
{
    bc_box(20, 6, 20, 5);
    mt_gotoXY(23, 7);
    write(1, "Set accum to\n", strlen("Sav tocum to\n"));
    char tmp[5] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 5);
    tmp[strlen(tmp) - 1] = '\0';
    strcpy(accum, tmp);
    refresh();
}

void set_instcnt()
{
    bc_box(20, 6, 26, 5);
    mt_gotoXY(22, 7);
    write(1, "Set instructionCounter to\n", strlen("Set instructionCounter to\n"));
    char tmp[5] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 5);
    tmp[strlen(tmp) - 1] = '\0';
    strcpy(inst_cnt, tmp);
    refresh();
}

void set_mem(int x, int y)
{
    bc_box(20, 6, 26, 5);
    mt_gotoXY(22, 7);
    write(1, "Set memory(dec) to\n", strlen("Set memory(dec) to\n"));
    char tmp[11] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 10);
    tmp[strlen(tmp) - 1] = '\0';
    int tmp1 = atoi(tmp);
    sc_memorySet(10 * y + x, tmp1);
    refresh();
}

void run(int *x, int *y)
{
    for (int i = 0; i < 100; i++) {
        int16_t val = 0;
        sc_memoryGet(i, &val);
        if (!val)
            break;
        *y = i / 10, *x = i % 10;
        print_mem(x, y);
        sleep(1);
    }
}

void step(int *x, int *y)
{
    *x += 1;
    if (*x > 9) {
        if (*y < 9) {
            *x = 0;
            *y += 1;
        } else
            *x -= 1;
    }
}

void interface()
{
    int exit = 0;
    int x = 0, y = 0, cnt = 0;
    refresh();
    while (!exit) {
        enum keys key = none;
        print_mem(&x, &y);
        print_accum();
        print_instcnt();
        print_operation();
        print_flg();
        print_membc(x, y);
        rk_readkey(&key);
        if (key == q)
            exit++;
        if (key == l)
            load_mem();
        if (key == s)
            save_mem();
        if (key == up)
            x--;
        if (key == down)
            x++;
        if (key == left)
            y--;
        if (key == right)
            y++;
        if (key == i) {
            sc_memoryInit();
            x = 0, y = 0;
            refresh();
        }
        if (key == f5)
            set_accum();
        if (key == f6)
            set_instcnt();
        if (key == r)
            run(&x, &y);
        if (key == t)
            step(&x, &y);
        if (key == enter)
            set_mem(x, y);
        if (cnt % 5 == 0) {
            mt_clrscr();
            refresh();
        }
        cnt++;
    }
}

int main()
{
    int fd = open("font2", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int cnt = 0;
    font = (int*) malloc(sizeof(int) * 64 * 18);
    if (bc_bigcharread(fd, font, 18, &cnt) == -1)
        return -1;
    sc_memoryInit();
    mt_clrscr();
    interface();
    write(1, "\e[0m", strlen("\e[0m"));
    rk_mytermrestore();
    mt_clrscr();
    return 0;
}
