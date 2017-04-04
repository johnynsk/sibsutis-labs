#ifndef SAPD_MERGE_H
#define SAPD_MERGE_H
#include "list.hpp"
#include "report.hpp"
#include <vector>
#include <map>

#include <csignal>

namespace Sapd
{
     namespace Merge
    {
        template <typename K, typename T>
        std::string renderItems(std::map<K, std::vector<T*>> array)
        {
            std::stringstream result;
            result << "[" << array.size() << "] ";

            for (auto item: array) {
                result << item.first << " ";
            }

            return result.str();
            return "";
        }


        template<typename K, typename T>
        std::pair<
            std::pair<
                typename std::map<K, std::vector<T*>>::iterator,
                typename std::map<K, std::vector<T*>>::iterator
            >,
            std::map<K, std::vector<T*>>
        >merge(
                typename std::map<K, std::vector<T*>>::iterator &iteratorA,
                typename std::map<K, std::vector<T*>>::iterator endA,
                typename std::map<K, std::vector<T*>>::iterator &iteratorB,
                typename std::map<K, std::vector<T*>>::iterator endB,
                int maxLength
        ) {
            std::map<K, std::vector<T*>> queue;
            int readedA = 0;
            int readedB = 0;

            std::cerr << "before all iterations size = " << maxLength << ";" << "\n";
            //std::raise(SIGABRT);
            while ((iteratorA != endA) && (iteratorB != endB)) {
//                std::cerr << renderItems(queue) << (iteratorB == listB.end() ? "true" : "false")  <<"." << listA.size() <<"."<< listB.size() <<".";
 //               std::cerr << (iteratorB == listB.begin() ? "true": "false") <<";";
                if ((*iteratorA).second.size() <= (*iteratorB).second.size() && readedA < maxLength) {
                    std::cerr << "insert A\n";
                    queue.insert((*iteratorA));
                    iteratorA++;
                    readedA++;

                    continue;
                }

                if (readedB >= maxLength) {
                    break;
                }
                //std::cerr << renderItems(*listB);
                std::cerr << "insert B\n";// << iteratorB == listB.end ()<< ":" << *listB.end() << "\n";
                queue.insert((*iteratorB));
                iteratorB++;
                readedB++;
            }

            std::cerr << "Loop ended\n";

            while (iteratorA != endA && readedA < maxLength) {
                std::cerr << "insert A\n";
                queue.insert((*iteratorA));
                iteratorA++;
                readedA++;
            }

            while (iteratorB != endB && readedB < maxLength) {
                std::cerr << "insert B\n";
                queue.insert((*iteratorB));
                iteratorB++;
                readedB++;
            }

            std::cerr << "output data\n";

            std::pair<
                    std::pair<
                        typename std::map<K, std::vector<T*>>::iterator,
                        typename std::map<K, std::vector<T*>>::iterator
                    >,
                std::map<K, std::vector<T*>>
                > result;
            //result.first.first = iteratorA;
            //result.first.second = iteratorB;
            result.second = queue;
            return result;
        }

       //std::vector<struct list*>
        template <typename K, typename T>
        std::map<K, std::vector<T*>> sort(std::map<K, std::vector<T*>> list)
        {
            std::map<K, std::vector<T*>> listA;
            std::map<K, std::vector<T*>> listB;
            auto iterator = list.begin();

            int length = 0;
            int position = 0;
            int size = 1;

            std::cerr << "incoming value = " << renderItems(list) <<std::endl << std::endl;

            while (iterator != list.end()) {
                std::cerr << "separate iteration = " << length << std::endl;

                if (length % 2 == 0) {
                    listA[(*iterator).first] = (*iterator).second;
                } else {
                    listB[(*iterator).first] = (*iterator).second;
                }

                length++;
                iterator++;
            }

            std::map<K, std::vector<T*>> newListA;
            std::map<K, std::vector<T*>> newListB;

            // разбил случайным образом на 2 списка
            while (size < length) {

                std::cerr << "size=" << size << std::endl;
                std::cerr << "listA = " << renderItems(listA) << std::endl;
                std::cerr << "listB = " << renderItems(listB) << std::endl;

                auto iteratorA = listA.begin();
                auto iteratorB = listB.begin();
                std::map<K, std::vector<T*>> newListA;
                std::map<K, std::vector<T*>> newListB;

                position = 0;

                while (iteratorA != listA.end() || iteratorB != listB.end()) {
                    std::cerr << "position=" << position << std::endl;
                    auto mergedResult = merge(iteratorA, listA.end(), iteratorB, listB.end(), size);
//                    iteratorA = mergedResult.first.first;
//                    iteratorB = mergedResult.first.second;
                    auto merged = mergedResult.second;

                    std::cerr << "merged = " ;
                    std::cerr << renderItems(merged) << std::endl;
                    for (auto item: merged) {
                        if (position % 2 == 0) {
                            newListA[item.first] = item.second;
                        } else {
                            newListB[item.first] = item.second;
                        }
                    }

                    position++;
//                    if (position > 10) break;
                }

                size *= 2;
                listA = newListA;
                listB = newListB;
            }

  //          std::vector<struct list*> result;
  //          result.allocate(2);

//            result[0] = listA;
//            result[1] = listB;
//
//            return result;
            std::cerr << ":" << listA.size() << ":" << listB.size() << "\n";
            return listA;
        }


    } //namespace Merge
} //namespace Sapd


#endif
