#pragma once
#include <string>
#include <algorithm>

namespace HexSummator
{
    std::string add(const std::string c_first, const std::string c_second);
    bool validate(const std::string value);
    bool validateDec(const std::string value);
    long long hexdec(const std::string value);
    std::string dechex(long long value);
}

