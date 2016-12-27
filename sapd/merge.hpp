#ifndef SAPD_MERGE_H
#define SAPD_MERGE_H
#include "list.hpp"
#include "report.hpp"

namespace Sapd
{
    namespace Merge
    {
        struct list
        *merge(struct item **iteratorA, struct item **iteratorB, int maxLength)
        {
            struct list *queue = new struct list;
            queue->begin = nullptr;
            int readedA = 0;
            int readedB = 0;

            while ((*iteratorA) != nullptr && (*iteratorB) != nullptr) {
//                result.compares++;
                if ((*iteratorA)->data <= (*iteratorB)->data && readedA < maxLength) {
                    Sapd::Queue::push(queue, (*iteratorA)->data);
                    (*iteratorA) = (*iteratorA)->next;
                    readedA++;
//                    result.swaps++;

                    continue;
                }

                if (readedB >= maxLength) {
                    break;
                }

                Sapd::Queue::push(queue, (*iteratorB)->data);
                (*iteratorB) = (*iteratorB)->next;
                readedB++;
//                result.swaps++;
            }

            while ((*iteratorA) != nullptr && readedA < maxLength) {
                Sapd::Queue::push(queue, (*iteratorA)->data);
                (*iteratorA) = (*iteratorA)->next;
                readedA++;
//                result.swaps++;
            }

            while ((*iteratorB) != nullptr && readedB < maxLength) {
                Sapd::Queue::push(queue, (*iteratorB)->data);
                (*iteratorB) = (*iteratorB)->next;
                readedB++;
//                result.swaps++;
            }

            return queue;
        }

        //std::vector<struct list*>
        void
        sort(struct list *list)
        {
            struct list *listA = new struct list;
            struct list *listB = new struct list;
            listB->begin = nullptr;
            listA->begin = nullptr;

            struct item *iterator = list->begin;

            int length = 0;
            int position = 0;
            int size = 1;

            std::cerr << "incoming value = " << render(list) <<std::endl << std::endl;

            while (iterator != nullptr) {
                std::cerr << "separate iteration = " << length << std::endl;

                if (length % 2 == 0) {
                    Sapd::Queue::push(listA, iterator->data);
                } else {
                    Sapd::Queue::push(listB, iterator->data);
                }

                length++;
                iterator = iterator->next;
            }

            struct list *newListA = new struct list;
            struct list *newListB = new struct list;
            newListA->begin = nullptr;
            newListB->begin = nullptr;

            // разбил случайным образом на 2 списка
            while (size < length) {
                std::cerr << "size=" << size << std::endl;
                std::cerr << "listA = " << render(listA) << std::endl;
                std::cerr << "listB = " << render(listB) << std::endl;

                struct item *iteratorA = listA->begin;
                struct item *iteratorB = listB->begin;

                newListA = new struct list;
                newListB = new struct list;
                newListA->begin = nullptr;
                newListB->begin = nullptr;


                position = 0;

                while (iteratorA != nullptr || iteratorB != nullptr) {
                    std::cerr << "position=" << position << std::endl;
                    struct list *merged = merge(&iteratorA, &iteratorB, size);

                    std::cerr << "merged = " ;
                    std::cerr<< Sapd::render(merged) << std::endl;

                    if (position % 2 == 0) {
                        Sapd::Queue::append(newListA, merged);
                    } else {
                        Sapd::Queue::append(newListB, merged);
                    }

                    position++;
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
        }


    } //namespace Merge
} //namespace Sapd


#endif
