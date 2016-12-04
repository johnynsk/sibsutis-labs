#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>

#include "../array.h"
#include "../report.hpp"
#include "../shell.hpp"
#include "../quicksort.hpp"
#include "../heapsort.hpp"

using namespace Sapd;

std::string
reportShell(std::vector<int> arrayRandomed, std::vector<int> arraySorted)
{
    struct report randomed = Shell::sort(arrayRandomed);
    struct report sorted = Shell::sort(arraySorted);
    std::map<std::string, struct report> theoretical = Shell::theorethicalReport(arrayRandomed);

    std::stringstream result;

    result
        << "| Шелла | "
        << std::to_string(sorted.swaps) << " | " << std::to_string(sorted.compares) << " | "
        << std::to_string(randomed.swaps) << " | " << std::to_string(randomed.compares) << " | "
        << std::to_string(theoretical["min"].swaps) << " | " << std::to_string(theoretical["min"].compares) << " | "
        << std::to_string(theoretical["max"].swaps) << " | " << std::to_string(theoretical["max"].compares) << " | "
        << std::endl;

    return result.str();
}

std::string
reportHeapSort(std::vector<int> arrayRandomed, std::vector<int> arraySorted)
{
    struct report randomed = HeapSort::sort(arrayRandomed);
    struct report sorted = HeapSort::sort(arraySorted);
    struct report theoretical = HeapSort::theorethicalReport(arrayRandomed);

    std::stringstream result;

    result
        << "| Пирамидальная | "
        << std::to_string(sorted.swaps) << " | " << std::to_string(sorted.compares) << " | "
        << std::to_string(randomed.swaps) << " | " << std::to_string(randomed.compares) << " | "
        << std::to_string(theoretical.swaps) << " | " << std::to_string(theoretical.compares) << " | - | - |"
        << std::endl;

    return result.str();
}

std::string
reportQuickSort(std::vector<int> arrayRandomed, std::vector<int> arraySorted)
{
    struct report randomed = QuickSort::sort(arrayRandomed);
    struct report sorted = QuickSort::sort(arraySorted);
    struct report theoretical = QuickSort::theorethicalReport(arrayRandomed);

    std::stringstream result;

    result
        << "| Быстрая (Хоара) | "
        << std::to_string(sorted.swaps) << " | " << std::to_string(sorted.compares) << " | "
        << std::to_string(randomed.swaps) << " | " << std::to_string(randomed.compares) << " | "
        << std::to_string(theoretical.swaps) << " | " << std::to_string(theoretical.compares) << " | - | - |"
        << std::endl;

    return result.str();
}

std::string
buildReport(std::vector<int> arrayRandomed)
{
    std::vector<int> arraySorted(arrayRandomed);
    std::sort(arraySorted.begin(), arraySorted.begin() + arraySorted.size());

    std::stringstream result;
    result << std::endl << "## Отчет для N=" << std::to_string(arrayRandomed.size()) << std::endl << std::endl;
    result
        << "### Исходный массив:" << std::endl << std::endl
        << "Сгенерирован массив:"  << std::endl << output(arrayRandomed) << std::endl;

    result << "### Таблица" << std::endl << std::endl;

    result
        << "| метод | M упорядоченный | C упорядоченый | M случайный | C случайный |"
        << " M теоретическое | C теоретическое | M теоретическое (max) | C теоретическое (max) |" << std::endl
        << "| C для случайного массива | M теоретическое" << std::endl
        << "|---|---|---|---|---|---|---|---|---|" << std::endl;

    result << reportShell(std::vector<int>(arrayRandomed), std::vector<int>(arraySorted));
    result << reportHeapSort(std::vector<int>(arrayRandomed), std::vector<int>(arraySorted));
    result << reportQuickSort(std::vector<int>(arrayRandomed), std::vector<int>(arraySorted));


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

