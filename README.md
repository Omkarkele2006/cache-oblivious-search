# Cache-Oblivious Search Structures

## Project Title

**Design and Empirical Evaluation of Cache-Oblivious Search Structures for Modern Memory Hierarchies**

---

# 1. Objective

This project implements and evaluates:

* Binary Search Tree (BST) — cache-unaware baseline
* B-Tree — cache-aware structure
* van Emde Boas (vEB) Layout — cache-oblivious structure

### Goals:

* Analyze execution time across workloads
* Study worst-case degradation
* Evaluate memory locality (via hardware counters)

---

# 2. Tech Stack

* **C++** — Core implementation & benchmarking
* **Python (pandas, matplotlib)** — Analysis & visualization
* **Linux perf** — Hardware-level profiling
* **GitHub** — Version control & reproducibility

---

# 3. Experimental Setup

### Workloads

* Uniform Random
* Sorted (worst-case for BST)
* Reverse Sorted
* Zipfian (real-world skewed distribution)

### Operations

* Insert / Build
* Search

### Methodology

* Averaged over **NUM_RUNS = 3**
* High-resolution timing (`std::chrono`)
* Input sizes:

  * 1000
  * 5000
  * 10000
  * 20000

---

# 4. Phase 1: Initial BST Baseline

(Original baseline retained)

| n     | Time (ms) |
| ----- | --------- |
| 1000  | 0.463323  |
| 5000  | 2.26068   |
| 10000 | 4.25868   |
| 20000 | 7.86498   |

---

## Key Insight

> BST shows good average performance but is highly input-sensitive.

---

# 5. Phase 2: BST vs B-Tree

(Original comparison retained)

## Key Insight

> B-Trees provide stable performance independent of input distribution.

---

# 6. Phase 3: vEB (Incorrect Version)

## Observation

* Fast build
* Extremely slow search (~O(n))

## Insight

> Correct traversal is essential for cache-oblivious structures.

---

# 7. Phase 4: FINAL IMPLEMENTATION (Correct vEB)

---

## FINAL BENCHMARK RESULTS (UPDATED)

### n = 1000

| Structure | Workload | Insert/Build (ms) | Search (ms) |
| --------- | -------- | ----------------- | ----------- |
| BST       | Uniform  | 0.097618          | 0.0946706   |
| BTree     | Uniform  | 0.449447          | 0.119573    |
| vEB       | Uniform  | 0.0969248         | 0.0763746   |
| BST       | Sorted   | 2.21642           | 2.05894     |
| BTree     | Sorted   | 0.409438          | 0.116326    |
| vEB       | Sorted   | 0.138745          | 0.088981    |
| BST       | Reverse  | 2.14342           | 2.06351     |
| BTree     | Reverse  | 0.420263          | 0.0909904   |
| vEB       | Reverse  | 0.0859996         | 0.0684146   |

---

### n = 5000

| Structure | Workload | Insert/Build (ms) | Search (ms) |
| --------- | -------- | ----------------- | ----------- |
| BST       | Uniform  | 0.6728            | 0.551315    |
| BTree     | Uniform  | 1.80872           | 0.695893    |
| vEB       | Uniform  | 0.524477          | 0.410411    |
| BST       | Sorted   | 73.6531           | 71.2922     |
| BTree     | Sorted   | 2.09292           | 0.581324    |
| vEB       | Sorted   | 0.521857          | 0.414203    |
| BST       | Reverse  | 73.9741           | 71.2801     |
| BTree     | Reverse  | 2.17753           | 0.570374    |
| vEB       | Reverse  | 0.57127           | 0.415653    |

---

### n = 10000

| Structure | Workload | Insert/Build (ms) | Search (ms) |
| --------- | -------- | ----------------- | ----------- |
| BST       | Uniform  | 1.36547           | 1.26874     |
| BTree     | Uniform  | 3.89995           | 1.73361     |
| vEB       | Uniform  | 1.10954           | 0.873274    |
| BST       | Sorted   | 316.31            | 303.912     |
| BTree     | Sorted   | 4.16718           | 1.12075     |
| vEB       | Sorted   | 1.2534            | 0.869811    |
| BST       | Reverse  | 319.379           | 330.053     |
| BTree     | Reverse  | 4.44091           | 1.24422     |
| vEB       | Reverse  | 1.11572           | 0.872009    |

---

### n = 20000

| Structure | Workload | Insert/Build (ms) | Search (ms) |
| --------- | -------- | ----------------- | ----------- |
| BST       | Uniform  | 3.39206           | 3.03295     |
| BTree     | Uniform  | 8.06215           | 3.4171      |
| vEB       | Uniform  | 2.40194           | 1.87666     |
| BST       | Sorted   | 1293.71           | 1245        |
| BTree     | Sorted   | 8.67753           | 2.39285     |
| vEB       | Sorted   | 2.32537           | 1.85411     |
| BST       | Reverse  | 1292.53           | 1335.2      |
| BTree     | Reverse  | 9.24141           | 2.44125     |
| vEB       | Reverse  | 2.3463            | 1.85869     |

---

## Key Insight

> BST becomes **~556× slower** than vEB in worst-case (sorted input, n=20000).

---

# 8. Hardware-Level Analysis (Linux perf)

## Setup

* CPU: Intel i7-13620H
* Cores: 0–7 (P-cores only via `taskset`)
* OS: Ubuntu Live USB
* Compiler: `g++ -O2`

---

## Basic Perf Results

* Cache references: **1,670,989,444**

* Cache misses: **1,907,085**
  → **Miss rate = 0.1141%**

* Cycles: **143,124,472,767**

* Instructions: **167,331,592,852**
  → **IPC = 1.1689**

---

## Detailed Cache Analysis

* L1 loads: **77,437,458,197**

* L1 misses: **10,245,760,539**
  → **L1 miss rate = 13.23%**

* LLC loads: **151,654,922**

* LLC misses: **820,982**
  → **LLC miss rate = 0.541%**

---

## Topdown Analysis

* Backend bound: **71.9%**
* Frontend bound: **4.2%**
* Bad speculation: **1.9%**
* Retiring: **22.0%**

---

## Key Insight

> Despite moderate L1 misses, extremely low LLC misses confirm strong spatial locality and effective cache utilization.

---

# 9. Graphical Analysis

Generated using Python (pandas + matplotlib):

* Search Time vs n
* Build Time vs n
* Worst-case comparison
* Log-scale performance
* Zipfian workload performance graphs
* Memory usage comparison graph

---

## Observations

### Uniform Case

* BST competitive
* B-Tree slower due to overhead
* vEB fastest

### Worst Case (Sorted)

* BST collapses (O(n²))
* B-Tree stable
* vEB best

---

# 10. Core Research Insight

> Cache-oblivious layouts (vEB) achieve performance comparable to or better than cache-aware structures (B-Trees), without requiring explicit knowledge of cache parameters.

---
# 11. Contributions

This work provides:

- A complete empirical comparison of cache-unaware, cache-aware, and cache-oblivious search structures
- Evaluation across uniform, worst-case, and real-world (Zipfian) workloads
- Hardware-level analysis using Linux perf
- Large-scale validation up to 1e6 elements
- Memory footprint analysis across structures
---

# 12. Extended Large-Scale Results (1e6+)

## Uniform Workload (n = 1,000,000)

| Structure | Insert/Build (ms) | Search (ms) |
| --------- | ----------------- | ----------- |
| BST       | **595.931**       | **387.885** |
| B-Tree    | **523.762**       | **488.243** |
| vEB       | **21.7166**       | **39.1822** |

---

## Key Observations

* vEB vs BST (search):

  **387.885 / 39.1822 = 9.90×**

* vEB vs B-Tree (search):

  **488.243 / 39.1822 = 12.46×**

*vEB is ~10× faster than BST and ~12× faster than B-Tree at n = 1e6*

---

## Mid-scale Comparison (n = 100,000)

| Structure | Insert (ms) | Search (ms) |
| --------- | ----------- | ----------- |
| BST       | **17.5559** | **9.82753** |
| B-Tree    | **19.9674** | **14.4764** |
| vEB       | **1.60513** | **3.49173** |

---

## Worst Case (Sorted Input, n = 100,000)

| Structure | Insert (ms) | Search (ms) |
| --------- | ----------- | ----------- |
| BST       | **23472.8** | **16194.8** |
| B-Tree    | **9.93296** | **5.2148**  |
| vEB       | **1.80457** | **3.73268** |

---

## Critical Insight

* BST exhibits **catastrophic degradation** under sorted input
* Insert time reaches **23.47 seconds** at n = 100,000
* vEB remains under **2 ms build time**

Demonstrates clear **O(n²) vs cache-efficient behavior**

---

## Scaling Trend (Uniform Workload)

| n       | BST Search (ms) | B-Tree Search (ms) | vEB Search (ms) |
| ------- | --------------- | ------------------ | --------------- |
| 1000    | 0.0226253       | 0.042079           | 0.0231647       |
| 10000   | 0.407557        | 0.708169           | 0.298706        |
| 100000  | 9.82753         | 14.4764            | 3.49173         |
| 1000000 | 387.885         | 488.243            | 39.1822         |

---

## Final Scaling Insight

> Performance gap widens significantly with increasing input size, demonstrating the growing importance of cache locality at scale.

---

## Experimental Notes

* BST worst-case (sorted/reverse) skipped beyond **n = 100,000**
* Reason: O(n²) behavior leads to impractical runtimes

---

## Combined Hardware + Scaling Insight

> Low LLC miss rates combined with vEB’s recursive layout enable superior cache utilization, which becomes increasingly beneficial as dataset size grows.

---

# 13. Extended Real-World Evaluation (Zipfian Distribution)

## Zipfian Workload (Real-World Skewed Data)

Zipfian distribution models real-world scenarios where a small subset of values appears very frequently while the majority appear rarely.

---

## Large-Scale Results (n = 1,000,000)

| Structure | Insert/Build (ms) | Search (ms) |
| --------- | ----------------- | ----------- |
| BST       | **169890**        | **137.559** |
| B-Tree    | **404.319**       | **229.139** |
| vEB       | **22.194**        | **20.1526** |

---

## Key Observations

* BST vs vEB (Insert):

  **169890 / 22.194 ≈ 7650×**

* BST vs B-Tree (Insert):

  **169890 / 404.319 ≈ 420×**

*BST becomes extremely inefficient under skewed distributions*

---

## Mid-scale Behavior (n = 100,000)

| Structure | Insert (ms) | Search (ms) |
| --------- | ----------- | ----------- |
| BST       | **761.028** | **6.166**   |
| B-Tree    | **20.4865** | **8.5781**  |
| vEB       | **1.9416**  | **1.88322** |

---

## Scaling Trend (Zipfian Insert)

| n       | BST Insert (ms) | B-Tree Insert (ms) | vEB Build (ms) |
| ------- | --------------- | ------------------ | -------------- |
| 10000   | 5.09667         | 1.28486            | 0.175232       |
| 50000   | 144.599         | 8.9597             | 0.957693       |
| 100000  | 761.028         | 20.4865            | 1.9416         |
| 200000  | 3327.99         | 49.798             | 4.17436        |
| 500000  | 31019.3         | 157.319            | 11.7928        |
| 1000000 | 169890          | 404.319            | 22.194         |

---

## Key Insight

> Zipfian distributions amplify structural imbalance in BSTs due to repeated key insertions, leading to severe performance degradation, while B-Trees and cache-oblivious vEB layouts remain stable.

---

## Combined Insight (All Workloads)

| Workload | BST              | B-Tree | vEB  |
| -------- | ---------------- | ------ | ---- |
| Uniform  | Good             | Stable | Best |
| Sorted   | Worst (O(n²))    | Stable | Best |
| Zipfian  | Degrades heavily | Stable | Best |

---

## Final Research Insight

> Cache-oblivious vEB layouts consistently outperform both cache-unaware BSTs and cache-aware B-Trees across uniform, worst-case, and real-world (Zipfian) workloads, with performance advantages becoming dramatically more pronounced at scale.

---
# 14. Memory Footprint Analysis

## Memory Usage Across Structures

Memory usage was estimated analytically based on structural design:

* BST: pointer-based nodes (high overhead)
* B-Tree: partially compact node structure
* vEB: contiguous array-based layout

---

## Results

| n       | BST (bytes)  | B-Tree (bytes) | vEB (bytes) |
| ------- | ------------ | -------------- | ----------- |
| 1000    | **20000**    | **8000**       | **4000**    |
| 10000   | **200000**   | **80000**      | **40000**   |
| 100000  | **2000000**  | **800000**     | **400000**  |
| 1000000 | **20000000** | **8000000**    | **4000000** |

---

## Key Observations

* BST uses **5× more memory than vEB**
* B-Tree uses **2× more memory than vEB**
* Memory grows linearly with input size for all structures

---

## Insight

> Pointer-heavy structures like BST incur significant memory overhead due to node allocations and pointers, whereas cache-oblivious layouts such as vEB achieve compact memory representation through contiguous storage.

---

## Implication

* Lower memory footprint → better cache utilization
* Better cache utilization → faster performance

Explains why **vEB outperforms BST and B-Tree at scale**

---

# 15. Reproducibility

```bash
g++ src/benchmark/runner.cpp -o runner
./runner

taskset -c 0-7 perf stat ./runner
taskset -c 0-7 perf stat -d ./runner
```

---

# 16. Status

* BST implemented
* B-Tree implemented
* vEB implemented (correct)
* Benchmarking complete
* Hardware profiling complete
* Graphs generated
* Large-scale evaluation (1e6) complete
* Zipfian (real-world distribution) analysis complete


---

# 17. Future Work

* Parallel benchmarking
* Cache-line level analysis
* NUMA-aware evaluation
* Paper submission

