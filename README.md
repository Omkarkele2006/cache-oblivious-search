# Cache-Oblivious Search Structures

## Project Title
Design and Empirical Evaluation of Cache-Oblivious Search Structures for Modern Memory Hierarchies

---

## Objective
This project aims to implement and empirically evaluate cache-oblivious data structures (e.g., van Emde Boas layouts) and compare them against traditional structures like Binary Search Trees (BST) and B-Trees.

The focus is on:
- Execution time
- Cache efficiency (later phase)
- Performance under different data distributions

---

## Tech Stack
- C++ (Core data structures and benchmarking)
- Python (Analysis & visualization)
- SQLite/PostgreSQL (Data storage - upcoming)
- Linux perf (Hardware counters - upcoming)

---

## Experimental Setup (Phase 1)

### Workloads Tested
- Uniform Random
- Sorted (worst-case)
- Reverse Sorted (worst-case)

### Operations
- Insert
- Search

### Methodology
- Multiple runs averaged (NUM_RUNS = 5)
- High-resolution timing (std::chrono)

---

## Results (BST Baseline)

### Key Observations

1. **Uniform Workload**
   - Near O(n log n) behavior
   - Balanced tree structure

2. **Sorted / Reverse Workloads**
   - Severe degradation in performance
   - Tree becomes skewed (linked-list-like)

3. **Performance Explosion**

| n | Uniform (ms) | Sorted (ms) |
|--|-------------|------------|
| 1,000 | ~0.17 | ~8.3 |
| 5,000 | ~0.82 | ~217 |
| 10,000 | ~2.2 | ~914 |
| 20,000 | ~5.0 | ~4200 |

---

## Insight

These results demonstrate that:

> Traditional BSTs are highly sensitive to input distribution and suffer catastrophic performance degradation under adversarial inputs.

This motivates the need for:
- Cache-aware structures
- Cache-oblivious layouts (vEB)

---

## Next Steps

- Implement B-Tree (cache-aware baseline)
- Implement van Emde Boas layout
- Integrate hardware performance counters (cache misses)
- Perform comparative analysis

---

## Status

✅ Baseline BST implemented  
✅ Benchmarking pipeline ready  
✅ Multi-workload evaluation complete  
🚧 Cache-aware & cache-oblivious structures (in progress)