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
---

## Comparative Results: BST vs B-Tree

### Key Findings

1. **Uniform Workload**
   - BST performs slightly faster due to lower overhead
   - B-Tree introduces additional cost from node management

2. **Adversarial Workloads (Sorted / Reverse)**

   - BST shows catastrophic degradation:
     - O(n²) behavior
     - Extremely high latency

   - B-Tree remains stable:
     - O(n log n)
     - Consistent performance

### Example (n = 20000)

| Structure | Insert Time |
|----------|------------|
| BST (sorted) | ~2910 ms |
| B-Tree (sorted) | ~9.7 ms |

### Insight

> B-Trees are significantly more robust to input distribution and provide stable performance across workloads, making them suitable for memory-hierarchy-aware systems.

---

## Conclusion (Current Phase)

- BST is efficient only under favorable conditions
- B-Tree provides:
  - structural balance
  - input robustness
  - improved memory locality

This establishes a strong baseline for evaluating **cache-oblivious structures (vEB layout)** in the next phase.
---

## Cache-Oblivious (vEB) Observations

### Key Findings

1. **Build Performance**
   - vEB layout construction is efficient and scales well
   - Comparable or faster than BST and B-Tree insertion

2. **Search Performance**
   - Current implementation uses linear search (O(n))
   - Results do not reflect true vEB theoretical performance

3. **Interpretation**

> The observed slowdown in vEB search is due to the simplified implementation and not an inherent limitation of the vEB layout.

4. **Research Insight**

- vEB layout improves spatial locality
- Eliminates dependency on cache parameters
- Provides a strong foundation for cache-efficient search structures

---

## Final Insight

| Structure | Strength |
|----------|--------|
| BST | Simple, fast for random input |
| B-Tree | Robust, cache-aware |
| vEB | Cache-oblivious, layout-optimized |

---