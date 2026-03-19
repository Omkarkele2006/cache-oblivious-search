#include <iostream>
#include <fstream>
#include <vector>
#include "../common/timer.hpp"
#include "../structures/bst/bst.hpp"
#include "workload_generator.hpp"

const int NUM_RUNS = 5;

double benchmark_insert(const std::vector<int>& data) {
    double total_time = 0.0;

    for (int i = 0; i < NUM_RUNS; ++i) {
        BST tree;
        Timer timer;

        timer.start();
        for (int x : data) {
            tree.insert(x);
        }
        total_time += timer.stop();
    }

    return total_time / NUM_RUNS;
}

double benchmark_search(const std::vector<int>& data) {
    BST tree;

    // Preload tree
    for (int x : data) {
        tree.insert(x);
    }

    double total_time = 0.0;

    for (int i = 0; i < NUM_RUNS; ++i) {
        Timer timer;

        timer.start();
        for (int x : data) {
            tree.search(x);
        }
        total_time += timer.stop();
    }

    return total_time / NUM_RUNS;
}

int main() {
    std::ofstream outfile("results.csv");
    outfile << "structure,workload,n,insert_ms,search_ms\n";

    std::vector<int> sizes = {1000, 5000, 10000, 20000};

    for (int n : sizes) {
        std::cout << "\n===== n = " << n << " =====\n";

        // 3 workloads
        std::vector<std::pair<std::string, std::vector<int>>> workloads = {
            {"uniform", WorkloadGenerator::generate_uniform(n)},
            {"sorted", WorkloadGenerator::generate_sorted(n)},
            {"reverse", WorkloadGenerator::generate_reverse_sorted(n)}
        };

        for (auto& [type, data] : workloads) {
            std::cout << "Workload: " << type << std::endl;

            double insert_time = benchmark_insert(data);
            double search_time = benchmark_search(data);

            std::cout << "Insert: " << insert_time << " ms\n";
            std::cout << "Search: " << search_time << " ms\n";

            outfile << "BST," << type << "," << n << ","
                    << insert_time << "," << search_time << "\n";
        }
    }

    outfile.close();
    return 0;
}