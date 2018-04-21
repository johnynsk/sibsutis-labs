#ifndef GENCHAR_H
#define GENCHAR_H
#include "../lib/char.h"
#include <fcntl.h>
#include <stdlib.h>
#endif
int * getchar2(int pos)
{
    switch (pos) {
        case 0: return char_0();
        case 1: return char_1();
        case 2: return char_2();
        case 3: return char_3();
        case 4: return char_4();
        case 5: return char_5();
        case 6: return char_6();
        case 7: return char_7();
        case 8: return char_8();
        case 9: return char_9();
        case 10: return char_a();
        case 11: return char_b();
        case 12: return char_c();
        case 13: return char_d();
        case 14: return char_e();
        case 15: return char_f();
        case 16: return char_plus();
        case 17: return char_minus();
    }
}

int main() {
    int fd = open("font", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int * chars = malloc(sizeof(int) * 64 * 18);
    for (int i = 0; i < 18; i++) {
        int * bchar = getchar2(i);
        memcpy(&chars[i * 64], &bchar[0], 64);
        for(int j = 0; j < 64; j++ ){
            printf("%d:", chars[i * 64 + j]);
        }
        break;
    }
    bc_bigcharwrite(fd, chars, 18);

    return 0;
}
