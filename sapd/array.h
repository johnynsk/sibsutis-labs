#ifndef ARRAY_H
#define ARRAY_H
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>

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
