/**
 * Лабораторная работа №3
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    double sum = 0, x;
    printf("i=1..n, n=");
    scanf("%d", &n);
    printf("x=");
    scanf("%f", &x);

    for (int i = 1; i <= n; i++) {
        sum += x / sin(i * x);
    }

    printf("%2f\n", sum);
    return 0;
}

