#ifndef SHELL_H
#define SHELL_H
#include <vector>
#include <map>
#include <math.h>

#include "report.hpp"

namespace Sapd
{
    namespace Shell
    {
        struct report
        sort(std::vector<int> array)
        {
            struct report result;
            int length = array.size();
            int left = 0;
            int compares = 0;
            int swaps = 0;
            int item;

            for (int step = log2(length); step > 0; step--) {
                for (int i = step + 1; i < length; i++) {
                    item = array[i];
                    left = i - step;

                    while (left > 0 && ++compares &&item < array[left]) {
                        array[left + step] = array[left];
                        left -= step;

                        swaps++;
                    }


                    array[left + step] = item;
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

            result["min"].compares = length - 1;
            result["min"].swaps = 2 * (length - 1);

            result["max"].compares = (pow(length, 2) - length) / 2;
            result["max"].swaps = (pow(length, 2) - length) / 2 + 2 * length - 2;

            return result;
        }
    }
}

#endif
