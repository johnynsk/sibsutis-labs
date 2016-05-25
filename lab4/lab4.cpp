/**
 * Лабораторная работа №4
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <math.h>
#define ITEMS_COUNT 5

float simpson (float* data, int a, int b)
{
    float sum = 0;

    sum += data[a] + data[b];

    for (int i = a + 1; i <= b - 1; i++ ) {
        if (i % 2 == 0) {
            sum += 2 * data[i];
        } else {
            sum += 4 * data[i];
        }
    }

    float h = 1; // (b - a) / (b - a)

    sum *= h / 3;

    return sum;
}

float trapezium (float* data, int a, int b)
{
    float sum = 0;

    sum += (data[a] + data[b]) / 2;

    for (int i = a + 1; i <= b - 1; i++ ) {
        sum += data[i];
    }

    return sum;
}

float f (float x)
{
    return 1 / (sqrt(x) * (0.5 + 0.1 * pow(x, 3)));
}

float* calc (float* data)
{
    static float result[ITEMS_COUNT];

    for (int i = 0; i < ITEMS_COUNT; i++) {
        result[i] = f(data[i]);
    }

    return result;
}

float* readItems()
{
    static float items[ITEMS_COUNT];
    float item;

    for (int i = 0; i < ITEMS_COUNT; i++) {
        printf("Введите элемент массива (осталось %d): ", ITEMS_COUNT - i);
        scanf("%f", &items[i]);
    }

    return items;
}

void output(float* data)
{
    for (int i = 0; i < ITEMS_COUNT; i++) {
        printf("%f", data[i]);
    }
}

int main ()
{
    float* rawItems;
    float* calculatedItems;
    int a, b;

    rawItems = readItems();
    calculatedItems = calc(rawItems);

    printf("Введите пределы интегрирования, a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);

    printf("Интеграл методом трапеции = %f\n", trapezium(calculatedItems, a, b));
    printf("Интеграл методом Симпсона = %f\n", simpson(calculatedItems, a, b));

    return 0;
}

