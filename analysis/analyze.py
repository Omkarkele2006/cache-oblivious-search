import pandas as pd
import matplotlib.pyplot as plt

# Load data
df = pd.read_csv("../results/results.csv")

df['structure'] = df['structure'].str.strip()

# Separate
search_df = df[df['operation'] == 'search']
insert_df = df[df['operation'].isin(['insert', 'build'])]

search_mean = search_df.groupby(['structure', 'n', 'workload'])['time_ms'].mean().reset_index()
insert_mean = insert_df.groupby(['structure', 'n', 'workload'])['time_ms'].mean().reset_index()

# Helper function
def plot_graph(data, workload, ylabel, title, filename, log=False):
    plt.figure(figsize=(8,5))

    for structure in data['structure'].unique():
        subset = data[(data['structure'] == structure) & (data['workload'] == workload)]
        if not subset.empty:
            plt.plot(subset['n'], subset['time_ms'], marker='o', label=structure)

    if log:
        plt.yscale('log')

    plt.xlabel("Input Size (n)")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.legend()
    plt.savefig(f"plots/{filename}")
    plt.close()

# -------------------------------
# 📊 UNIFORM
# -------------------------------
plot_graph(search_mean, "uniform", "Search Time (ms)", "Search Performance (Uniform)", "search_uniform.png")
plot_graph(insert_mean, "uniform", "Insert/Build Time (ms)", "Build Performance (Uniform)", "build_uniform.png")

# -------------------------------
# 📊 SORTED (Worst Case)
# -------------------------------
plot_graph(search_mean, "sorted", "Search Time (ms)", "Worst Case (Sorted Input)", "search_sorted.png")

# -------------------------------
# 📊 ZIPFIAN (NEW 🔥)
# -------------------------------
plot_graph(search_mean, "zipfian", "Search Time (ms)", "Search Performance (Zipfian)", "search_zipfian.png")
plot_graph(insert_mean, "zipfian", "Insert/Build Time (ms)", "Build Performance (Zipfian)", "build_zipfian.png")

# -------------------------------
# 📊 LOG SCALE (Uniform)
# -------------------------------
plot_graph(search_mean, "uniform", "Search Time (log ms)", "Search Performance (Log Scale)", "search_log.png", log=True)

# -------------------------------
# 📊 LOG SCALE (Zipfian 🔥)
# -------------------------------
plot_graph(search_mean, "zipfian", "Search Time (log ms)", "Search Performance (Zipfian Log Scale)", "search_zipfian_log.png", log=True)

print("All graphs (including Zipfian) generated successfully!")

# -------------------------------
# 📊 MEMORY ANALYSIS (NEW 🔥)
# -------------------------------
