#include <iostream>
#include "structures/veb/veb_layout.hpp"
#include "structures/veb/veb_tree.hpp"

int main() {
    std::vector<int> data = {10, 20, 5, 15, 30};

    VEBLayout layout_builder;
    layout_builder.construct(data);

    VEBTree tree;
    tree.build(layout_builder.get_layout());

    std::cout << tree.search(15) << std::endl; // 1
    std::cout << tree.search(99) << std::endl; // 0

    return 0;
}