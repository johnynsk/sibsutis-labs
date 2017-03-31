#include "../tree/random.hpp"
#include <iostream>

int main()
{
    Tree::Random *tree = new Tree::Random();
    int values[] = {5,-2, 9, -3, 2, 3, 8, 7, 19};
    struct Tree::container temp;
    for (auto i = 0; i < 8; i++) {
        temp.data = values[i];
        tree->push(&temp);
    }

    std::vector<struct Tree::container*> data = tree->getAllChilds();
    for (struct Tree::container *element : data)
    {
        std::cout << " " << element->data;
    }

    return 0;
}
