#include "ui.h"

int *font = NULL;

void dump_mem()
{
    trace;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int command, operand, value;
            sc_memoryGet(i * 10 + j, &value);
            sc_commandDecode(value, &command, &operand);
            log_info(sformat(" %d_%d:%d@%d %X:%X ", i*10 + j, command, operand, value, command, operand));
        }
    }
}

void print_mem(int x, int y)
{
    trace;
    //dump_mem();
    int instruction;
    sc_instGet(&instruction);
    for (int i = 0; i < 100; i++) {
        int command, operand;
        int value;
        sc_memoryGet(i, &value);
        sc_commandDecode(value, &command, &operand);

        char result[5];
        if (command < 16 && operand < 16) {
            sprintf(result, "0%X:0%X", command, operand);
        } else if (command < 16 && operand >= 16) {
            sprintf(result, "0%X:%X", command, operand);
        } else if (command >= 16 && operand < 16) {
            sprintf(result, "%X:0%X", command, operand);
        } else {
            sprintf(result, "%X:%X", command, operand);
        }

        if (i / 10 == y && i % 10 == x) {
            mt_setbgcolor(COLOR_RED);

            mt_gotoXY(0, 23);
            char buf[80];
            //sprintf(buf, "val: %d; cmd: %d; ond: %d;   ", value, command, operand);
            //print_on_screen(buf);
            mt_resetcolor();
        }

        mt_gotoXY(2 + 6 * (i / 10), 2 + (i % 10));
        if (i == instruction) {
            mt_setbgcolor(COLOR_RED);
        }
        if (i / 10 == y && i % 10 == x) {
            mt_setbgcolor(COLOR_GREEN);
        }

        print_on_screen(result);
        mt_resetcolor();
    }
}

void print_accum()
{
    trace;
    mt_gotoXY(71, 2);
    int acc = 0;
    sc_accumGet(&acc);
    char tmp[4];
    sprintf(tmp, "%4d", acc);
    print_on_screen(tmp);
}

void print_instcnt()
{
    trace;
    mt_gotoXY(63, 5);
    int inst = 0;
    sc_instGet(&inst);
    int memory_contents, command, operand;
    sc_memoryGet(inst, &memory_contents);
    sc_commandDecode(memory_contents, &command, &operand);
    print_on_screen(sformat("%18s", sformat("%s|%d @ %2d", command_name(command), operand, inst)));
}

void print_operation(int x, int y)
{
    trace;
    int memory_contents;
    log_debug(sformat("current_instruction %d", x+y*10));
    sc_memoryGet(x + y * 10, &memory_contents);
    int command;
    int operation;
    sc_commandDecode(memory_contents, &command, &operation);
    mt_gotoXY(63, 8);
    print_on_screen(sformat("%18s", sformat("%s|%d @ %d%d", command_name(command), operation, y, x)));
}

void print_flags()
{
    trace;
    char flags[] = "ODMTC";
    mt_gotoXY(67, 11);
    for (int i = 0; i < 5; i++) {
        int value;
        sc_regGet(1 << i, &value);

        if (value) {
            mt_setfgcolor(COLOR_RED);
        } else {
            mt_setfgcolor(COLOR_WHITE);
        }
        trace;
        print_on_screen(sformat("%c ", flags[i]));
        mt_resetcolor();
    }
}

void print_bigmemory(int x, int y)
{
    trace;
    int value;
    int command, operand;
    log_debug(sformat("current_instruction %d", 10*y+x));
    sc_memoryGet(10 * y + x, &value);
    sc_commandDecode(value, &command, &operand);
    int sign = value < 0 ? 1 : 0;
    bc_printbigchar(&font[(16 + sign) * 64], 2 + 10 * 0, 14, COLOR_YELLOW, COLOR_GREEN);
    bc_printbigchar(&font[(command / 16) * 64], 2 + 10 * 1, 14, COLOR_YELLOW, COLOR_GREEN);
    bc_printbigchar(&font[(command % 16) * 64], 2 + 10 * 2, 14, COLOR_YELLOW, COLOR_GREEN);

    bc_printbigchar(&font[(operand / 16) * 64], 2 + 10 * 3, 14, COLOR_YELLOW, COLOR_GREEN);
    bc_printbigchar(&font[(operand % 16) * 64], 2 + 10 * 4, 14, COLOR_YELLOW, COLOR_GREEN);
}

void print_keys()
{
    trace;
    bc_box(51, 13, 33, 10);
    mt_gotoXY(52, 13);
    const char tmp[] = " Keys: ";
    print_on_screen(tmp);
    const char *tmp1[] = {"l - load", "s - save", "r - run", "t - step",
        "i - reset", "F5 - accumulator", "F6 - instructionCounter", "F9 - enter command"};
    for (int i = 0; i < 8; i++) {
        mt_gotoXY(52, 14 + i);
        print_on_screen(tmp1[i]);
    }
}

void load_mem()
{
    trace;
    bc_box(20, 6, 20, 5);
    mt_gotoXY(24, 7);
    print_on_screen("Load\n");
    char tmp[255] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 255);
    tmp[strlen(tmp) - 1] = '\0';
    if (sc_memoryLoad(tmp)) {
        bc_box(20, 6, 20, 5);
        mt_gotoXY(23, 7);
        print_on_screen("Failed to open\n");
        mt_gotoXY(29, 9);
        mt_setbgcolor(COLOR_RED);
        print_on_screen("OK");
        mt_resetcolor();
        mt_gotoXY(30, 9);
        read(1, tmp, 1);
    }
    sc_accumSet(0);
    sc_instSet(0);
    refresh(coordX, coordY);
}

void save_mem()
{
    trace;
    bc_box(20, 6, 20, 5);
    mt_gotoXY(23, 7);
    print_on_screen("Save to\n");
    char tmp[255] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 255);
    tmp[strlen(tmp) - 1] = '\0';
    if (sc_memorySave(tmp)) {
        bc_box(20, 6, 20, 5);
        mt_gotoXY(23, 7);
        print_on_screen("Failed to save\n");
        mt_gotoXY(29, 9);
        mt_setbgcolor(COLOR_RED);
        print_on_screen("OK");
        mt_setbgcolor(COLOR_DEFAULT);
        mt_gotoXY(30, 9);
        read(1, tmp, 1);
    }
    mt_gotoXY(0, 27);
    print_on_screen(tmp);
    refresh(coordX, coordY);
}

void set_accum()
{
    trace;
    bc_box(20, 6, 20, 5);
    mt_gotoXY(23, 7);
    print_on_screen("Set accum to\n");
    char tmp[5] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 5);
    int new_acc = atoi(tmp);
    sc_accumSet(new_acc);
    refresh(coordX, coordY);
}

void set_instruction()
{
    trace;
    bc_box(20, 6, 26, 5);
    mt_gotoXY(22, 7);
    print_on_screen("Set instructionCounter to\n");
    char tmp[5];// = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 5);
    tmp[strlen(tmp) - 1] = '\0';
    int new_inst = atoi(tmp);
    mt_gotoXY(0, 28);
    if (new_inst < 0 || new_inst > 99) {
        //TODO CHECK!!
        return;
    }
    sc_instSet(new_inst);
    refresh(coordX,coordY);
}

void enter_command(int command)
{
    trace;
    char tmp[10];// = "\0";

    if (command == -1) {
        bc_box(20, 6, 26, 5);
        mt_gotoXY(22, 7);
        print_on_screen("Enter command id\n");
        mt_gotoXY(21, 9);
        read(1, tmp, 5);
        tmp[strlen(tmp) - 1] = '\0';
        command = atoi(tmp);
    }

    bc_box(20, 6, 26, 5);
    mt_gotoXY(22, 7);
    print_on_screen("Enter operand\n");
    mt_gotoXY(21, 9);
    read(1, tmp, 5);
    tmp[strlen(tmp) - 1] = '\0';
    int8_t operand = atoi(tmp);

    bc_box(20, 6, 20, 5);
    mt_gotoXY(23, 7);

    int output;
    sc_commandEncode(command, operand, &output);
    sc_memorySet(10 * coordY + coordX, output);

    refresh(coordX,coordY);
}

void enter_command_name()
{
    trace;
    bc_box(20, 6, 26, 5);
    mt_gotoXY(22, 7);
    print_on_screen("Enter command name\n");
    char tmp[8];// = "";
    mt_gotoXY(21, 9);
    read(1, tmp, 7);
    log_debug(tmp);
    tmp[strlen(tmp) - 1] = '\0';
    log_debug(tmp);
    int command = command_id(tmp);

    enter_command(command);
}


void set_mem()
{
    trace;
    bc_box(20, 6, 26, 5);
    mt_gotoXY(22, 7);
    print_on_screen("Set memory(dec) to\n");
    char tmp[11] = "\0";
    mt_gotoXY(21, 9);
    read(1, tmp, 10);
    tmp[strlen(tmp) - 1] = '\0';

    if (tmp[0] != '\n' && tmp[0] != '\0') {
        int tmp1 = atoi(tmp);
        sc_memorySet(10 * coordY + coordX, tmp1);
    }
    refresh(coordX, coordY);
}

void step(int * x, int * y)
{
    trace;
//    char tmp[255] = "\0";
//    log_debug(sprintf(tmp, "step called %d %d\n", *x, *y));
    CU();

    int current_instruction = 0;
    sc_instGet(&current_instruction);
    *x = current_instruction / 10;
    *y = current_instruction % 10;
}

void init()
{
    trace;
    int fd = open("font", O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int count = 0;
    font = (int*) malloc(sizeof(int) * 64 * 18);

    if (bc_bigcharread(fd, font, 18, &count) == -1 && count < 18) {
        print_on_screen_stream("Failed to open font\n", 2);
        return;
    }

    sc_regInit();
    sc_regSet(FLAG_OVERFLOW, 0);
    sc_regSet(FLAG_DIVISION_BY_ZERO, 0);
    sc_regSet(FLAG_MEMORY_ERROR, 0);
    sc_regSet(FLAG_WRONG_COMMAND, 0);
    sc_regSet(FLAG_TICK_IGNORE, 1);
    sc_memoryInit();
    sc_instSet(0);
    sc_accumSet(0);
}

void refresh(int x, int y)
{
    trace;
    bc_box(1, 1, 61, 12);
    mt_gotoXY(30, 0);
    char memory[] = " Memory ";
    print_on_screen(memory);

    bc_box(62, 1, 22, 3);
    mt_gotoXY(66, 1);
    char accumulator[] = " accumulator ";
    print_on_screen(accumulator);

    bc_box(62, 4, 22, 3);
    mt_gotoXY(63, 4);
    char instruction[] = " instructionCounter ";
    print_on_screen(instruction);

    bc_box(62, 7, 22, 3);
    mt_gotoXY(68, 7);
    char operation[] = " Operation ";
    print_on_screen(operation);

    bc_box(62, 10, 22, 3);
    mt_gotoXY(69, 10);
    char flags[] = " Flags ";
    print_on_screen(flags);

    bc_box(1, 13, 50, 10);
    print_keys();
    interface(x, y);
}

void key_handler(int *exit, int * x, int * y)
{
    trace;
    enum keys key = none;
    rk_readkey(&key);

    int tick_ignore;
    sc_regGet(FLAG_TICK_IGNORE, &tick_ignore);

    if (key == r) {
        tick_ignore = (tick_ignore) ? 0 : 1;
        //sc_regSet(FLAG_WRONG_COMMAND, 1);
        sc_regSet(FLAG_TICK_IGNORE, tick_ignore);
    } else if (key == up) {
        *x -= 1;

        if (*x < 0) {
            *x = 9;
        }
    } else if (key == down) {
        *x += 1;

        if (*x > 9) {
            *x = 0;
        }
    } else if (key == left) {
        *y -= 1;

        if (*y < 0) {
            *y = 9;
        }
    } else if (key == right) {
        *y += 1;
        if (*y > 9) {
            *y = 0;
        }
    }

    coordX = *x;
    coordY = *y;


    if (!tick_ignore) {
        return;
    }

    if (key == q) {
        sc_regSet(FLAG_TICK_IGNORE, 1);
        *exit = 1;
    }

    if (key == l) {
        load_mem();
    } else if (key == s) {
        save_mem();
    } else if (key == f5) {
        set_accum();
    } else if (key == f6) {
        set_instruction(x, y);
    } else if (key == f7) {
        enter_command(-1);
    } else if (key == f9) {
        enter_command_name();
    } else if (key == t) {
        step(x, y);
        sc_regSet(FLAG_TICK_IGNORE, 1);
    } else if (key == enter) {
        set_mem();
    } else if (key == i) {
        init();
        sc_regSet(FLAG_TICK_IGNORE, 1);
        *x = 0, *y = 0;
        refresh(*x, *y);
    }


    coordX = *x;
    coordY = *y;
}

int ui_numeric_input(const char * message)
{
    trace;
    rk_mytermrestore();
    int tick_ignore;
    sc_regGet(FLAG_TICK_IGNORE, &tick_ignore);

    bc_box(20, 6, 20, 5);
    mt_gotoXY(21, 7);
    print_on_screen(message);
    char string_value[10] = "\0";

    mt_gotoXY(21, 9);
    read(1, string_value, 10);

    int int_value = atoi(string_value);

    refresh(coordX, coordY);
    sc_regSet(FLAG_TICK_IGNORE, tick_ignore);
    rk_mytermsave();

    return int_value;
}

char * ui_string_input(const char * message)
{
    trace;
    rk_mytermrestore();
    int tick_ignore;
    sc_regGet(FLAG_TICK_IGNORE, &tick_ignore);

    bc_box(20, 6, 20, 5);
    mt_gotoXY(21, 7);
    print_on_screen(message);
    char string_value[255] = "\0";

    mt_gotoXY(21, 9);
    read(1, string_value, 255);

    refresh(coordX, coordY);
    sc_regSet(FLAG_TICK_IGNORE, tick_ignore);
    rk_mytermsave();

    return string_value;
}

int ui_readvalue(int address)
{
    trace;
    rk_mytermrestore();
    int tick_ignore;
    sc_regGet(FLAG_TICK_IGNORE, &tick_ignore);
    sc_regSet(FLAG_TICK_IGNORE, 1);

    bc_box(20, 6, 20, 5);
    mt_gotoXY(21, 7);
    print_on_screen("Input value (dec)\n");
    char string_value[10] = "\0";

    mt_gotoXY(21, 9);
    read(1, string_value, 10);

    int int_value = atoi(string_value);
    sc_memorySet(address, int_value);

    refresh(coordX, coordY);
    sc_regSet(FLAG_TICK_IGNORE, tick_ignore);
    rk_mytermsave();

    return 0;
}

int ui_printvalue(int address)
{
    trace;
    int tick_ignore;
    sc_regGet(FLAG_TICK_IGNORE, &tick_ignore);
    sc_regSet(FLAG_TICK_IGNORE, 1);

    bc_box(20, 6, 20, 5);
    mt_gotoXY(23, 7);

    int value;
    sc_memoryGet(address, &value);
    char string_value[10] = "\0";
    sprintf(string_value, "%d", value);
    print_on_screen(string_value);
    log_debug(sformat("current_instruction %d value = %d; strvalue = %s .", address, value, string_value));


    mt_gotoXY(29, 9);
    mt_setbgcolor(COLOR_RED);
    print_on_screen("OK");

    mt_resetcolor();
    mt_gotoXY(30, 9);
    char buffer[10]; //press any key
    read(1, buffer, 1);

    sc_regSet(FLAG_TICK_IGNORE, tick_ignore);
    return 0;
}

void interface(int x, int y)
{
    trace;
    print_mem(x, y);
    print_accum();
    print_instcnt();
    log_debug(sformat("x=%d y=%d", x, y));
    print_operation(x, y);
    print_flags();
    print_bigmemory(x, y);
}

void main_loop()
{
    trace;
    int exit = 0;
    int cnt = 0;
    int x = 0, y = 0;
    refresh(x, y);
    while (!exit) {
        trace;
        log_debug(sformat("x=%d y=%d", x, y));
        interface(x, y);
        key_handler(&exit, &x, &y);
        if (cnt == 15) {
            mt_clrscr();
            refresh(x, y);
            cnt = 0;
        }
        cnt++;
    }
}
