#ifndef VEB_LAYOUT_HPP
#define VEB_LAYOUT_HPP

#include <vector>
#include <algorithm>

class VEBLayout {
private:
    std::vector<int> layout;

    void build(const std::vector<int>& sorted, int l, int r) {
        if (l > r) return;

        int mid = (l + r) / 2;

        // Place root
        layout.push_back(sorted[mid]);

        // Recursively build left and right
        build(sorted, l, mid - 1);
        build(sorted, mid + 1, r);
    }

public:
    void construct(std::vector<int> data) {
        layout.clear();

        // vEB requires sorted data
        std::sort(data.begin(), data.end());

        build(data, 0, data.size() - 1);
    }

    const std::vector<int>& get_layout() const {
        return layout;
    }
};

#endif