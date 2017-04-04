#include <string>
#include <sstream>
class Record
{
    protected:
        std::string loaner;
        std::string lawyer;
        std::string date;
        int sum;
        std::string key;

    public:
    Record(std::string sLoaner, int sSum, std::string sDate, std::string sLawyer)
    {
        this->loaner = sLoaner;
        this->lawyer = sLawyer;
        this->date = sDate;
        this->sum = sSum;

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
        result << firstname << patronymic;

//        result << lastname.substr(0, 2) << firstname << patronymic;
        return result.str();
    }

    public:

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

    bool operator<(Record *second) {
        if (this->getLawyer() < second->getLawyer()) {
            return true;
        }

        if (this->getLawyer() == second->getLawyer()) {
            if (this->getSum() < second->getSum()) {
                return true;
            }
        }

        return false;
    }
};
