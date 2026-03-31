import pandas as pd
import matplotlib.pyplot as plt
import os

# ================= LOAD DATA =================
df = pd.read_csv("results/results.csv")

# ================= PROCESS =================
# Group and compute mean + std
grouped = df.groupby(["structure", "workload", "n", "operation"])

stats = grouped["time_ms"].agg(["mean", "std"]).reset_index()

# Save processed data
os.makedirs("data/processed", exist_ok=True)
stats.to_csv("data/processed/summary.csv", index=False)

print("✅ Summary saved to data/processed/summary.csv")

# ================= PLOTTING =================
os.makedirs("analysis/plots", exist_ok=True)

structures = stats["structure"].unique()
workloads = stats["workload"].unique()

# -------- Plot: Search Performance --------
for workload in workloads:
    plt.figure()

    for structure in structures:
        subset = stats[
            (stats["workload"] == workload) &
            (stats["structure"] == structure) &
            (stats["operation"] == "search")
        ]

        plt.errorbar(
            subset["n"],
            subset["mean"],
            yerr=subset["std"],
            label=structure,
            marker='o'
        )

    plt.title(f"Search Performance ({workload})")
    plt.xlabel("Input Size (n)")
    plt.ylabel("Time (ms)")
    plt.yscale("log") 
    plt.legend()
    plt.grid()

    filename = f"analysis/plots/search_{workload}.png"
    plt.savefig(filename)
    plt.close()

    print(f"📊 Saved: {filename}")

# -------- Plot: Build/Insert Performance --------
for workload in workloads:
    plt.figure()

    for structure in structures:
        op = "build" if structure == "vEB" else "insert"

        subset = stats[
            (stats["workload"] == workload) &
            (stats["structure"] == structure) &
            (stats["operation"] == op)
        ]

        plt.errorbar(
            subset["n"],
            subset["mean"],
            yerr=subset["std"],
            label=structure,
            marker='o'
        )

    plt.title(f"Build/Insert Performance ({workload})")
    plt.xlabel("Input Size (n)")
    plt.ylabel("Time (ms)")
    plt.yscale("log")
    plt.legend()
    plt.grid()

    filename = f"analysis/plots/build_{workload}.png"
    plt.savefig(filename)
    plt.close()

    print(f"📊 Saved: {filename}")