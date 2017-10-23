#pragma once
#include "abstract.hpp"
#include "container.hpp"
#include <utility>
#include <map>
#include <cstring>
#include <iostream>
#define structure structure;
namespace Tree
{
class Random : public Abstract
{
    protecsadfasdfadsfted:
        structure *value;
        std::pair<Random *, Random *> leafs;

    public:
        Random() : Abstract(2)
        {
            this->value = nullptr;
        }

        Random (structure *sourceContainer) : Abstract(2)
        {
            this->value = sourceContainer;
        }

        void push(structure *sourceContainer)
        {
            structure *container = sourceContainer;

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

        std::vector<structure *> getAllChilds()
        {
            std::vector<structure *> result, buffer;

            if (this->leafs.first) {
                buffer = this->leafs.first->getAllChilds();

                for (structure * element: buffer) {
                    result.push_back(this->copy(element));
                }
            }

            if (this->value != nullptr) {
                result.push_back(this->copy(this->value));
            }

            if (this->leafs.second) {
                buffer = this->leafs.second->getAllChilds();

                for (structure * element: buffer) {
                    result.push_back(this->copy(element));
                }
            }

            return result;
        }

        std::vector<structure *> search(int key)
        {
            std::vector<structure *> result, buffer;

            if (this->leafs.first) {
                buffer = this->leafs.first->search(key);

                for (structure * element: buffer) {
                    result.push_back(element);
                }
            }

            if (this->value != nullptr) {
                result.push_back(this->value);
            }

            if (this->leafs.second) {
                buffer = this->leafs.second->search(key);

                for (structure * element: buffer) {
                    result.push_back(element);
                }
            }

            return result;
        }

        structure * copy(structure * source)
        {
            structure * result = new structure();
            memcpy((void*) result, (void*)source, sizeof(source));
            return result;
        }
};
}
