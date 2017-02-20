#pragma once
#include "abstract.hpp"
#include "container.hpp"
#include <utility>

namespace Tree
{
class Random : public Abstract
{
    protected:
        std::pair<Random, Random> leafs;
        struct container value;

    public:
        Random() : Abstract(2)
        {
            this->value = nullptr;
        }

        Random (struct container container) : Abstract(2)
        {
            this->value = container;
        }

        void push(struct container *container)
        {
            if (this->value == nullptr) {
                this->value = container;
                return;
            }

            if (this->value->data <= container->data) {
                if (!this->leafs.second) {
                    this->leafs.second = container;
                    return;
                }

                this->leafs.second.push(container);
                return;
            }

            if (!this->leafs.first) {
                this->leafs.first = container;
                return;
            }

            this->leafs.first.push(container);
            return;

        }

        std::vector<struct container> getAllChilds()
        {
            std::vector<struct container> result, buffer;

            if (this->leafs.first) {
                buffer = this->leafs.first->getAllChilds();

                for (struct container element: buffer) {
                    result.push_back(element);
                }
            }

            if (this->value) {
                result.push_back(this->value);
            }

            if (this->leafs.second) {
                buffer = this->leafs.second->getAllChilds();

                for (struct container element: buffer) {
                    result.push_back(element);
                }
            }

            return result;
        }
};
}
