#include <vector>
#include <iostream>
#include <map>
#include <string>
/*
        template<typename K, typename T>
        std::map<K, std::vector<T*>>
        qmerge(
                typename std::map<K, std::vector<T*>>::iterator &iteratorA,
                typename std::map<K, std::vector<T*>>::iterator &endA,
                typename std::map<K, std::vector<T*>>::iterator &iteratorB,
                typename std::map<K, std::vector<T*>>::iterator &endB
//                int maxLength
        ) {
            std::map<K, std::vector<T*>> result;
            return result;
        }
*/

bool iterate(std::map<std::string, std::vector<int>>::iterator &iterator, std::map<std::string, std::vector<int>>::iterator &end, std::map<std::string, std::vector<int>> &list)
{
    if (iterator == list.end()) {
        return false;
    }

    std::cerr << (iterator == end ? "true": "false") << "\n";

    iterator++;
    return true;
}

int main ()
{
//    std::map<std::string, std::vector<int*>> list;
 //   std::map<std::string, std::vector<int*>>::iterator iteratorA = list.begin();
//    std::map<std::string, std::vector<int*>>::iterator endA = list.end();
//    qmerge(iteratorA, endA, iteratorA, endA);
    std::map<std::string, std::vector<int>> test;
    test["d"].push_back(5);
    test["b"].push_back(6);
    test["c"].push_back(7);
    test["a"].push_back(8);
    test["0"].push_back(0);
    test["1"].push_back(1);
    auto iterator = test.begin();
    auto iteratorE = test.end();
    int counts = 0;

/*    do {
        std::cout << (*iterator).first << ":";
        if (counts++ > 5) {
            std::cerr << "bad iterator change\n";
            break;
        }

        std::cout << (iterator == test.end() ? "itrue": "ifalse") << "\n";
//        iterator++;
    }
//    } while (iterator != test.end());
//    while (iterate(iterator, iteratorE, test));
*/
    class A {
        public:
        int Compare(const A &other) {
            std::cout << "s111";
            return 0;
        }

        bool operator>(const A &other) {
            std::cout << "something";
            return false;
        }

        bool operator<(const A &other) {
            std::cout << "smth";
            return false;
        }

        int operator>(A *other) {
            std::cout << "qweqwe";
            return 1;
        }
    };

    A *a = new A();
    A *b = new A();
    std::cout << (*a > b ? "true" : "false") << "\n";
    return 0;
}
