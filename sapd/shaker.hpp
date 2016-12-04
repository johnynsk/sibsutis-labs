#ifndef SHAKER_H
#define SHAKER_H
#include "report.hpp"
#include <vector>
#include <map>
#include <string>

namespace Sapd
{
    namespace Shaker
    {
        struct report
        sort(std::vector<int> array)
        {
            struct report result;
            int length = array.size();
            int left = 0;
            int right = length - 1;
            int compares = 0;
            int swaps = 0;
            int edge = -1;

            while (left < right) {
                for (int i = right - 1; i > left; i--) {
                    compares++;

                    if (array[i] >= array[i+1]) {
                        continue;
                    }

                    std::swap(array[i], array[i+1]);
                    edge = i;
                    swaps++;
                }

                left = edge;

                for (int i = left; i < right; i++) {
                    compares++;

                    if (array[i] <= array[i+1]) {
                        continue;
                    }

                    std::swap(array[i], array[i+1]);
                    edge = i;
                    swaps++;
                }

                right = edge;

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

            result["avg"].swaps = length * length;
            result["avg"].compares = length * length;
            result["min"].compares = length - 1;
            result["max"].compares = (length * length - length) / 2;

            return result;
        }
    }
}

#endif
