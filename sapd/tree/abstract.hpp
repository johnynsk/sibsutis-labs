#pragma once
#include <vector>

namespace Tree
{
class Abstract
{
    protected:
        int width;
        std::vector<Abstract> leafs;

    public: Abstract(int width)
    {
        this->width = width;
    }

    public: Abstract()
    {
        this->width = 2;
    }
};
} // namespace Tree
