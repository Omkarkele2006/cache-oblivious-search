#ifndef VEB_LAYOUT_HPP
#define VEB_LAYOUT_HPP

#include <vector>
#include <algorithm>
#include "veb_node.hpp"

class VEBLayout {
private:
    std::vector<VEBNode> layout;

    void build(const std::vector<int>& sorted, int l, int r) {
        if (l > r) return;

        int mid = (l + r) / 2;

        int left_size = mid - l;

        layout.push_back({sorted[mid], left_size});

        build(sorted, l, mid - 1);
        build(sorted, mid + 1, r);
    }

public:
    void construct(std::vector<int> data) {
        layout.clear();
        std::sort(data.begin(), data.end());
        build(data, 0, data.size() - 1);
    }

    const std::vector<VEBNode>& get_layout() const {
        return layout;
    }
};

#endif