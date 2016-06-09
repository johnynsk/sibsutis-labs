/**
 * Лабораторная работа №6
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

float f (int a, int b, int x)
{
    if (abs(x) > a) {
        return 0;
    }

    return b * exp(-pow(a, 2) / (pow(a, 2) - pow(abs(x), 2)));
}

int main ()
{
    float a, b, x;

    cout<<"Введите a, b, x через пробел"<<endl;
    cin>>a>>b>>x;

    cout<<"result = "<<f(a, b, x)<<endl;

    return 0;
}

