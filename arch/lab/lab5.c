#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "../lib/ui.h"

struct itimerval nval, oval;

void sighandler2(int signum)
{
    if (signum == SIGKILL) {
        mt_clrscr();
        exit(0);
    }
    if (signum == SIGALRM) {
        int8_t freq_flg = 0,
            comm_flg = 0,
            inst_curr = 0;
        sc_regGet(FLAG_TICK_IGNORE, &freq_flg);
        sc_regGet(FLAG_WRONG_COMMAND, &comm_flg);
        sc_instGet(&inst_curr);

        if (comm_flg) {
            sc_regSet(FLAG_TICK_IGNORE, 1);
        }

        if (!freq_flg) {
            step(&coordX, &coordY);
            interface(coordX, coordY);
        }

        if (inst_curr == 99)
            sc_regSet(FLAG_TICK_IGNORE, 1);
    }
}

int main2()
{
    signal(SIGALRM, sighandler);
    signal(SIGKILL, sighandler);

    nval.it_interval.tv_sec = 0;
    nval.it_interval.tv_usec = 80000;
    nval.it_value.tv_sec = 0;
    nval.it_value.tv_usec = 50000;
    setitimer(ITIMER_REAL, &nval, &oval);

    init();

    main_loop();

    write(1, "\e[0m", 4);
    rk_mytermrestore();
    mt_clrscr();
    return 0;
}
