#include <fstream>
#include <iostream>
#include <locale>
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include "./record.hpp"
#include "../merge_t.hpp"
#include "../merge.hpp"
#include "../tree/random_t.hpp"

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
        if (grouped.find(current->getKey()) == grouped.end()) {
            std::vector<Record *> container;
            grouped[current->getKey()] = container;
        }

        grouped[current->getKey()].push_back(current);
    }

    return grouped;
}

void log(std::string message, int level) {
    if (level == 1) {
        std::cerr << message;
    }
}

int main()
{
    std::fstream file;
    file.open("./sapd/sapd26/BASE3.dat", std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл на чтение ./sapd/sapd26/BASE3.dat\n";
        return 1;
    }

    struct record_cp866 buffer;
    std::vector<Record*> records;

    std::cerr << "Чтение из файла\n";

    int limiter = 0;
    while (file.good() && file.read((char*) &buffer, sizeof(buffer))) {
        records.push_back(new Record{
            to_utf8(std::string(&buffer.loaner[0], &buffer.loaner[31])),
            buffer.sum,
            to_utf8(std::string(&buffer.date[0], &buffer.date[8])),
            to_utf8(std::string(&buffer.lawyer[0], &buffer.lawyer[21]))
        });

        limiter++;
    }

    std::cerr << "readed " << records.size() << " records\n";

    auto sequenced = sequence(records);
    std::cerr << "sequenced " << sequenced.size() << " records\n";

    for (auto element: sequenced) {
        std::cout << "* " << element.first << "\n";
    }

    std::string searchKey;
    std::cout << "Введите ключ поиска: ";
    std::cin >> searchKey;

    if (sequenced.find(searchKey) == sequenced.end()) {
        std::cerr << "Записей с таким ключом не обнаружено\n";
        return 2;
    }

    auto founded = sequenced[searchKey];

    for (auto element: founded) {
        std::cerr << "-- " << element->getLawyer() << " [" << element->getSum() << "\t" << element->getDate() << element->getLoaner() << "]\n";
    }

    std::cerr << "[total: " << founded.size() << "]\n";

/*    std::map<int, std::vector<Record*>> treeData;
//    std::vector<Record*>
//    std::map<int, std::map<int, Record*>>;
    for (auto element: founded) {
        if (treeData.find(element->getSum()) == treeData.end()) {
            std::vector<Record *> container;
            treeData[element->getSum()] = container;
        }

        treeData[element->getSum()].push_back(element);
    }*/

    auto sorted = Sapd::Merge::sort(founded);

    Tree::RandomT *tree = new Tree::RandomT();
    for (auto element: sorted) {
        tree->push(element);
    }
/*
    for (auto list: sorted) {
        for (auto item: list.second) {
            item->setWeight =
        }
        std::cerr << item.first << "\n";
    }
*/
    std::cout << "Введите сумму для поиска: ";

    int sum;
    std::cin >> sum;

    std::vector<Record*> filtered = tree->search<int, Record>(sum);

    for (auto element: filtered) {
        std::cout << element->getLawyer() << "\t" << element->getDate() << "\t" << element->getSum() <<"\n";
    }

    return 0;
}
