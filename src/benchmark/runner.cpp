#include <iostream>
#include <fstream>
#include <vector>
#include "../structures/veb/veb_layout.hpp"
#include "../structures/veb/veb_tree.hpp"
#include <algorithm>
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
// ---------------- VEB ----------------
double veb_build(const std::vector<int>& data) {
    double total = 0;

    for (int i = 0; i < NUM_RUNS; i++) {
        VEBLayout layout;
        Timer t;

        t.start();
        layout.construct(data);
        total += t.stop();
    }

    return total / NUM_RUNS;
}

double veb_search(const std::vector<int>& data) {
    // Build once
    VEBLayout layout_builder;
    layout_builder.construct(data);

    VEBTree tree;
    tree.build(layout_builder.get_layout());

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
    outfile << "structure,workload,n,build_ms,search_ms\n";

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

            // -------- VEB --------
            std::cout << "[vEB] Workload: " << type << std::endl;

            // vEB requires sorted data
            std::vector<int> sorted_data = data;
            std::sort(sorted_data.begin(), sorted_data.end());

            double veb_bld = veb_build(sorted_data);
            double veb_srch = veb_search(sorted_data);

            std::cout << "Build: " << veb_bld << " ms\n";
            std::cout << "Search: " << veb_srch << " ms\n";

            outfile << "vEB," << type << "," << n << ","
                    << veb_bld << "," << veb_srch << "\n";        
        }
    }

    outfile.close();
    return 0;
}