#include <sstream>
#include <iostream>
#include <string.h>

#ifndef PROJECT_APP_MAN
#define PROJECT_APP_MAN

namespace Application {

class Man {
    public:
        std::string format();
        std::string format(int offset);

        char surname[64];
        int number;
        int points;
};

std::string
Man::format()
{
    std::stringstream result;

    result
        << " фамилия: " << surname
        << "; номер: " << number
        << "; очков: " << points
        << std::endl;

    return result.str();
}

std::string
Man::format(int offset)
{
    std::stringstream result;

    result
        << "#" << offset
        << " фамилия: " << surname
        << "; номер: " << number
        << "; очков: " << points
        << std::endl;

    return result.str();
}

Man
readMan()
{
    Man item;
    std::string surname;

    std::cin.ignore();

    std::cout << " фамилия: > ";
    getline(std::cin, surname);
    strcpy(item.surname, surname.c_str());

    std::cout << " номер: > ";
    std::cin >> item.number;

    std::cout << " очков: > ";
    std::cin >> item.points;

    std::cin.ignore();

    return item;
}
} //napespace Application

#endif

