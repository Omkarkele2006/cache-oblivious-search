#include <iostream>
#include <fstream>
#include <vector>

#include "../common/timer.hpp"
#include "../structures/bst/bst.hpp"
#include "../structures/btree/btree.hpp"
#include "workload_generator.hpp"

const int NUM_RUNS = 5;

// ---------------- BST ----------------
double bst_insert(const std::vector<int>& data) {
    double total = 0;

    for (int i = 0; i < NUM_RUNS; i++) {
        BST tree;
        Timer t;

        t.start();
        for (int x : data) tree.insert(x);
        total += t.stop();
    }

    return total / NUM_RUNS;
}

double bst_search(const std::vector<int>& data) {
    BST tree;
    for (int x : data) tree.insert(x);

    double total = 0;

    for (int i = 0; i < NUM_RUNS; i++) {
        Timer t;

        t.start();
        for (int x : data) tree.search(x);
        total += t.stop();
    }

    return total / NUM_RUNS;
}

// ---------------- B-TREE ----------------
double btree_insert(const std::vector<int>& data) {
    double total = 0;

    for (int i = 0; i < NUM_RUNS; i++) {
        BTree tree;
        Timer t;

        t.start();
        for (int x : data) tree.insert(x);
        total += t.stop();
    }

    return total / NUM_RUNS;
}

double btree_search(const std::vector<int>& data) {
    BTree tree;
    for (int x : data) tree.insert(x);

    double total = 0;

    for (int i = 0; i < NUM_RUNS; i++) {
        Timer t;

        t.start();
        for (int x : data) tree.search(x);
        total += t.stop();
    }

    return total / NUM_RUNS;
}

int main() {
    std::ofstream outfile("results.csv");
    outfile << "structure,workload,n,insert_ms,search_ms\n";

    std::vector<int> sizes = {1000, 5000, 10000, 20000};

    for (int n : sizes) {
        std::cout << "\n===== n = " << n << " =====\n";

        std::vector<std::pair<std::string, std::vector<int>>> workloads = {
            {"uniform", WorkloadGenerator::generate_uniform(n)},
            {"sorted", WorkloadGenerator::generate_sorted(n)},
            {"reverse", WorkloadGenerator::generate_reverse_sorted(n)}
        };

        for (auto& [type, data] : workloads) {

            // -------- BST --------
            std::cout << "[BST] Workload: " << type << std::endl;

            double bst_ins = bst_insert(data);
            double bst_srch = bst_search(data);

            std::cout << "Insert: " << bst_ins << " ms\n";
            std::cout << "Search: " << bst_srch << " ms\n";

            outfile << "BST," << type << "," << n << ","
                    << bst_ins << "," << bst_srch << "\n";

            // -------- B-TREE --------
            std::cout << "[BTree] Workload: " << type << std::endl;

            double bt_ins = btree_insert(data);
            double bt_srch = btree_search(data);

            std::cout << "Insert: " << bt_ins << " ms\n";
            std::cout << "Search: " << bt_srch << " ms\n";

            outfile << "BTree," << type << "," << n << ","
                    << bt_ins << "," << bt_srch << "\n";
        }
    }

    outfile.close();
    return 0;
}