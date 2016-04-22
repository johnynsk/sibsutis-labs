/**
 * Лабораторная работа №2
 * Задача №5
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <exception>

int getHalfByMonth(int month)
{
    if (month <= 0 || month > 12) {
        throw std::exception();
    }

    return (month - 1) / 6  + 1;
}


int getQuarterByMonth(int month)
{
    if (month <= 0 || month > 12) {
        throw std::exception();
    }

    return (month - 1) / 3 + 1;
}


int main()
{
    int N;
    printf("Введите номер месяца = ");
    scanf("%d", &N);
    int H;
    int Q;

    try {
        H = getHalfByMonth(N);
        Q = getQuarterByMonth(N);
    } catch (std::exception &e) {
        printf ("Ошибка в вводе месяца. Введите месяц от 1 до 12\n");
        return 1;
    }

    printf("Результат: %d месяц - это %d половина года, %d квартал\n", N, H, Q);

    return 0;
}

