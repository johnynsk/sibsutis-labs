#include "../lib/term.h"

int main() {
    printf("mt_clrscr()\n");
    if (!mt_clrscr()) {
    printf("passed\n");
    int rows, cols;
    printf("mt_getscreensize()\n");
    mt_getscreensize(&cols, &rows);
    cols /= 2;
    rows /= 2;
    printf("passed\n");
    printf("mt_gotoXY()\n");
    mt_gotoXY(rows, cols);
    printf("passed\n");
    mt_getscreensize(&rows, &cols);
    mt_gotoXY(cols, rows);
    printf("\n");
    return 0;
    }

    return 1;
}

int main4()
{
    printf("test mt_clrscr():\n");
    if (!mt_clrscr()) {
        printf("passed");
        int rows, cols;
        printf("test mt_getscreensize()");
        if (!mt_getscreensize(&cols, &rows)) {
 //           printf("passed \n");
            printf("rows = %d, cols %d", rows, cols);
            rows /= 2;
            cols /= 2;
            cols -= 10;
            //printf("test mt_gotoXY():");
            if (!mt_gotoXY(rows, cols)) {
                printf("passed");
                mt_getscreensize(&rows, &cols);
                mt_gotoXY(rows, cols);
                printf(" ");
                //printf("TEST PASSED*");
            }
        }
    }

    return 0;
}
