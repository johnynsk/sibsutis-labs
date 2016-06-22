/**
 * Лабораторная работа №6
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

float f (float a, float b, float x)
{
    if (fabs(x) >= a) {
        return 0;
    }

    return b * exp(-pow(a, 2) / (pow(a, 2) - pow(fabs(x), 2)));
}

int main ()
{
    float a, b, x;

    cout << "Введите a, b, x через пробел" << endl;
    cin >> a >> b >> x;

    cout << "result = " << f(a, b, x) << "#" << x << ":" << a << ":" <<b << endl;

    return 0;
}

