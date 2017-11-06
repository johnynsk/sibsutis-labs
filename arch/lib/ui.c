#include "ui.h"

int *font = NULL;

void print_mem(int x, int y)
{
    for (int8_t i = 0; i < 100; i++) {
        mt_gotoXY(2 + 6 * (i / 10), 2 + (i % 10));

        if (x > 9) {
            x = 0;
        } else if (x < 0) {
            x = 9;
        }

        if (y > 9) {
            y = 0;
        } else if (y < 0) {
            y = 9;
        }

        if (i / 10 == y && i % 10 == x) {
            mt_setbgcolor(COLOR_RED);
        }

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
    int acc = 0;
    sc_accumGet(&acc);
    char tmp[4];
    sprintf(tmp, "%d", acc);
    write(1, tmp, strlen(tmp));
}

void print_instcnt()
{
    mt_gotoXY(71, 5);
    int8_t inst = 0;
    sc_instGet(&inst);
    char tmp[4];
    sprintf(tmp, "%d", inst);
    write(1, tmp, strlen(tmp));
}

void print_operation(int x, int y)
{
    int16_t tmp = 0;
    sc_memoryGet(x + y * 10, &tmp);
    char tmp1[10];
    int8_t cmd, opr;
    sc_commandDecode(tmp, &cmd, &opr);
    sprintf(tmp1, "%x:%x", cmd, opr);
    mt_gotoXY(69, 8);
    write(1, tmp1, strlen(tmp1));
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
}

void print_keys()
{
    bc_box(51, 13, 33, 10);
    mt_gotoXY(52, 13);
    const char tmp[] = " Keys: ";
    write(1, tmp, strlen(tmp));
    const char *tmp1[] = {"l - load", "s - save", "r - run", "t - step",
        "i - reset", "F5 - accumulator", "F6 - instructionCounter"};
    for (int i = 0; i < 7; i++) {
        mt_gotoXY(52, 14 + i);
        write(1, tmp1[i], strlen(tmp1[i]));
    }
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
    int new_acc = atoi(tmp);
    sc_accumSet(new_acc);
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
    int new_inst = atoi(tmp);
    sc_instSet(new_inst);
    refresh();
}

void set_mem()
{
    bc_box(20, 6, 26, 5);
    mt_gotoXY(22, 7);
    write(1, "Set memory(dec) to\n", strlen("Set memory(dec) to\n"));
    char tmp[11] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 10);
    tmp[strlen(tmp) - 1] = '\0';
    int tmp1 = atoi(tmp);
    sc_memorySet(10 * coordY + coordX, tmp1);
    refresh();
}

void step(int * x, int * y)
{
    CU();
    int8_t inst_curr = 0;
    sc_instGet(&inst_curr);
    *x = inst_curr / 10;
    *y = inst_curr % 10;
}

void init()
{
    int fd = open("font2", O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int count = 0;
    font = (int*) malloc(sizeof(int) * 64 * 18);
    if (bc_bigcharread(fd, font, 18, &count) == -1 && count < 18) {
        write(2, "Failed to open font2\n", strlen("Failed to open font2\n"));
        return;
    }

    sc_regSet(FLAG_OVERFLOW, 0);
    sc_regSet(FLAG_DIVISION_BY_ZERO, 0);
    sc_regSet(FLAG_MEMORY_ERROR, 0);
    sc_regSet(FLAG_TICK_IGNORE, 1);
    sc_regSet(FLAG_WRONG_COMMAND, 0);
    sc_memoryInit();
    sc_instSet(0);
    sc_accumSet(0);

    mt_clrscr();
}

void refresh(int x, int y)
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
    interface(x, y);
}

void key_handler(int *exit, int * x, int * y)
{
    enum keys key = none;
    rk_readkey(&key);
    if (key == r) {
        int8_t tmp;
        sc_regGet(FLAG_TICK_IGNORE, &tmp);
        tmp = (tmp) ? 0 : 1;
        sc_regSet(FLAG_TICK_IGNORE, tmp);
    }

    int8_t freq_flg;
    sc_regGet(FLAG_TICK_IGNORE, &freq_flg);
    if (!freq_flg)
        return;

    if (key == q)
        *exit = 1;
    if (key == l)
        load_mem();
    if (key == s)
        save_mem();
    if (key == up)
        *x -= 1;
    if (key == down)
        *x += 1;
    if (key == left)
        *y -= 1;
    if (key == right)
        *y += 1;
    if (key == i) {
        init();
        *x = 0, *y = 0;
        refresh(*x, *y);
    }
    if (key == f5)
        set_accum();
    if (key == f6)
        set_instcnt();
    if (key == t)
        step(x, y);
    if (key == enter)
        set_mem();
    coordX = *x;
    coordY = *y;
}

void interface(int x, int y)
{
    print_mem(x, y);
    print_accum();
    print_instcnt();
    print_operation(x, y);
    print_flg();
    print_membc(x, y);
}

void main_loop()
{
    int exit = 0;
    int cnt = 0;
    int x = 0, y = 0;
    refresh(x, y);
    while (!exit) {
        interface(x, y);
        key_handler(&exit, &x, &y);
        if (cnt == 5) {
            mt_clrscr();
            refresh(x, y);
            cnt = 0;
        }
        cnt++;
    }
}
