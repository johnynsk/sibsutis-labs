#ifndef SAPD_QUEUE_H
#define SAPD_QUEUE_H
#include <string>
#include <sstream>
#include <vector>

#include "report.hpp"

namespace Sapd
{
    struct item {
        int data;
        struct item *next;
    };

    struct list {
        struct item *begin;
        struct item *end;
    };

    void
    drop(struct list &list)
    {
        struct item *item;
        struct item *iterator = list.begin;

        while (iterator != NULL) {
            item = iterator;
            iterator = item->next;

            delete item;
        }

        list.begin = nullptr;
        list.end = nullptr;
    }

    std::string
    render(struct list *list)
    {
        std::stringstream result;
        std::stringstream items;
        int count = 0;
        struct item *item = list->begin;

        items << "[";

        while (item != nullptr) {
            if (count != 0) {
                items << ", ";
            }

            items << item->data;
            item = item->next;
            count++;
        }

        items << "]";

        result << "struct list (" << count << "): " << std::endl << items.str() << std::endl;

        return result.str();
    }

    struct list
    *create()
    {
        struct list *list = new struct list;

        list->begin = nullptr;
        list->end = nullptr;

        return list;
    }

    struct list
    clear(struct list &list)
    {
        drop(list);
        list.begin = nullptr;
        list.end = nullptr;

        return list;
    }

    struct checksum
    checksum(struct list *list)
    {
        struct checksum result;
        result.sum = 0;
        result.series = 0;
        struct item *iterator = list->begin;

        if (iterator == nullptr) {
            return result;
        }

        int previous = iterator->data;

        while (iterator != nullptr) {
            result.sum += iterator->data;

            if (previous > iterator->data) {
                result.series++;
            }

            iterator = iterator->next;
        }

        return result;
    }

    namespace Queue {
        struct list
        *push(struct list *queue, int data)
        {
            struct item *item = new struct item;
            item->data = data;
            item->next = nullptr;

            if (queue->begin == nullptr) {
                queue->begin = item;
            } else {
                queue->end->next = item;
            }

            queue->end = item;

            return queue;
        }

        struct list
        *fill(struct list *list, std::vector<int> &values)
        {
            for (std::size_t i = 0; i < values.size(); i++) {
                push(list, values[i]);
            }

            return list;
        }
    } // namespace Queue

    namespace Stack
    {
        struct list
        *push(struct list *stack, int data)
        {
            struct item *item = new struct item;
            item->data = data;
            item->next = stack->begin;

            stack->begin = item;

            return stack;
        }

        struct list
        *fill(struct list *list, std::vector<int> &values)
        {
            for (std::size_t i = 0; i < values.size(); i++) {
                push(list, values[i]);
            }

            return list;
        }
    } //namespace Stack
} //namespace Sapd

#endif
