#ifndef VEB_TREE_HPP
#define VEB_TREE_HPP

#include <vector>
#include "veb_node.hpp"


class VEBTree {
private:
    std::vector<VEBNode> layout;

    bool search_rec(int key, int index) const {
        if (index >= layout.size()) return false;

        const VEBNode& node = layout[index];

        if (node.key == key) return true;

        int left_index = index + 1;
        int right_index = index + 1 + node.left_size;

        if (key < node.key) {
            return search_rec(key, left_index);
        } else {
            return search_rec(key, right_index);
        }
    }

public:
    void build(const std::vector<VEBNode>& data) {
        layout = data;
    }

    bool search(int key) const {
        return search_rec(key, 0);
    }
};

#endif