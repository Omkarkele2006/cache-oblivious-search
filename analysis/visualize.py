🚀 Cache-Oblivious Search Structures
📌 Project Title

Design and Empirical Evaluation of Cache-Oblivious Search Structures for Modern Memory Hierarchies

📖 Overview

Modern computing performance is heavily influenced by memory hierarchy behavior (L1/L2/L3 cache, RAM). Traditional data structures often fail to fully exploit cache locality.

This project explores and benchmarks three fundamental search structures:

🌳 Binary Search Tree (BST) — cache-unaware baseline

📦 B-Tree — cache-aware structure

⚡ van Emde Boas (vEB) Layout — cache-oblivious structure

The goal is to understand how memory locality impacts real-world performance, beyond theoretical complexity.

🎯 Objectives

Compare build and search performance

Evaluate impact of input distribution

Analyze cache locality effects

Demonstrate advantages of cache-oblivious design

🛠️ Tech Stack
Component	Technology
Core Implementation	C++ (STL, std::chrono)
Data Analysis	Python (pandas, matplotlib)
Environment	WSL (Ubuntu/Linux)
Future Scope	perf, PostgreSQL
🧪 Experimental Setup
📊 Workloads Tested

🔹 Uniform Random

🔹 Sorted (worst-case for BST)

🔹 Reverse Sorted

⚙️ Operations Measured

Build / Insert

Search

📏 Methodology

High-resolution timing using std::chrono

Multiple input sizes:

n = 1000, 5000, 10000, 20000

Consistent benchmarking environment

Deterministic input generation

📉 Phase 1: BST Baseline
Runtime Scaling
n	Time (ms)
1000	0.46
5000	2.26
10000	4.25
20000	7.86
🔍 Insight

BST performs efficiently on random data but lacks structural guarantees, leading to instability.

⚔️ Phase 2: BST vs B-Tree
Key Results (n = 20000)
Structure	Workload	Insert (ms)	Search (ms)
BST	Uniform	4.02	3.36
B-Tree	Uniform	8.38	4.06
BST	Sorted	2910.98	2675.98
B-Tree	Sorted	9.79	2.92
BST	Reverse	2832.25	3148.57
B-Tree	Reverse	14.31	4.15
🔍 Insight

B-Trees provide consistent and input-independent performance, unlike BST which degrades catastrophically.

⚠️ Phase 3: Initial vEB Attempt
Observation

Fast build time

Extremely slow search (~O(n))

❌ Problem

Incorrect traversal caused linear scan behavior, defeating vEB advantages.

✅ Phase 4: Correct vEB Implementation
Fixes Applied

Proper recursive layout

Correct subtree navigation

Contiguous memory organization

📊 Final Results (n = 20000)
Structure	Workload	Build (ms)	Search (ms)
BST	Uniform	3.47	3.18
B-Tree	Uniform	8.14	3.53
vEB	Uniform	2.47	1.87
BST	Sorted	2646.21	2299.85
B-Tree	Sorted	9.91	2.64
vEB	Sorted	2.22	1.82
BST	Reverse	2831.17	2637.53
B-Tree	Reverse	10.10	2.51
vEB	Reverse	2.33	1.89
📌 Key Observations
🔹 1. BST Behavior

Fast for random input

❌ Degrades to O(n²) for sorted/reverse

Highly input-sensitive

🔹 2. B-Tree Behavior

Stable across all workloads

Handles adversarial inputs well

Slight overhead in simple cases

🔹 3. vEB Layout (Core Contribution 🚀)

🏆 Best search performance across all workloads

Cache-efficient and stable

No hardware tuning required

🔹 4. Build vs Search Trade-off

vEB has preprocessing overhead

But significantly faster search

✅ Ideal for read-heavy systems (databases, indexing engines)

📈 Visualization

All graphs generated using Python:

analysis/plots/

Includes:

Build vs Input Size

Search vs Input Size

Workload comparisons

Log-scale performance graphs

📌 Notes

Log scale highlights drastic BST degradation

Clear separation between B-Tree and vEB performance

🧠 Core Research Insight

Cache-oblivious structures (vEB) can match or outperform cache-aware structures (B-Trees) without requiring knowledge of cache size or block parameters.

🔁 Reproducibility
Compile & Run
g++ src/benchmark/runner.cpp -o runner
./runner
Generate Graphs
python3 analysis/visualize.py
🔮 Future Work

📊 Multiple-run averaging with error bars

🧠 Cache miss analysis using perf

📦 Scaling to large datasets (1e6+)

📉 Real-world distributions (Zipfian)

📄 IEEE / research paper submission

✅ Project Status

✅ BST implemented

✅ B-Tree implemented

✅ vEB implemented (correct & optimized)

✅ Benchmarking completed

✅ Visualization completed

🚀 Project is research-ready

👨‍💻 Authors

Om Karkele, Yash Kashid, Aditya Katkar, Kartik Mandhane 
VIT Pune