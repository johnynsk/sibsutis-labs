#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include "../array.h"
#include "../report.hpp"
#include "../shaker.hpp"
#include "../straight.hpp"
#include "../bubble.hpp"

using namespace Sapd;

std::string
output(std::vector<int> array)
{
    std::stringstream result;
    result << "Array (" << std::to_string(array.size()) <<"): " << std::endl << "[";

    for (size_t i = 0; i < array.size(); i++) {
        if (i != 0) {
            result << ", ";
        }

        result << std::to_string(array[i]).c_str();
    }

    result << "]" << std::endl;

    return result.str();
}

void
reportSorted(std::vector<int> array)
{
    std::vector<int> arraySorted(array);
    std::sort(arraySorted.begin(), arraySorted.begin() + arraySorted.size());

    struct report straight = Straight::sort(std::vector<int>(array));
    struct report bubble = Bubble::sort(std::vector<int>(array));
    struct report shaker = Shaker::sort(std::vector<int>(array));

    struct report straightSorted = Straight::sort(std::vector<int>(arraySorted));
    struct report bubbleSorted = Bubble::sort(std::vector<int>(arraySorted));
    struct report shakerSorted = Shaker::sort(std::vector<int>(arraySorted));

    std::stringstream result;
    result << std::endl << "## Отчет для N=" << std::to_string(array.size()) << std::endl << std::endl;
    result
        << "### Исходный массив:" << std::endl << std::endl
        << "Сгенерирован массив:"  << std::endl << output(array) << std::endl;

    result << "### Таблица" << std::endl << std::endl;

    result
        << "| метод | M для упорядоченного массива | C для упорядоченного массива | M для случайного массива "
        << "| C для случайного массива |" << std::endl
        << "|---|---|---|---|---|" << std::endl;

    result
        << "| Прямой выбор | "
        << std::to_string(straightSorted.swaps) << " | " << std::to_string(straightSorted.compares) << " | "
        << std::to_string(straight.swaps) << " | " << std::to_string(straight.compares) << " | " << std::endl;

    result
        << "| Пузырьковая | "
        << std::to_string(bubbleSorted.swaps) << " | " << std::to_string(bubbleSorted.compares) << " | "
        << std::to_string(bubble.swaps) << " | " << std::to_string(bubble.compares) << " | " << std::endl;

    result
        << "| Шейкерная | "
        << std::to_string(shakerSorted.swaps) << " | " << std::to_string(shakerSorted.compares) << " | "
        << std::to_string(shaker.swaps) << " | " << std::to_string(shaker.compares) << " | " << std::endl;

    std::cout << result.str();
}

int
main()
{
    int length;
    std::cout << "Введите количество элементов массивов: > ";
    std::cin >> length;

    std::cout << std::endl;

    std::vector<int> array = fillRandom(length);

    reportSorted(array);

    std::cout << std::endl;

    return 0;
}

