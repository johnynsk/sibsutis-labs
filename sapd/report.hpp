#ifndef REPORT_H
#define REPORT_H
#include <vector>

namespace Sapd
{
    struct report
    {
        int compares;
        int swaps;
        std::vector<int> result;
    };

    struct checksum
    {
        int sum;
        int series;
    };
}

#endif
