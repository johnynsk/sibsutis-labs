#include "hexsummator.hpp"
#include <iostream>
#include <string>
int main(int argc, char ** argv)
{
    if (argc < 2) {
        return (1);
    }

    std::cout << HexSummator::add(std::string(argv[1]), std::string(argv[2]));

    return 0;
}
