#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "lib/ui.h"
#include "lib/log.h"

struct itimerval nval, oval;

void sighandler(int signal)
{
    trace;
    if (signal == SIGKILL) {
        mt_clrscr();
        exit(0);
    }

    if (signal != SIGALRM) {
        return;
    }

    int tick_ignore;
    int wrong_command;
    int current_instruction;

    sc_regGet(FLAG_TICK_IGNORE, &tick_ignore);
    sc_regGet(FLAG_WRONG_COMMAND, &wrong_command);
    sc_instGet(&current_instruction);
    if (!tick_ignore) {
        CU();
        interface(coordX, coordY);
    }
}

int main()
{
    log_setlevel(LOG_OFF);
//    log_setlevel(LOG_TRACE_DETAIL);
//    log_setlevel(LOG_INFO);
log_setlevel(LOG_DEBUG);
    trace;
    init();
    signal(SIGALRM, sighandler);
    signal(SIGKILL, sighandler);

    nval.it_interval.tv_sec = 0;
    nval.it_interval.tv_usec = 300000;
    nval.it_value.tv_sec = 0;
    nval.it_value.tv_usec = 50000;
    setitimer(ITIMER_REAL, &nval, &oval);

    main_loop();

    write(1, "\e[0m", 4);
    rk_mytermrestore();
    mt_clrscr();
    return 0;
}

int main2(){
    return 0;
}
