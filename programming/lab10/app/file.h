#include "constants.h"
#include "man.h"
#include <cstdio>
#include <string.h>
#include <iostream>
#include <fstream>
#include <fstream>

namespace Application {
namespace File {

const int MODE_SURNAME = 1;
const int MODE_NUMBER = 2;
const int MODE_POINTS = 4;

/**
 * Производит поиск по файлу с заданными параметрами
 * @param filename  имя файла
 * @param query     запрос для поиска
 * @param mode      режим поиска
 */
bool
searchByQuery(std::string filename, Man query, int mode)
{
    std::fstream file;
    Man item;
    bool match;
    int offset = 0;
    file.open(filename.c_str(), std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл на чтение " << filename << std::endl;

        return false;
    }

    while (file.good() && file.read((char*) &item, sizeof(Man))) {
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
            std::cout << item.format(offset);
        }

        offset++;
    }

    file.close();

    return true;
}

/**
 * Создает файл и наполняет его содержимым
 *
 * @param filename
 * @return bool
 */
bool
create(std::string filename)
{
    std::ofstream output;
    output.open(filename.c_str(), std::ios::binary);

    if (!output.is_open()) {
        std::cerr << "Не удалось открыть файл на запись " << filename << std::endl;
        return false;
    }

    int count;
    std::cout << "Введите количество вводимых спортсменов: > ";
    std::cin >> count;

    Man item;

    for (int i = 0; i < count; i++) {
        item = Application::readMan();

        output.write((char*) &item, sizeof(Man));
    }

    output.close();

    return true;
}

/**
 * Заменяет в файле с позиции position данные на item
 * @param filename имя файла
 * @param position позиция в файле
 * @param item     новый элемент
 */
bool
replace(std::string filename, int position, Man item)
{
    std::fstream file;
    file.open(filename.c_str(), std::ios::binary | std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл на чтение" << filename << std::endl;

        return false;
    }
    std::cout << item.points << ":" << item.number << std::endl;

    file.seekg(position * sizeof(Man));

    if (!file.eof()) {
        file.write((char*) &item, sizeof(Man));
    }

    file.close();

    return true;
}

/**
 * Вставляет элемент на определенное место
 *
 * @param filename где
 * @param item     что
 * @param position куда
 */
void
insert(std::string filename, Man item, int position)
{
    if (position == Application::POSITION_END) {
        std::fstream file;
        file.open(filename.c_str(), std::ios::binary | std::ios::out | std::ios::app);

        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл на запись " << filename << std::endl;
            return;
        }

        file.write((char*) &item, sizeof(Man));
        file.close();

        return;
    }

    std::string tempFilename = filename;
    tempFilename.append(".tmp");

    std::fstream input, output;
    input.open(filename.c_str(), std::ios::binary | std::ios::in);
    output.open(tempFilename.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);

    bool written = false;

    if (position == Application::POSITION_BEGIN) {
        output.write((char*) &item, sizeof(Man));
        written = true;
    }

    int pointer = 0;
    Man currentItem;

    while (input.good() && input.read((char*) &currentItem, sizeof(Man))) {
        output.write((char*) &currentItem, sizeof(Man));

        if (pointer == position && !written) {
            output.write((char*) &item, sizeof(Man));
            written = true;
        }

        pointer++;
    }

    if (!written) {
        output.write((char*) &item, sizeof(Man));
    }

    input.close();
    output.close();

    remove(filename.c_str());
    rename(tempFilename.c_str(), filename.c_str());

    return;
}

}
}
