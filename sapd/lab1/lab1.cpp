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
buildReportStraight(std::vector<int> arrayRandomed, std::vector<int> arraySorted)
{
    std::stringstream result;

    struct report randomed = Straight::sort(std::vector<int>(arrayRandomed));
    struct report sorted = Straight::sort(std::vector<int>(arraySorted));
    struct report theorethical = Straight::theorethicalReport(arrayRandomed);

    result
        << "| Прямой выбор | "
        << std::to_string(sorted.swaps) << " | " << std::to_string(sorted.compares) << " | "
        << std::to_string(randomed.swaps) << " | " << std::to_string(randomed.compares) << " | " << std::endl;

    return result.str();
}

std::string
buildReportShaker(std::vector<int> arrayRandomed, std::vector<int> arraySorted)
{
    std::stringstream result;

    struct report randomed = Shaker::sort(std::vector<int>(arrayRandomed));
    struct report sorted = Shaker::sort(std::vector<int>(arraySorted));
    std::map<std::string, struct report> theorethical = Shaker::theorethicalReport(arrayRandomed);

    result
        << "| Шейкерная | "
        << std::to_string(sorted.swaps) << " | " << std::to_string(sorted.compares) << " | "
        << std::to_string(randomed.swaps) << " | " << std::to_string(randomed.compares) << " | " << std::endl;

    return result.str();
}

std::string
buildReportBubble(std::vector<int> arrayRandomed, std::vector<int> arraySorted)
{
    std::stringstream result;

    struct report randomed = Bubble::sort(std::vector<int>(arrayRandomed));
    struct report sorted = Bubble::sort(std::vector<int>(arraySorted));
    std::map<std::string, struct report> theorethical = Bubble::theorethicalReport(arrayRandomed);

    result
        << "| Пузырьковая | "
        << std::to_string(sorted.swaps) << " | " << std::to_string(sorted.compares) << " | "
        << std::to_string(randomed.swaps) << " | " << std::to_string(randomed.compares) << " | " << std::endl;

    return result.str();
}

std::string
buildReport(std::vector<int> array)
{
    std::vector<int> arraySorted(array);
    std::sort(arraySorted.begin(), arraySorted.begin() + arraySorted.size());

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

    result << buildReportStraight(std::vector<int>(array), std::vector<int>(arraySorted));
    result << buildReportBubble(std::vector<int>(array), std::vector<int>(arraySorted));
    result << buildReportShaker(std::vector<int>(array), std::vector<int>(arraySorted));

    return result.str();
}

int
main()
{
    int length;
    std::cout << "Введите количество элементов массивов: > ";
    std::cin >> length;

    std::cout << std::endl;

    std::vector<int> array = fillRandom(length);

    std::cout << buildReport(array);

    std::cout << std::endl;

    return 0;
}

