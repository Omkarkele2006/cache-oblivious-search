#include <iostream>
#include "structures/btree/btree.hpp"

int main() {
    BTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    std::cout << tree.search(10) << std::endl; // 1
    std::cout << tree.search(99) << std::endl; // 0

    return 0;
}