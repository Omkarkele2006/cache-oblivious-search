# Cache-Oblivious Search Structures

## Project Title

**Design and Empirical Evaluation of Cache-Oblivious Search Structures for Modern Memory Hierarchies**

---

## 1. Objective

This project implements and evaluates:

* Binary Search Tree (BST) — cache-unaware baseline
* B-Tree — cache-aware structure
* van Emde Boas (vEB) Layout — cache-oblivious structure

The goal is to analyze:

* Execution time
* Sensitivity to input distribution
* Memory locality effects (implicit)

---

## 2. Tech Stack

* **C++** — Core implementation & benchmarking
* **Python** — Analysis & visualization (next phase)
* **SQLite/PostgreSQL** — (planned)
* **Linux perf** — (planned)

---

## 3. Experimental Setup

### Workloads

* Uniform Random
* Sorted (worst-case for BST)
* Reverse Sorted

### Operations

* Insert
* Search

### Methodology

* Averaged over multiple runs
* High-resolution timing using `std::chrono`

---

# 4. Phase 1: Initial BST Baseline

### Simple Runtime Benchmark

| n     | Time (ms) |
| ----- | --------- |
| 1000  | 0.463323  |
| 5000  | 2.26068   |
| 10000 | 4.25868   |
| 20000 | 7.86498   |

---

### Insert vs Search

| n     | Insert (ms) | Search (ms) |
| ----- | ----------- | ----------- |
| 1000  | 0.131949    | 0.120668    |
| 5000  | 0.797756    | 0.895085    |
| 10000 | 1.85798     | 1.20646     |
| 20000 | 3.82578     | 2.99528     |

---

### Multi-Workload BST Results

#### n = 20000

| Workload | Insert (ms) | Search (ms) |
| -------- | ----------- | ----------- |
| Uniform  | 5.09059     | 4.48164     |
| Sorted   | 4226.86     | 4407.16     |
| Reverse  | 4541.11     | 4293.66     |

---

## Key Insight

> BST exhibits catastrophic performance degradation (O(n²)) under adversarial inputs.

---

# 5. Phase 2: BST vs B-Tree

### Full Results (Extract)

#### n = 20000

| Structure | Workload | Insert (ms) | Search (ms) |
| --------- | -------- | ----------- | ----------- |
| BST       | Uniform  | 4.02506     | 3.3665      |
| BTree     | Uniform  | 8.38907     | 4.06717     |
| BST       | Sorted   | 2910.98     | 2675.98     |
| BTree     | Sorted   | 9.7933      | 2.92398     |
| BST       | Reverse  | 2832.25     | 3148.57     |
| BTree     | Reverse  | 14.3195     | 4.15346     |

---

## Key Insight

> B-Trees provide robust performance independent of input distribution.

---

# 6. Phase 3: Initial vEB (Incorrect Navigation)

### Observation

* Build time: fast
* Search time: extremely high (O(n))

Example (n = 20000):

| Structure | Search (ms)   |
| --------- | ------------- |
| vEB       | ~2400–2900 ms |

---

## Insight

> vEB layout without correct navigation degenerates to linear scan.

---

# 7. Phase 4: Correct vEB Implementation (Final)

### (With subtree metadata + correct traversal)

---

## FINAL RESULTS

### n = 1000

| Structure | Workload | Insert/Build (ms) | Search (ms) |
| --------- | -------- | ----------------- | ----------- |
| BST       | Uniform  | 0.0805            | 0.0733      |
| BTree     | Uniform  | 0.3424            | 0.0949      |
| vEB       | Uniform  | 0.7812            | 0.0611      |
| BST       | Sorted   | 4.794             | 4.536       |
| BTree     | Sorted   | 0.361             | 0.082       |
| vEB       | Sorted   | 0.074             | 0.061       |

---

### n = 5000

| Structure | Workload | Insert/Build (ms) | Search (ms) |
| --------- | -------- | ----------------- | ----------- |
| BST       | Uniform  | 0.642             | 0.539       |
| BTree     | Uniform  | 1.746             | 0.601       |
| vEB       | Uniform  | 0.431             | 0.336       |
| BST       | Sorted   | 133.784           | 132.46      |
| BTree     | Sorted   | 1.965             | 0.515       |
| vEB       | Sorted   | 0.430             | 0.340       |

---

### n = 10000

| Structure | Workload | Insert/Build (ms) | Search (ms) |
| --------- | -------- | ----------------- | ----------- |
| BST       | Uniform  | 1.664             | 1.275       |
| BTree     | Uniform  | 3.614             | 1.426       |
| vEB       | Uniform  | 0.916             | 0.758       |
| BST       | Sorted   | 554.738           | 545.747     |
| BTree     | Sorted   | 3.940             | 1.028       |
| vEB       | Sorted   | 0.989             | 0.717       |

---

### n = 20000

| Structure | Workload | Insert/Build (ms) | Search (ms) |
| --------- | -------- | ----------------- | ----------- |
| BST       | Uniform  | 3.474             | 3.185       |
| BTree     | Uniform  | 8.146             | 3.530       |
| vEB       | Uniform  | 2.475             | 1.876       |
| BST       | Sorted   | 2646.21           | 2299.85     |
| BTree     | Sorted   | 9.911             | 2.640       |
| vEB       | Sorted   | 2.220             | 1.827       |
| BST       | Reverse  | 2831.17           | 2637.53     |
| BTree     | Reverse  | 10.102            | 2.513       |
| vEB       | Reverse  | 2.335             | 1.897       |

---

# 8. Final Analysis

## Observations

### 1. Uniform Workload

* BST is competitive
* B-Tree slightly slower
* vEB achieves best search time

---

### 2. Adversarial Inputs

* BST collapses (O(n²))
* B-Tree remains stable
* vEB remains stable and faster

---

### 3. Cache Behavior Insight

| Structure | Memory Pattern              |
| --------- | --------------------------- |
| BST       | Pointer chasing             |
| B-Tree    | Block-based                 |
| vEB       | Contiguous recursive layout |

---

## 🔥 Core Research Insight

> Cache-oblivious layouts (vEB) achieve performance comparable to or better than cache-aware structures (B-Trees) without requiring knowledge of cache parameters.

---

# 9. Conclusion

* BST is highly input-sensitive
* B-Tree is robust and cache-aware
* vEB provides:

  * superior locality
  * stable performance
  * cache-oblivious design

---

# 10. Reproducibility

```bash
g++ src/benchmark/runner.cpp -o runner
./runner
```

---

# 11. Future Work

* Hardware counters (cache misses via perf)
* Zipfian distributions
* Larger datasets (1e6+)
* Python-based visualization
* Paper submission

---

# 12. Status

✅ BST implemented
✅ B-Tree implemented
✅ vEB implemented (correct)
✅ Full benchmarking complete
🚀 Ready for analysis + paper writing

---
