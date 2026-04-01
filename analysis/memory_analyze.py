import pandas as pd
import matplotlib.pyplot as plt

mem_df = pd.read_csv("../results/memory_results.csv")

plt.figure(figsize=(8,5))

for structure in mem_df['structure'].unique():
    subset = mem_df[mem_df['structure'] == structure]
    plt.plot(subset['n'], subset['memory_bytes'], marker='o', label=structure)

plt.xlabel("Input Size (n)")
plt.ylabel("Memory Usage (bytes)")
plt.title("Memory Footprint Comparison")
plt.grid(True)
plt.legend()
plt.savefig("plots/memory_usage.png")
plt.close()

print("Memory graph generated!")