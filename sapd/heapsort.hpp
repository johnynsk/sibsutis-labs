#ifndef SAPD_HEAPSORT_H
#define SAPD_HEAPSORT_H
#include "report.hpp"
#include <vector>
#include <math.h>

namespace Sapd
{
    namespace HeapSort
    {
        struct report
        sort(std::vector<int> array);

        struct report
        heap(std::vector<int> array, const std::size_t begin, const std::size_t end);

        struct report
        theorethicalReport(std::vector<int> array);
    }
}

namespace Sapd
{
    namespace HeapSort
    {
        struct report
        sort(std::vector<int> array)
        {
            struct report result;
            result.compares = 0;
            result.swaps = 0;
            result.result = array;

            std::size_t left = array.size() / 2;
            std::size_t right = array.size() - 1;

            while (left != 0) {
                struct report report = heap(array, left, right);
                result.compares += report.compares;
                result.swaps += report.swaps;

                left--;
            }

            while (right != 0) {
                std::swap(array[0], array[right]);
                result.swaps++; // += 3;
                right--;

                struct report report = heap(array, 0, right);
                result.compares += report.compares;
                result.swaps += report.swaps;
            }

            return result;
        }

        struct report
        heap(std::vector<int> array, const std::size_t begin, const std::size_t end)
        {
            struct report result;
            result.compares = 0;
            result.swaps = 0;

            int item = array[begin];
            std::size_t left = begin;
            std::size_t right = end;

            while (true) {
                right = 2 * left;

                if (right > end) {
                    break;
                }

                result.compares++;
                if ((right < end) && (array[right + 1] <= array[right])) {
                    right++;
                }

                result.compares++;
                if (item <= array[right]) {
                    break;
                }

                result.swaps++;
                array[left] = array[right];
                left = right;
            }

            array[left] = item;
            result.swaps++;

            return result;
        }

        struct report
        theorethicalReport(std::vector<int> array)
        {
            struct report result;
            std::size_t length = array.size();

            result.swaps = length * log(length) + 6.5 * length - 4;
            result.compares = 2 * length * log(length) + length + 2;

            return result;
        }
    }
}

#endif

