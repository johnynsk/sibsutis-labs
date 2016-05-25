/**
 * Лабораторная работа №3
 * Задача №2
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <math.h>

int main()
{
    int n, i = 1;
    double sum = 0, x;
    printf("i=1..n, n=");
    scanf("%d", &n);
    printf("x=");
    scanf("%f", &x);

    do {
        sum += x / sin(i * x);
        i++;
    } while (i <= n);

    printf("%f\n", sum);
    return 0;
}

