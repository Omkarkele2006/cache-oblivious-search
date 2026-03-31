#ifndef WORKLOAD_GENERATOR_HPP
#define WORKLOAD_GENERATOR_HPP

#include <vector>
#include <random>
#include <algorithm>

class WorkloadGenerator {
public:

    // Uniform random
    static std::vector<int> generate_uniform(int n, int min = 1, int max = 1000000) {
        std::vector<int> data;
        data.reserve(n);

        std::mt19937 gen(42);  // fixed seed for reproducibility
        std::uniform_int_distribution<> dist(min, max);

        for (int i = 0; i < n; ++i) {
            data.push_back(dist(gen));
        }

        return data;
    }

    // Sorted (worst-case BST)
    static std::vector<int> generate_sorted(int n) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            data[i] = i;
        }
        return data;
    }

    // Reverse sorted (also worst-case)
    static std::vector<int> generate_reverse_sorted(int n) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            data[i] = n - i;
        }
        return data;
    }
};

#endif