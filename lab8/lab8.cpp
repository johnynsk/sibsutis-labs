/**
 * Лабораторная работа №8
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <iostream>
#define INSTITUTIONS 4

using namespace std;

struct institution {
    char *name;
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
        cout<<"Ввод учебного заведения #"<<i<<endl;
        cout<<"Введите название учебного заведения: >";
        cin>>institutions[i].name;
        cout<<"Введите количество студентов: >";
        cin>>institutions[i].studentsCount;
        cout<<"Введите количество факультетов: >";
        cin>>institutions[i].departmentCount;
        cout<<"Введите количество кафедр: >";
        cin>>institutions[i].cathedralCount;
    }

    for (int i = 0; i < INSTITUTIONS; i++) {
        studentsCount += institutions[i].studentsCount;
        departmentCount += institutions[i].departmentCount;
        cathedralCount += institutions[i].cathedralCount;
    }

    cout<<"Общее количество студентов = "<<studentsCount<<"; факультетов = "<<departmentCount<<"; кафедр = "<<cathedralCount<<";"<<endl;

    return 0;
}

