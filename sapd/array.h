#ifndef ARRAY_H
#define ARRAY_H
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>

#include "report.hpp"

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

    std::vector<int>
    fillIncrease(int length)
    {
        std::vector<int> result(length);
        int initial = -100;
        for (int i = 0; i < length; i++) {
            result[i] = std::rand() % 200 + initial;
            initial = result[i];
        }

        return result;
    }

    std::vector<int>
    fillDecrease(int length)
    {
        std::vector<int> result(length);
        int initial = -10000;
        for (int i = 0; i < length; i++) {
            result[i] = initial - std::rand() % 200;
            initial = result[i];
        }

        return result;
    }

    struct checksum
    checksum(std::vector<int> vector)
    {
        struct checksum result;
        result.sum = 0;
        result.series = 0;

        if (vector.size() == 0) {
            return result;
        }

        int previous = vector[0];

        for (std::size_t i = 0; i < vector.size(); i++) {
            result.sum += vector[i];

            if (previous > vector[i]) {
                result.series++;
            }
        }

        return result;
    }

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

} //namespace Sapd
#endif
