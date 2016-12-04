#include <map>
#include "../list.hpp"
#include <iostream>

#include "../report.hpp"
#include "../array.h"

#include "stdio.h"
//#include <stdafx.h>
#include <stdlib.h>
#include <time.h>
#include <locale>

const int EXIT = 0;
const int FILL_DATA = 1;
const int VIEW = 2;
const int CHECKSUM = 3;

const int FILL_RANDOM = 0;
const int FILL_INCREASE = 1;
const int FILL_DECREASE = -1;

using namespace Sapd;

struct bundle {
    struct list *queue;
    struct list *stack;
    std::vector<int> vector;
};

std::map<std::string, struct checksum>
calcChecksum(struct bundle bundle)
{
    std::map<std::string, struct checksum> result;

    result["stack"] = checksum(bundle->stack);
    result["queue"] = checksum(bundle->queue);
    result["vector"] = checksum(bundle->vector);

    return result;
}

std::string
printChecksum(struct bundle bundle)
{
    std::stringstream result;
    std::map<std::string, struct checksum> sums = calcChecksum(bundle);

    result
        << "### Контрольные суммы" << std::endl << std::endl
        << "| struct | checksum | serie |" << std::endl
        << "|---|---|---|" << std::endl
        << "| Очередь | " << sums["queue"].sum << " | " << sums["queue"].serie << " | " << std::endl
        << "| Стек | " << sums["stack"].sum << " | " << sums["stack"].serie << " | " << std::endl
        << "| Вектор | " << sums["vector"].sum << " | " << sums["Вектор"].serie << " | " << std::endl
        << std::endl;

    return result.str();
}

struct bundle
*fill(int length)
{
    int command;
    struct bundle *result = new struct bundle;
    result->stack = create();
    result->queue = create();

    while (true)
    {
        std::cout
            << std::endl << "Режим ввода данных: "
            << std::endl << FILL_DECREASE << ". Ввод данных по убыванию"
            << std::endl << FILL_RANDOM << ". Ввод случайных данных"
            << std::endl << FILL_INCREASE << ". Ввод данных по возрастанию"
            << std::endl << "Введите команду > ";

        std::cin >> command;

        if (command == FILL_RANDOM) {
            result->vector = fillRandom(length);
            result->stack = fill(result->stack, result->vector);
            result->queue = fill(result->queue, result->vector);

            return result;
        }

        if (command == FILL_INCREASE) {
            result->vector = fillIncrease(length);
            result->stack = fill(result->stack, result->vector);
            result->queue = fill(result->queue, result->vector);

            return result;
        }

        if (command == FILL_DECREASE) {
            result->vector = fillDecrease(length);
            result->stack = fill(result->stack, result->vector);
            result->queue = fill(result->queue, result->vector);

            return result;
        }
    }
}

int
main()
{
    struct bundle *bundle;
    bundle->queue = create();
    bundle->stack = create();
    int command;
    int length;

    while (true) {
        std::cout
            << std::endl << "Ввод команды" << std::endl
            << FILL_DATA << ". Генерация данных" << std::endl
            << VIEW << ". Просмотр данных" << std::endl
            << CHECKSUM << ". Подсчет контрольных сумм" << std::endl
            << EXIT << ". Выход" << std::endl
            << "Введите команду > ";
        std::cin >> command;

        if (command == EXIT) {
            break;
        }

        if (command == FILL_DATA) {
            std::cout << "Введите длину данных: > ";
            std::cin >> length;

            fill(length);
            continue;
        }

        if (command == VIEW) {
            continue;
        }

        if (command == CHECKSUM) {
            calcChecksum();
            continue;
        }

        std::cerr << "wrong command " << std::to_string(command) << std::endl;
    }

    return 0;
}

