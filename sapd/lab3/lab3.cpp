#include <map>
#include <iostream>

#include "../list.hpp"
#include "../report.hpp"
#include "../array.h"

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
calcChecksum(struct bundle *bundle)
{
    std::map<std::string, struct checksum> result;

    result["stack"] = checksum(bundle->stack);
    result["queue"] = checksum(bundle->queue);
    result["vector"] = checksum(bundle->vector);

    return result;
}

std::string
printChecksum(struct bundle *bundle)
{
    std::stringstream result;
    std::map<std::string, struct checksum> sums = calcChecksum(bundle);

    result
        << "### Контрольные суммы" << std::endl << std::endl
        << "| struct | checksum | serie |" << std::endl
        << "|---|---|---|" << std::endl
        << "| Очередь | " << std::to_string(sums["queue"].sum) << " | "
        << std::to_string(sums["queue"].series) << " | " << std::endl
        << "| Стек | " << std::to_string(sums["stack"].sum) << " | "
        << std::to_string(sums["stack"].series) << " | " << std::endl
        << "| Вектор | " << std::to_string(sums["vector"].sum) << " | "
        << std::to_string(sums["Вектор"].series) << " | " << std::endl
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
            result->stack = Stack::fill(result->stack, result->vector);
            result->queue = Queue::fill(result->queue, result->vector);

            return result;
        }

        if (command == FILL_INCREASE) {
            result->vector = fillIncrease(length);
            result->stack = Queue::fill(result->stack, result->vector);
            result->queue = Queue::fill(result->queue, result->vector);

            return result;
        }

        if (command == FILL_DECREASE) {
            result->vector = fillDecrease(length);
            result->stack = Stack::fill(result->stack, result->vector);
            result->queue = Queue::fill(result->queue, result->vector);

            return result;
        }
    }
}

int
main()
{
    struct bundle *bundle = new struct bundle;
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

            bundle = fill(length);
            continue;
        }

        if (command == VIEW) {
            std::cout
                << "vector: " << std::endl << output(bundle->vector) << std::endl
                << "queue" << std::endl << render(bundle->queue) << std::endl
                << "stack" << std::endl << render(bundle->stack) << std::endl;

            continue;
        }

        if (command == CHECKSUM) {
            std::cout << printChecksum(bundle);
            continue;
        }

        std::cerr << "wrong command " << std::to_string(command) << std::endl;
    }

    return 0;
}

