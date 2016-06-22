/**
 * Лабораторная работа №7
 * Методом деления отрезка пополам найти с точностью epsilon=0.0001 корень уравнения
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/**
 * Искомое уравнение
 */
double equal(double x)
{
    return cos(2 / x) - 2 * sin(1 / x) + 1 / x;
}

/**
 * Вычисление корня
 */
double root(double a, double b, double epsilon)
{
    double middle = fabs(a - b) / 2 + a;

    if (fabs(a - b) <= epsilon) {
        return equal(middle) * epsilon;
    }

    return root(a, middle, epsilon) + root(middle, b, epsilon);
}

int main ()
{
    double a, b, epsilon;
    cout << "Задайте границы отрезка [a, b]: a> ";
    cin >> a;
    cout << "b> ";
    cin >> b;
    cout << "epsilon> ";
    cin >> epsilon;

    cout << "Результат = " << (double) root(min(a, b), max(a, b), epsilon) << " +- " << epsilon << endl;

    return 0;
}

