/**
 * Лабораторная работа №1
 * Задача №5
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <math.h>


float calc(int z, int t, float y)
{
    return (8 * pow(z, 2) + 1) / (y + pow(t, 2));
}


int main()
{
    int z = 1;
    int t = 2;
    float y = t + z;

    float x = calc(z, t, y);

    printf("Дано: t=%d, z=%d, y=%f\n", t, z, y);
    printf("Результат: x=%f\n", x);

    return 0;
}

