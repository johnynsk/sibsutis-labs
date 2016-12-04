/**
 * Лабораторная работа №9
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
    ifstream input;
    ofstream output;
    char symbol;

    input.open("lab9.in.txt", ifstream::binary);
    output.open("lab9.out.txt");

    if (!input.is_open() || !output.is_open()) {
        cout<<"Что-то пошло не так"<<endl;
    }

    while (input.good()) {
        symbol = input.get();

        if (symbol == 'm') {
            symbol = 'M';
        }

        output<<(char)symbol;
    }

    input.close();
    output.close();

    return 0;
}

