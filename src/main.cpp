#include <iostream>
#include "structures/bst/bst.hpp"

int main() {
    BST tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    std::cout << tree.search(10) << std::endl; // 1
    std::cout << tree.search(7) << std::endl;  // 0

    return 0;
}