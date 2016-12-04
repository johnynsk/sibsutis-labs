#ifndef ARRAY_H
#define ARRAY_H
#include <cstdlib>
#include <vector>

namespace Sapd
{
    std::vector<int>
    fillRandom(int length)
    {
        std::vector<int> result(length);

        for (int i = 0; i < length; i++)
        {
            result[i] = std::rand() % 200 - 100;
        }

        return result;
    }
} //namespace Sapd
#endif
