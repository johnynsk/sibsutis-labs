#include <fstream>
#include <iostream>
#include <locale>
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include "./record.hpp"
#include "../merge_t.hpp"

struct record_cp866 {
    char loaner[32];//32
    unsigned short int sum;
    char date[8];//8
    char lawyer[22];//22
};

std::string to_utf8(std::string source);
int main();
std::map<std::string, std::vector<Record*> > sequence(std::vector<Record *> records);

std::string to_utf8(std::string source)
{
    boost::locale::generator gen;

    std::string result = boost::locale::conv::to_utf<char>(
        std::string(source),
        (std::locale) gen.generate("ru_RU.cp866"),
        boost::locale::conv::default_method
    );

    return result;
}

std::map<std::string, std::vector<Record*> > sequence(std::vector<Record *> records)
{
    std::map<std::string, std::vector<Record *> > grouped;

    for (auto current: records) {
        std::cout << ":" << current->getKey() << "\n";
        if (grouped.find(current->getKey()) == grouped.end()) {
            std::vector<Record *> container;
            grouped[current->getKey()] = container;
        }

        grouped[current->getKey()].push_back(current);
    }

    return grouped;
}

int main()
{
    std::fstream file;
    file.open("./sapd/sapd26/BASE3.dat", std::ios::binary | std::ios::in);

    struct record_cp866 buffer;
    std::vector<Record*> records;

    int limiter = 0;
    while (file.good() && file.read((char*) &buffer, sizeof(buffer))) {
        records.push_back(new Record{
            to_utf8(std::string(&buffer.loaner[0], &buffer.loaner[31])),
            buffer.sum,
            to_utf8(std::string(&buffer.date[0], &buffer.date[8])),
            to_utf8(std::string(&buffer.lawyer[0], &buffer.lawyer[21]))
        });

        if (limiter >= 5) {
            break;
        }

        limiter++;
    }

    std::cerr << "readed " << records.size() << " records\n";

    for (auto item: records) {
        std::cerr << item->getLawyer() << "\n";
    }

    auto sequenced = sequence(records);
    std::cerr << "sequenced " << sequenced.size() << " records\n";

    for (auto item: sequenced) {
        std::cerr << item.first << "\n";

        for (auto element: item.second) {
            std::cerr << "-- " << element->getLawyer() << " [" << element->getSum() << "]\n";
        }
    }


    auto sorted = Sapd::Merge::sort<std::string, Record>(sequenced);

    for (auto item: sorted) {
        std::cerr << item.first << "\n";
    }

    return 0;
}
