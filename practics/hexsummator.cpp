#include "hexsummator.hpp"

std::string clean(const std::string in)
{
    bool subzero = false;
    std::string str(in);

    if (str[0] == '-') {
        subzero = true;
        str = str.substr(1);
    }

    while(str[0] == '0' && str.size() > 1) {
        str = str.substr(1);
    }

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] >= 'a' && str[i] <= 'f') {
            str[i] = str[i] - 'a' + 'A';
        }
    }

    return subzero ? std::string("-").append(str) : str;
}

namespace HexSummator {
std::string add(const std::string c_first, const std::string c_second)
{
    std::string first(clean(c_first)), second(clean(c_second)), result;

    if (!validate(first) || !validate(second)) {
        return "";
    }

    bool zfirst = false, zsecond = false, zthird = false;

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

    for (size_t i = 0; i <= smax; i++) {
        char A = i < first.size()  ? first[i]  : '0';
        char B = i < second.size() ? second[i] : '0';

        A -= A >= '0' && A <= '9' ? '0' : 'A' - 10;
        B -= B >= '0' && B <= '9' ? '0' : 'A' - 10;

        char R = transition + (zfirst ? -A : A) + (zsecond ? -B : B);
        transition = 0;
        if (i < first.size() -1 || i < second.size() - 1) {
            zthird = false;
        }

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
    result = clean(result);
    result = result.size() ? result : std::string("0");

    return zthird ? std::string("-").append(result) : result;
}

bool validate(const std::string value)
{
    if (value.size() > 15) {
        return false;
    }

    for (size_t i = 0; i < value.size(); i++) {
        if (value[i] >= '0' && value[i] <= '9') {
            continue;
        } else if (value[i] >= 'A' && value[i] <= 'F') {
            continue;
        } else if (value[i] >= 'a' && value[i] <= 'f') {
            continue;
        } if (i == 0 && value[i] == '-') {
            continue;
        }

        return false;
    }

    return true;
}

bool validateDec(const std::string value)
{
    if (value.size() > 19) {
        return false;
    }
    for (size_t i = 0; i < value.size(); i++) {
        if (value[i] >= '0' && value[i] <= '9') {
            continue;
        } if (i == 0 && value[i] == '-') {
            continue;
        }

        return false;
    }

    return true;
}

long long hexdec(const std::string c_value)
{
    std::string value(c_value);
    std::transform(value.begin(), value.end(), value.begin(), ::toupper);
    if (!validate(value)) {
        return 0;
    }

    long long result = 0;
    bool subzero = false;

    if (value[0] == '-') {
        value = value.substr(1);
        subzero = true;
    }

    for (std::string::iterator it = value.begin(); it != value.end(); it++) {
        result *= 16;
        result += (*it >= '0' && *it <= '9') ? *it - '0' : *it - 'A' + 10;
    }

    return subzero ? result * -1 : result;
}

std::string dechex(const long long c_value)
{
    std::string result = "";
    std::string sign = "";
    long long value = c_value;

    if (value == 0) {
        return std::string("0");
    }

    if (value < 0) {
        sign = "-";
        value = -value;
    }

    while(value) {
        int number = value % 16;
        result.push_back((char)(number < 10 ? '0' + number : number - 10 + 'A'));
        value = (int)(value / 16);
    }

    std::reverse(result.begin(), result.end());
    return sign.append(result);
}
} //namespace HexSummator
