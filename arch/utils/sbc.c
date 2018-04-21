#include <string.h>
#include <stdio.h>
#define WRONG_COMMAND 16

int commands;
FILE * foutput, input;

void addCommand(const char * command, int operand)
{
    fprintf(foutput, "%d %s %d\n", commands, command, operand);
    commands++;
}

void parseLet();

int parseCommand(const char * command)
{
    if (!strcmp(command, "REM")) {
    } else if (!strcmp(command, "INPUT")) {
    } else if (!strcmp(command, "PRINT")) {
    } else if (!strcmp(command, "GOTO")) {
    } else if (!strcmp(command, "IF")) {
    } else if (!strcmp(command, "LET")) {
        parseLet();
    } else if (!strcmp(command, "END")) {
        addCommand("HALT", 0);
        return 0;
    }

    return WRONG_COMMAND;
}

int main()
{
    commands = 0;
}
