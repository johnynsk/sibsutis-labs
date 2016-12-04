/**
 * Лабораторная работа №4
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#define ITEMS_COUNT 100000

float simpson (float* data, float a, float b)
{
    float sum = 0;
    float h = (b - a) / ITEMS_COUNT;

    sum += data[0] + data[ITEMS_COUNT - 1];

    for (int i = 1; i <= ITEMS_COUNT - 2; i++ ) {
        if (i % 2 == 0) {
            sum += 2 * data[i];
        } else {
            sum += 4 * data[i];
        }
    }

    sum *= h / 3;

    return sum;
}

float trapezium (float* data, float a, float b)
{
    float sum = 0;
    float h = (b - a) / ITEMS_COUNT;

    sum += (data[0] + data[ITEMS_COUNT - 1]) / 2;

    for (int i = 1; i <= ITEMS_COUNT - 2; i++ ) {
        sum += data[i];
    }

    sum *= h;

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

float* getItems(float a, float b)
{
    static float items[ITEMS_COUNT];
    float delta = (b - a) / (ITEMS_COUNT - 1);

    for (int i = 0; i < ITEMS_COUNT; i++) {
        items[i] = a + delta * i;
    }

    return items;
}

void output(float* data)
{
    for (int i = 0; i < ITEMS_COUNT; i++) {
        printf("%d: %f\n", i, data[i]);
    }
}

int main ()
{
    float* rawItems;
    float* calculatedItems;
    float a, b;

    printf("Введите пределы интегрирования, a = ");
    scanf("%f", &a);
    printf("b = ");
    scanf("%f", &b);

    rawItems = getItems(a, b);
    calculatedItems = calc(rawItems);

    printf("Интеграл методом трапеции = %f\n", trapezium(calculatedItems, a, b));
    printf("Интеграл методом Симпсона = %f\n", simpson(calculatedItems, a, b));

    return 0;
}

