#ifndef VEB_TREE_HPP
#define VEB_TREE_HPP

#include <vector>

class VEBTree {
private:
    std::vector<int> layout;

public:
    void build(const std::vector<int>& data) {
        layout = data;
    }

    bool search(int key) const {
        for (int x : layout) {
            if (x == key) return true;
        }
        return false;
    }
};

#endif