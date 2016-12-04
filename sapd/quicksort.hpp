#ifndef SAPD_QUICKSORT_H
#define SAPD_QUICKSORT_H
#include <vector>
#include <cmath>
#include <iostream> //remove todo
#include "report.hpp"

namespace Sapd
{
    namespace QuickSort
    {
        struct report
        sort(std::vector<int> array);

        struct report
        sort(std::vector<int> array, long from, long to);
    }
}

namespace Sapd
{
    namespace QuickSort
    {
        struct report
        sort(std::vector<int> array)
        {
            return sort(array, 0, array.size() - 1);
        }

        struct report
        sort(std::vector<int> array, long left, long right)
        {
            struct report result;
            result.compares = 0;
            result.swaps = 0;
            result.result = array;

            if (left > right) {
                return result;
            }

            int item = array[left];
            long i = left;
            long j = right;

            while (i < j) {
                result.compares++;
                while (array[i] < item) {
                    i++;
                    result.compares++;
                }

                while (array[j] > item) {
                    j--;
                    result.compares++;
                }

                if (i <= j) {
                    std::swap(array[i], array[j]);
                    result.swaps++;
                    i++;
                    j--;
                }
            }

            if (left < j) {
                struct report report = sort(array, left, j);
                result.compares += report.compares;
                result.swaps += report.swaps;
            }

            result.compares++;

            if (i < right) {
                struct report report = sort(array, i, right);
                result.compares += report.compares;
                result.swaps += report.swaps;
            }

            result.compares++;
            result.result = array;

            return result;
        }

        struct report
        theorethicalReport(std::vector<int> array)
        {
            std::size_t length = array.size();
            struct report result;

            result.swaps = 3 * (length - 1);
            result.compares = (std::pow(length, 2) + length * 5 + 4) / 2;

            return result;
        }
    }
}

#endif

