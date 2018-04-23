#include "hexsummator.hpp"

std::string clean_leading_zeros(const std::string in)
{
    bool subzero = false;
    std::string str(in);

    if (str[0] == '-') {
        subzero = true;
        str = str.substr(1);
    }

    while(str[0] == '0') {
        str = str.substr(1);
    }

    return subzero ? std::string("-").append(str) : str;
}
namespace HexSummator {
std::string add(const std::string c_first, const std::string c_second)
{
    std::string first(clean_leading_zeros(c_first)), second(clean_leading_zeros(c_second)), result;
    bool zfirst = false, zsecond = false, zthird;

    if (first[0] == '-') {
        zfirst = true;
        first = first.substr(1);
    }

    if (second[0] == '-') {
        zsecond = true;
        second = second.substr(1);
    }

    std::reverse(first.begin(), first.end());
    std::reverse(second.begin(), second.end());

    size_t smax = std::max(first.size(), second.size());
    char transition = 0;

    for (size_t i = 0; i < smax; i++) {
        char A = i < first.size()  ? first[i]  : '0';
        char B = i < second.size() ? second[i] : '0';

        A -= A >= '0' && A <= '9' ? '0' : 'A' - 10;
        B -= B >= '0' && B <= '9' ? '0' : 'A' - 10;

        char R = transition + (zfirst  ? -A : A) + (zsecond ? -B : B);
        transition = 0;
        zthird = false;

        if (R < 0) {
            zthird = true;
            R = -R;
        }

        if (R > 15) {
            R = R % 16;
            transition = zthird ? -1 : 1;
        }

        result.push_back((char)(R <= 9 ? R + '0' : R + 'A' - 10));
    }

    std::reverse(result.begin(), result.end());
    result = clean_leading_zeros(result);
    result = result.size() ? result : std::string("0");

    return zthird ? std::string("-").append(result) : result;
}

bool validate(const std::string value)
{
    for (size_t i = 0; i < value.size(); i++) {
        if (value[i] >= '0' && value[i] <= '9') {
            continue;
        } else if (value[i] >= 'A' && value[i] <= 'F') {
            continue;
        } if (i == 0 && value[i] == '-') {
            continue;
        }

        return false;
    }

    return true;
}
} //namespace HexSummator
