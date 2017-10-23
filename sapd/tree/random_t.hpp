#pragma once
#include "abstract.hpp"
#include "container.hpp"
#include <utility>
#include <map>
#include <cstring>
#include <iostream>
#include "../sapd26/record.hpp"

namespace Tree
{
class RandomT : public Abstract
{
    protected:
        Record *value;
        std::pair<RandomT *, RandomT *> leafs;

    public:
        RandomT() : Abstract(2)
        {
            this->value = nullptr;
        }

        template <typename T>
        RandomT (T *sourceContainer) : Abstract(2)
        {
            this->value = sourceContainer;
        }

        template <typename T>
        void push(T &sourceContainer)
        {
            auto container = sourceContainer; //his->copy(sourceContainer);

            if (this->value == nullptr) {
                this->value = container;
                return;
            }

            if (this->value <= container) {
                if (!this->leafs.second) {
                    this->leafs.second = new RandomT(container);
                    return;
                }

                this->leafs.second->push(container);
                return;
            }

            if (this->leafs.first == nullptr) {
                this->leafs.first = new RandomT(container);
                return;
            }

            this->leafs.first->push(container);
            return;

        }


        std::vector<Record*> getAllChilds()
        {
            std::vector<Record*> result;

            if (this->leafs.first != nullptr) {
                auto buffer = this->leafs.first->getAllChilds();

                for (auto element: buffer) {
                    result.push_back(element);
                }
            }

            if (this->value != nullptr) {
                result.push_back(this->value);
            }

            if (this->leafs.second != nullptr) {
                auto buffer = this->leafs.second->getAllChilds();

                for (auto element: buffer) {
                    result.push_back(element);
                }
            }

            return result;
        }

        template <typename K, typename T>
        std::vector<T*> search(K key)
        {
            std::vector<T*> result;

            if (this->leafs.first != nullptr) {
                auto found = this->leafs.first->search<K, T>(key);

                for (auto element: found) {
                    result.push_back(element);
                }
            }

            if (this->value->match(key)) {
                result.push_back(this->value);
            }

            if (this->leafs.second != nullptr) {
                auto found = this->leafs.second->search<K, T>(key);

                for (auto element: found) {
                    result.push_back(element);
                }
            }

            return result;
        }

        int sgetWidth()
        {
            return this->width;
        }

};
}
