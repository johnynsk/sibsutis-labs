/**
 * Лабораторная работа №5
 * Задача №2
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <string.h>
#define WORDS_COUNT 10

bool check (char* word)
{
    int i = 0;

    while (word[i] != '\0') {
        if (word[i] >= '0' && word[i] <= '9') {
            return false;
        }

        i++;
    }

    return true;
}

int main ()
{
    char words[WORDS_COUNT][40], temp[40];
    int i = 0;
    printf("Введите %d строк не содержащих цифр:\n", WORDS_COUNT);

    while (i < WORDS_COUNT) {
        scanf("%s", &temp);

        strcpy(words[i++], temp);
    }

    for (i = 0; i < WORDS_COUNT; i++) {
        if (!check(words[i])) {
            words[i][0] = '\0';
        }
    }

    printf("Следующие слова соответствуют условию:\n");

    for (i = 0; i < 10; i++) {
        if (strlen(words[i])) {
            printf("%s\n", words[i]);
        }
    }

    return 0;
}

