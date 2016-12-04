#ifndef STRAIGHT_HPP
#define STRAIGHT_HPP
#include "report.hpp"
#include <vector>

namespace Sapd
{
    namespace Straight
    {
        struct report
        sort(std::vector<int> array)
        {
            struct report result;
            int swaps = 0;
            int compares = 0;
            int length = array.size();
            int min = 0;

            for (int i = 0; i < length - 1; i++)
            {
                min = i;

                for (int j = i + 1; j < length; j++)
                {
                    compares++;
                    if (array[j] < array[min]) {
                        min = j;
                    }
                }

                std::swap(array[i], array[min]);
                swaps++;
            }

            result.compares = compares;
            result.swaps = swaps;
            result.result = array;

            return result;
        }

        struct report
        theorethicalReport(std::vector<int> array)
        {
            std::size_t length = array.size();
            struct report result;

            result.swaps = 3 * (length - 1);
            result.compares = (length * length - length) / 2;

            return result;
        }
    }
}

#endif
