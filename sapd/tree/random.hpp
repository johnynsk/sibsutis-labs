#pragma once
#include "abstract.hpp"
#include "container.hpp"
#include <utility>
#include <map>
#include <cstring>
#include <iostream>

namespace Tree
{
class Random : public Abstract
{
    protected:
        struct container *value;
        std::pair<Random *, Random *> leafs;

    public:
        Random() : Abstract(2)
        {
            this->value = nullptr;
        }

        Random (struct container *sourceContainer) : Abstract(2)
        {
            this->value = this->copy(sourceContainer);
        }

        void push(struct container *sourceContainer)
        {
            struct container *container = this->copy(sourceContainer);

            if (this->value == nullptr) {
                this->value = container;
                return;
            }

            if (this->value->data <= container->data) {
                if (!this->leafs.second) {
                    this->leafs.second = new Random(container);
                    return;
                }

                this->leafs.second->push(container);
                return;
            }

            if (this->leafs.first == nullptr) {
                this->leafs.first = new Random(container);
                return;
            }

            this->leafs.first->push(container);
            return;

        }

        std::vector<struct container *> getAllChilds()
        {
            std::vector<struct container *> result, buffer;

            if (this->leafs.first) {
                buffer = this->leafs.first->getAllChilds();

                for (struct container * element: buffer) {
                    result.push_back(this->copy(element));
                }
            }

            if (this->value != nullptr) {
                result.push_back(this->copy(this->value));
            }

            if (this->leafs.second) {
                buffer = this->leafs.second->getAllChilds();

                for (struct container * element: buffer) {
                    result.push_back(this->copy(element));
                }
            }

            return result;
        }

        std::vector<struct container *> collectInfo()
        {
            return this->collectInfo(0);
        }

        std::vector<struct container *> collectInfo(size_t deep)
        {
            std::vector<struct container *> result, buffer;

            if (this->leafs.first) {
                buffer = this->leafs.first->collectInfo(deep + 1);

                for (struct container * element: buffer) {
                    result.push_back(this->copy(element));
                }
            }

            if (this->value != nullptr) {
                result.push_back(this->copy(this->value));
            }

            if (this->leafs.second) {
                buffer = this->leafs.second->collectInfo(deep + 1);

                for (struct container * element: buffer) {
                    result.push_back(this->copy(element));
                }
            }

            return result;
        }


        struct container * copy(struct container * source)
        {
            struct container * result = new struct container();
            memcpy((void*) result, (void*)source, sizeof(source));
            return result;
        }
};
}
