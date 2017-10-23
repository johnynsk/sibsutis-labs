#ifndef SAPD_MERGE_H
#define SAPD_MERGE_H
#include "list.hpp"
#include "report.hpp"
#include <vector>
#include <map>
#include <typeinfo>
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

            //std:cerr << "incoming value = " << renderItems(list) <<std::endl << std::endl;

            while (iterator != list.end()) {
                //std:cerr << "separate iteration = " << length << std::endl;

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

                //std:cerr << "size=" << size << std::endl;
                //std:cerr << "listA = " << renderItems(listA) << std::endl;
                //std:cerr << "listB = " << renderItems(listB) << std::endl;

                auto iteratorA = listA.begin();
                auto endA = listA.end();
                auto iteratorB = listB.begin();
                auto endB = listB.begin();
                std::map<K, std::vector<T*>> newListA;
                std::map<K, std::vector<T*>> newListB;

                position = 0;

                while (iteratorA != listA.end() || iteratorB != listB.end()) {
                    //std:cerr << "position=" << position << std::endl;
// merge
                    int maxLength = size;
                    std::map<K, std::vector<T*>> queue;
                    int readedA = 0;
                    int readedB = 0;

                    //std:cerr << "before all iterations size = " << maxLength << ";" << "\n";
                    while ((iteratorA != listA.end()) && (iteratorB != listB.end())) {
                        if ((*iteratorA).second.size() <= (*iteratorB).second.size() && readedA < maxLength) {
                            //std:cerr << "insert A\n";
                            queue.insert((*iteratorA));
                            iteratorA++;
                            readedA++;

                            continue;
                        }

                        if (readedB >= maxLength) {
                            break;
                        }
                        //std:cerr << (iteratorB == listB.end() ? "true" : "false");
                        ////std:cerr << renderItems(*listB);
                        //std:cerr << "insert B\n";// << iteratorB == listB.end ()<< ":" << *listB.end() << "\n";
                        queue.insert((*iteratorB));
                        iteratorB++;
                        readedB++;
                    }

                    //std:cerr << "Loop ended\n";

                    while (iteratorA != listA.end() && readedA < maxLength) {
                        //std:cerr << "insert A\n";
                        queue.insert((*iteratorA));
                        iteratorA++;
                        readedA++;
                    }

                    while (iteratorB != listB.end() && readedB < maxLength) {
                        //std:cerr << "insert B\n";
                        queue.insert((*iteratorB));
                        iteratorB++;
                        readedB++;
                    }

                    //std:cerr << "output data\n";
//endof merge
                    //std::map<K, std::vector<T*>> merged =  qmerge(iteratorA, endA, iteratorB, endB);

                    //std:cerr << "merged = " ;
                    //std:cerr << renderItems(queue) << std::endl;
                    for (auto item: queue) {
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
            //std:cerr << ":" << listA.size() << ":" << listB.size() << "\n";
            return listA;
        }

        template <typename T>
        std::vector<T*> sort(std::vector<T*> list)
        {
            std::vector<T*> listA;
            std::vector<T*> listB;
            auto iterator = list.begin();

            int length = 0;
            int position = 0;
            int size = 1;

            while (iterator != list.end()) {
                if (length % 2 == 0) {
                    listA.push_back(*iterator);
                } else {
                    listB.push_back(*iterator);
                }

                length++;
                iterator++;
            }

            std::vector<T*> newListA;
            std::vector<T*> newListB;

            // разбил случайным образом на 2 списка
            while (size < length) {

                auto iteratorA = listA.begin();
                auto iteratorB = listB.begin();
                std::vector<T*> newListA;
                std::vector<T*> newListB;

                position = 0;

                while (iteratorA != listA.end() || iteratorB != listB.end()) {
// merge
                    int maxLength = size;
                    std::vector<T*> queue;
                    int readedA = 0;
                    int readedB = 0;

                    while ((iteratorA != listA.end()) && (iteratorB != listB.end())) {
                        if ((*iteratorA) <= (*iteratorB) && readedA < maxLength) {
                            queue.push_back(*iteratorA);
                            iteratorA++;
                            readedA++;

                            continue;
                        }

                        if (readedB >= maxLength) {
                            break;
                        }

                        queue.push_back(*iteratorB);
                        iteratorB++;
                        readedB++;
                    }

                    while (iteratorA != listA.end() && readedA < maxLength) {
                        queue.push_back(*iteratorA);
                        iteratorA++;
                        readedA++;
                    }

                    while (iteratorB != listB.end() && readedB < maxLength) {
                        queue.push_back(*iteratorB);
                        iteratorB++;
                        readedB++;
                    }
//endof merge
                    for (auto item: queue) {
                        if (position % 2 == 0) {
                            newListA.push_back(item);
                        } else {
                            newListB.push_back(item);
                        }
                    }

                    position++;
                }

                size *= 2;
                listA = newListA;
                listB = newListB;
            }

            return listA;
        }



    } //namespace Merge
} //namespace Sapd


#endif
