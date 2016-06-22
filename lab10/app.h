#ifndef PROJECT_APP
#define PROJECT_APP
#include <iostream>
#include <string>
#include "app/man.h"

using namespace std;

class App
{
    static const int
        POSITION_BEGIN = -2,
        POSITION_END = -1,

        MODE_SURNAME = 1,
        MODE_NUMBER = 2,
        MODE_POINTS = 4,

        OPERATION_HALT = 0,
        OPERATION_FILENAME = 1,
        OPERATION_SEARCH = 2,
        OPERATION_INSERT = 3,
        OPERATION_MODIFY = 4,
        OPERATION_CREATE = 5;

    public:
        App();
        void run();

    private:
        string filename;
        void _printUsage();
};

App::App()
{
    std::cout << "test output App" <<std::endl;
}

void App::run()
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
                cin.ignore();
                getline(cin, this->filename);

                break;

            case OPERATION_SEARCH:
                search(filename);

                break;

            case OPERATION_INSERT:
                break;

            case OPERATION_MODIFY:
                modify(filename);

                break;

            case OPERATION_CREATE:
                create(filename);

                break;
        }
    }
}

void App::_printUsage()
{
    cout << "Введите требуемую операцию: " << endl;
    cout << "1 - задать имя файла" << endl;
    cout << "2 - поиск записей в файле" << endl;
    cout << "3 - добавление записи в файл" << endl;
    cout << "4 - изменение существующей записи" << endl;
    cout << "5 - создание файла" << endl;
    cout << "0 - выход\n> " << endl;
}

#endif
