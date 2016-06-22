/**
 * Лабораторная работа №8
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <iostream>
#include <string>
#define INSTITUTIONS 4

using namespace std;

struct institution {
    string name;
    int studentsCount;
    int departmentCount;
    int cathedralCount;
};

int main ()
{
    struct institution institutions[INSTITUTIONS];
    int studentsCount = 0;
    int departmentCount = 0;
    int cathedralCount = 0;

    for (int i = 0; i < INSTITUTIONS; i++) {
        cout << "#" << i << " Введите название учебного заведения: > ";
        std::getline(cin, institutions[i].name, '\n');

        if (!institutions[i].name.length()) {
            std::getline(cin, institutions[i].name, '\n');
        }

        cout << endl << institutions[i].name << endl;
        cout << "#" << i << " Введите количество студентов: > ";
        cin >> institutions[i].studentsCount;
        cout << "#" << i << " Введите количество факультетов: > ";
        cin >> institutions[i].departmentCount;
        cout << "#" << i << " Введите количество кафедр: > ";
        cin >> institutions[i].cathedralCount;
    }

    for (int i = 0; i < INSTITUTIONS; i++) {
        studentsCount += institutions[i].studentsCount;
        departmentCount += institutions[i].departmentCount;
        cathedralCount += institutions[i].cathedralCount;
    }

    cout << "Общее количество студентов = " << studentsCount << "; факультетов = " << departmentCount
        << "; кафедр = " << cathedralCount << ";" << endl;

    return 0;
}

