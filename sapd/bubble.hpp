#ifndef BUBBLE_H
#define BUBBLE_H
#include "report.hpp"
#include <vector>

namespace Sapd
{
    namespace Bubble
    {
        struct report
        sort(std::vector<int> array)
        {
            int length = array.size();
            int item;
            struct report result;

            int swaps = 0;
            int compares = 0;

            for (int i = 0; i < length - 2; i++) {
                for (int j = length - 1; j > i + 1; j--) {
                    if (array[j] < array[j-1]) {
                        item = array[j];
                        array[j] = array[j-1];
                        array[j-1] = item;
                        swaps++;
                    }

                    compares++;
                }
            }

            result.compares = compares;
            result.swaps = swaps;
            result.result = array;

            return result;
        }

        std::map<std::string, struct report>
        theorethicalReport(std::vector<int> array)
        {
            std::size_t length = array.size();
            std::map<std::string, struct report> result;

            result["min"].swaps = 0;
            result["min"].compares = length;
            result["max"].swaps = 3 * (length * length - length) / 2;
            result["min"].compares = (length * length - length) / 2;

            return result;
        }
    } //namespace Bubble
} //namespace Sapd

#endif
