/**
 * Лабораторная работа №10
 * Обработка бинарных файлов
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <cmath>
#include "app.h"

#define POSITION_BEGIN -2
#define POSITION_END -1

#define MODE_SURNAME 1
#define MODE_NUMBER 2
#define MODE_POINTS 4

OPERATION_HALT 0
OPERATION_FILENAME 1
OPERATION_SEARCH 2
OPERATION_INSERT 3
OPERATION_MODIFY 4
OPERATION_CREATE 5

using namespace std;

struct sportsman {
    char surname[64];
    int number;
    int points;
};

struct sportsman readItem()
{
    struct sportsman item;
    string surname;

    cin.ignore();

    cout << " фамилия: > ";
    getline(cin, surname);

    strcpy(item.surname, surname.c_str());

    cout << " номер: > ";
    cin >> item.number;

    cout << " очков: > ";
    cin >> item.points;

    cin.ignore();

    return item;
}

bool create(string filename)
{
    ofstream output;
    output.open(filename.c_str(), ios::binary);

    if (!output.is_open()) {
        cout << "Не удалось открыть файл на запись " << filename << endl;
        return false;
    }

    int count;
    cout << "Введите количество вводимых спортсменов: > ";
    cin >> count;

    struct sportsman item;
    string surname;

    for (int i = 0; i < count; i++) {
        item = readItem();

        output.write((char*) &item, sizeof(struct sportsman));
    }

    output.close();

    return true;
}

bool insert(string filename, struct sportsman item, int position)
{
    if (position == POSITION_END) {
        fstream file;
        file.open(filename.c_str(), ios::binary | ios::out | ios::app);

        if (!file.is_open()) {
            cout << "Не удалось открыть файл на запись " << filename << endl;
            return false;
        }

        file.write((char*) &item, sizeof(struct sportsman));
        file.close();

        return true;
    }

    string tempFilename = filename;
    tempFilename.append(".tmp");

    fstream input, output;
    input.open(filename.c_str(), ios::binary | ios::in);
    output.open(tempFilename.c_str(), ios::binary | ios::out | ios::trunc);

    bool written = false;

    if (position == POSITION_BEGIN) {
        output.write((char*) &item, sizeof(struct sportsman));
        written = true;
    }

    int pointer = 0;
    struct sportsman currentItem;

    while (input.good() && input.read((char*) &currentItem, sizeof(struct sportsman))) {
        output.write((char*) &currentItem, sizeof(struct sportsman));

        if (pointer == position && !written) {
            output.write((char*) &item, sizeof(struct sportsman));
            written = true;
        }

        pointer++;
    }

    if (!written) {
        output.write((char*) &item, sizeof(struct sportsman));
    }

    input.close();
    output.close();

    remove(filename.c_str());
    rename(tempFilename.c_str(), filename.c_str());

    return true;
}

void outputItem(struct sportsman item, int offset)
{
    cout << "#" << offset << " фамилия: " << item.surname << "; номер: " << item.number << "; очков: " << item.points << endl;
}



bool searchByQuery(string filename, struct sportsman query, int mode)
{
    fstream file;
    struct sportsman item;
    bool match;
    int offset = 0;
    file.open(filename.c_str(), ios::binary | ios::in);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл на чтение" << filename << endl;

        return false;
    }

    while (file.good() && file.read((char*) &item, sizeof(struct sportsman))) {
        match = true;

        if (mode & MODE_SURNAME && strcmp(item.surname, query.surname) != 0) {
            match = false;
        }

        if (mode & MODE_NUMBER && item.number != query.number) {
            match = false;
        }

        if (mode & MODE_POINTS && item.points != query.points) {
            match = false;
        }

        if (match) {
            outputItem(item, offset);
        }

        offset++;
    }

    file.close();

    return true;
}


bool search(string filename)
{
    struct sportsman query;
    string buffer;
    int mode = 0;

    cin.ignore();

    cout << " фамилия > ";
    getline(cin, buffer, '\n');

    if (buffer.length()) {
        strcpy(query.surname, buffer.c_str());
        mode = mode | MODE_SURNAME;
    }

    cin.sync();
    cout << " номер > ";
    getline(cin, buffer, '\n');

    if (buffer.length()) {
        query.number = atoi(buffer.c_str());
        mode = mode | MODE_NUMBER;
    }

    cin.sync();
    cout << " очки > ";
    getline(cin, buffer, '\n');

    if (buffer.length()) {
        query.points = atoi(buffer.c_str());
        mode = mode | MODE_POINTS;
    }

    cin.sync();

    return searchByQuery(filename, query, mode);
}


bool modifyItem(string filename, struct sportsman modifiedItem, int position)
{
    fstream file;
    file.open(filename.c_str(), ios::binary | ios::in | ios::app);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл на чтение" << filename << endl;

        return false;
    }

    file.seekp(position * sizeof(struct sportsman));
    file.seekg(0, file.beg);
    file << (char*) &modifiedItem;
    file.close();

    return true;
}


bool modify(string filename)
{
    int place = 0;
    cout << "Введите номер элемента для модификации > ";
    cin >> place;

    cout << "Введите элемент для модификации" << endl;
    struct sportsman item = readItem();

    return modifyItem(filename, item, place);
}

int main()
{
    App *application = new App();
    application->run();
}

