#pragma once
#include <string>
#include <sstream>
class Record
{
    protected:
        std::string loaner;
        std::string lawyer;
        std::string date;
        int year;
        int month;
        int day;
        int sum;
        std::string key;

    public:
    Record(std::string sLoaner, int sSum, std::string sDate, std::string sLawyer)
    {
        this->loaner = sLoaner;
        this->lawyer = sLawyer;
        this->date = sDate;
        this->sum = sSum;
        std::stringstream streamDate(sDate);
        streamDate >> day >> month >> year;
        month = -month;
        year = -year;
        this->key = makeKey();//sLawyer.substr(0, 3).append(std::to_string(sSum));
    }

    private:
    std::string makeKey()
    {
        std::stringstream buffer(this->lawyer);
        std::string lastname;
        std::string firstname;
        std::string patronymic;

        buffer >> lastname;
        buffer >> firstname;
        buffer >> patronymic;

        std::stringstream result;
//        result << firstname << patronymic;

        result << lastname.substr(0, 2) << firstname << patronymic;
        return result.str();
    }

    public:
    std::string getLoaner()
    {
        return this->loaner;
    }
    //std::map<std::string key, Record *record>

    std::string getKey()
    {
        return this->key;
    }

    std::string getLawyer()
    {
        return this->lawyer;
    }

    int getSum()
    {
        return this->sum;
    }

    std::string getDate()
    {
        return this->date;
    }

    bool match (int key)
    {
        if (this->getSum() == key) {
            return true;
        }

        return false;
    }

    int getYear()
    {
        return this->year;
    }

    int getMonth()
    {
        return this->month;
    }

    int getDay()
    {
        return this->day;
    }

    bool operator>(Record *second) {
        if (this->getSum() > second->getSum()) {
            return true;
        }

        if (this->getYear() > second->getYear()) {
            return true;
        }

        if (this->getMonth() > second->getMonth()) {
            return true;
        }

        if (this->getDay() > second->getDay()) {
            return true;
        }

        //if (this->getDate() >
        return true;
    }

    bool operator<(Record *second) {
        if (this->getLawyer() < second->getLawyer()) {
            return true;
        }

        if (this->getLawyer() == second->getLawyer()) {
            if (this->getSum() < second->getSum()) {
                return true;
            }
        }

        if (this->getDate() < second->getDate()) {
            return true;
        }

        return false;
    }

};
