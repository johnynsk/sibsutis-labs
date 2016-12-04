/**
 * Лабораторная работа №3
 * Перестановки Дейкстры
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <iostream>
#include <cstdlib>

using namespace std;

bool reflex(unsigned int power, unsigned int *array)
{
    for (int i = 0; i < power; i++) {
        //if
    }
}

int main()
{
    unsigned long power;
    unsigned int *set;
    char item;

    cout<<"Введите мощность множества |A| > ";
    cin>>power;

    set = (unsigned int*) malloc (sizeof(unsigned int) * power * power);

    size_t count = 0;
    unsigned int i;
    unsigned int j;

    while (count < power * power) {
        i = count / power;
        j = count % power;
        cout<<"["<<i<<","<<j<<"]: >";
        cin>>item;

        if (item < '0' || item > '1') {
            cout<<"неверно задан элемент (0/1)"<<endl;
            continue;
        }
        set[i*power + j] = (unsigned int) (item - '0');

        count++;
    }

    for (i = 0; i < count / power; i++) {
        cout<<i<<": ";

        for (j = 0; j < power; j++) {
            cout<<(char) (set[i * power + j] + '0')<<" ";
        }

        cout<<endl;
    }

    return 0;
}

