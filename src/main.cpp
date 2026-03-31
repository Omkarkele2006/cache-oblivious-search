#include <iostream>
#include <vector>

#include "structures/bst/bst.hpp"
#include "structures/btree/btree.hpp"
#include "structures/veb/veb_layout.hpp"
#include "structures/veb/veb_tree.hpp"

int main() {
    std::vector<int> data = {10, 20, 5, 15, 30};

    std::cout << " DEMO: SEARCH STRUCTURES \n";

    // BST 
    std::cout << "\n[BST]\n";
    BST bst;
    for (int x : data) {
        bst.insert(x);
    }

    std::cout << "Search 15: " << bst.search(15) << std::endl;
    std::cout << "Search 99: " << bst.search(99) << std::endl;


    // B-TREE 
    std::cout << "\n[B-TREE]\n";
    BTree btree;

    for (int x : data) {
        btree.insert(x);
    }

    std::cout << "Search 15: " << btree.search(15) << std::endl;
    std::cout << "Search 99: " << btree.search(99) << std::endl;


    // vEB 
    std::cout << "\n[vEB]\n";

    // Step 1: Build layout
    VEBLayout layout_builder;
    layout_builder.construct(data);

    // Step 2: Build tree
    VEBTree veb;
    veb.build(layout_builder.get_layout());

    // Step 3: Search
    std::cout << "Search 15: " << veb.search(15) << std::endl;
    std::cout << "Search 99: " << veb.search(99) << std::endl;

    return 0;
}