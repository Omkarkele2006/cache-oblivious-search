#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "../structures/veb/veb_layout.hpp"
#include "../structures/veb/veb_tree.hpp"
#include "../structures/bst/bst.hpp"
#include "../structures/btree/btree.hpp"

#include "../common/timer.hpp"
#include "workload_generator.hpp"

const int NUM_RUNS = 5;

// ================= DATASET SAVE =================
void save_dataset(const std::vector<int>& data, const std::string& filename) {
    std::ofstream out(filename);

    for (int x : data) {
        out << x << "\n";
    }

    out.close();
}

// ================= BST =================
double bst_insert(const std::vector<int>& data, std::ofstream& out, const std::string& workload, int n) {
    double total = 0;

    for (int i = 1; i <= NUM_RUNS; i++) {
        BST tree;
        Timer t;

        t.start();
        for (int x : data) tree.insert(x);
        double time = t.stop();

        total += time;

        out << "BST," << workload << "," << n
            << ",insert," << time << "," << i << "\n";
    }

    return total / NUM_RUNS;
}

double bst_search(const std::vector<int>& data, std::ofstream& out, const std::string& workload, int n) {
    BST tree;
    for (int x : data) tree.insert(x);

    double total = 0;

    for (int i = 1; i <= NUM_RUNS; i++) {
        Timer t;

        t.start();
        for (int x : data) tree.search(x);
        double time = t.stop();

        total += time;

        out << "BST," << workload << "," << n
            << ",search," << time << "," << i << "\n";
    }

    return total / NUM_RUNS;
}

// ================= B-TREE =================
double btree_insert(const std::vector<int>& data, std::ofstream& out, const std::string& workload, int n) {
    double total = 0;

    for (int i = 1; i <= NUM_RUNS; i++) {
        BTree tree;
        Timer t;

        t.start();
        for (int x : data) tree.insert(x);
        double time = t.stop();

        total += time;

        out << "BTree," << workload << "," << n
            << ",insert," << time << "," << i << "\n";
    }

    return total / NUM_RUNS;
}

double btree_search(const std::vector<int>& data, std::ofstream& out, const std::string& workload, int n) {
    BTree tree;
    for (int x : data) tree.insert(x);

    double total = 0;

    for (int i = 1; i <= NUM_RUNS; i++) {
        Timer t;

        t.start();
        for (int x : data) tree.search(x);
        double time = t.stop();

        total += time;

        out << "BTree," << workload << "," << n
            << ",search," << time << "," << i << "\n";
    }

    return total / NUM_RUNS;
}

// ================= VEB =================
double veb_build(const std::vector<int>& data, std::ofstream& out, const std::string& workload, int n) {
    double total = 0;

    for (int i = 1; i <= NUM_RUNS; i++) {
        VEBLayout layout;
        Timer t;

        t.start();
        layout.construct(data);
        double time = t.stop();

        total += time;

        out << "vEB," << workload << "," << n
            << ",build," << time << "," << i << "\n";
    }

    return total / NUM_RUNS;
}

double veb_search(const std::vector<int>& data, std::ofstream& out, const std::string& workload, int n) {
    VEBLayout layout_builder;
    layout_builder.construct(data);

    VEBTree tree;
    tree.build(layout_builder.get_layout());

    double total = 0;

    for (int i = 1; i <= NUM_RUNS; i++) {
        Timer t;

        t.start();
        for (int x : data) tree.search(x);
        double time = t.stop();

        total += time;

        out << "vEB," << workload << "," << n
            << ",search," << time << "," << i << "\n";
    }

    return total / NUM_RUNS;
}

// ================= MAIN =================
int main() {
    std::ofstream outfile("src/benchmark/results.csv");
    outfile << "structure,workload,n,operation,time_ms,run_id\n";

    std::vector<int> sizes = {1000, 5000, 10000, 20000};

    for (int n : sizes) {
        std::cout << "\n===== n = " << n << " =====\n";

        std::vector<std::pair<std::string, std::vector<int>>> workloads = {
            {"uniform", WorkloadGenerator::generate_uniform(n)},
            {"sorted", WorkloadGenerator::generate_sorted(n)},
            {"reverse", WorkloadGenerator::generate_reverse_sorted(n)}
        };

        for (auto& [type, data] : workloads) {

            std::string filename = "data/raw/" + type + "_" + std::to_string(n) + ".csv";
            save_dataset(data, filename);

            // -------- BST --------
            std::cout << "[BST] Workload: " << type << std::endl;
            double bst_ins = bst_insert(data, outfile, type, n);
            double bst_srch = bst_search(data, outfile, type, n);

            std::cout << "Insert: " << bst_ins << " ms\n";
            std::cout << "Search: " << bst_srch << " ms\n";

            // -------- B-TREE --------
            std::cout << "[BTree] Workload: " << type << std::endl;
            double bt_ins = btree_insert(data, outfile, type, n);
            double bt_srch = btree_search(data, outfile, type, n);

            std::cout << "Insert: " << bt_ins << " ms\n";
            std::cout << "Search: " << bt_srch << " ms\n";

            // -------- VEB --------
            std::cout << "[vEB] Workload: " << type << std::endl;

            std::vector<int> sorted_data = data;
            std::sort(sorted_data.begin(), sorted_data.end());

            double veb_bld = veb_build(sorted_data, outfile, type, n);
            double veb_srch = veb_search(sorted_data, outfile, type, n);

            std::cout << "Build: " << veb_bld << " ms\n";
            std::cout << "Search: " << veb_srch << " ms\n";
        }
    }

    outfile.close();
    return 0;
}