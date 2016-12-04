#ifndef PROJECT_APP
#define PROJECT_APP
#include <iostream>
#include <string>
#include "app/constants.h"
#include "app/man.h"
#include "app/file.h"
#include <string.h>
#include <cstdlib>

using namespace std;

namespace Application {


class Iterator
{
    public:
        Iterator();
        void run();

    private:
        string filename;
        void _printUsage();
        void _search();
        void _showall();
        void _load();
        void _create();
        void _modify();
        void _insert();
};

Iterator::Iterator()
{
    std::cout << "test output App" <<std::endl;
}

void
Iterator::run()
{
    this->filename = "lab10.dat";
    int operation;

    while (true) {
        this->_printUsage();

        cin >> operation;

        switch (operation) {
            case OPERATION_HALT:
                return;

                break;

            case OPERATION_FILENAME:
                _load();

                continue;

            case OPERATION_SHOWALL:
                _showall();

                break;

            case OPERATION_SEARCH:
                _search();

                continue;

            case OPERATION_INSERT:
                _insert();
                continue;

            case OPERATION_MODIFY:
                _modify();

                continue;

            case OPERATION_CREATE:
                _create();

                continue;
        }
    }
}

void
Iterator::_insert()
{
    Man item = Application::readMan();

    while (true) {
        cin.clear();
        cout << "Введите позицию в файле (^ - начало файла, $ - конец файла, любое число - позиция в файле)" << endl
            << "После этого элемента будет добавлен ваш > ";

        std::string position;

        getline(cin, position, '\n');

        cout << "position: " << position;
        if (position == "$") {
            Application::File::insert(filename, item, Application::POSITION_END);
            break;
        }

        if (position == "^") {
            Application::File::insert(filename, item, Application::POSITION_BEGIN);
            break;
        }

        long line = std::stol(position, nullptr, 10);

        if (std::to_string(line) != position) {
            continue;
        }

        if (line < 0) {
            line = 0;
        }

        Application::File::insert(filename, item, line);
        break;
    }
}

void
Iterator::_load()
{
    cout << "Введите название файла: > ";
    cin.ignore();
    getline(cin, this->filename);
}


void
Iterator::_modify()
{
    int place = 0;
    cout << "Введите номер элемента для модификации > ";
    cin >> place;

    cout << "Введите элемент для модификации" << endl;
    Man item = Application::readMan();

    Application::File::replace(filename, place, item);
}

void
Iterator::_printUsage()
{
    cout
        << endl
        << "Введите требуемую операцию: " << endl
        << Application::OPERATION_FILENAME << " - задать имя файла" << endl
        << Application::OPERATION_SHOWALL << " - показать все записи" << endl
        << Application::OPERATION_SEARCH << " - поиск записей в файле" << endl
        << Application::OPERATION_INSERT << " - добавление записи в файл" << endl
        << Application::OPERATION_MODIFY << " - изменение существующей записи" << endl
        << Application::OPERATION_CREATE << " - создание файла" << endl
        << Application::OPERATION_HALT << " - выход" << endl
        << "> ";
}

void
Iterator::_create()
{
    Application::File::create(filename);
}



void
Iterator::_search()
{
    Man query;
    string buffer;
    int mode = 0;

    cin.ignore();

    cout << " фамилия > ";
    getline(cin, buffer, '\n');

    if (buffer.length()) {
        strcpy(query.surname, buffer.c_str());
        mode |= MODE_SURNAME;
    }

    cin.sync();
    cout << " номер > ";
    getline(cin, buffer, '\n');

    if (buffer.length()) {
        query.number = atoi(buffer.c_str());
        mode |= MODE_NUMBER;
    }

    cin.sync();
    cout << " очки > ";
    getline(cin, buffer, '\n');

    if (buffer.length()) {
        query.points = atoi(buffer.c_str());
        mode |= MODE_POINTS;
    }

    cin.sync();

    Application::File::searchByQuery(filename, query, mode);
}

void
Iterator::_showall()
{
    Man *item = new Man();
    Application::File::searchByQuery(filename, *item, 0);
}

} //namespace Application
#endif

