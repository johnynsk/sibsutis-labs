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

void pbchar(int * bchar) {
    for(int j = 0; j < 64; j++ ){
        if (j % 8 == 0) {
            printf("\n");
        }

        printf("%d:", bchar[j]);
    }
}

int main() {
    int fd = open("font2", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int * chars = malloc(sizeof(int) * 64 * 18);
    for (int i = 0; i < 18; i++) {
//        int * bchar = getchar2(i);
//        memcpy(&chars[i * 64], getchar2(i), sizeof(int) * 64);
    }
    int count;
    bc_bigcharread(fd, chars, 18, &count);
    pbchar(&chars[10 * 64]);
//    bc_bigcharwrite(fd, chars, 18);

    return 0;
}
