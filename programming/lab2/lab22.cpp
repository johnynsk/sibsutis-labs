/**
 * Лабораторная работа №2
 * Задача №5
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>

int main()
{
    int N;
    int H;
    int Q;
    printf("Введите номер месяца = ");
    scanf("%d", &N);
    switch(N) {
        case 1:
        case 2:
        case 3:
            H = 1;
            Q = 1;
            break;
        case 4:
        case 5:
        case 6:
            H = 1;
            Q = 2;
            break;
        case 7:
        case 8:
        case 9:
            H = 2;
            Q = 3;
            break;
        case 10:
        case 11:
        case 12:
            H = 2;
            Q = 4;
            break;
        default:
            printf ("Ошибка в вводе месяца. Введите месяц от 1 до 12\n");
            return 1;
    }

    printf("Результат: %d месяц - это %d половина года, %d квартал\n", N, H, Q);

    return 0;
}

