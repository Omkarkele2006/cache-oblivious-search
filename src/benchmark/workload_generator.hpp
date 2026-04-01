#ifndef WORKLOAD_GENERATOR_HPP
#define WORKLOAD_GENERATOR_HPP

#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

class WorkloadGenerator {
public:

    // ================= ZIPFIAN =================
    static std::vector<int> generate_zipfian(int n, double s = 1.0) {
        std::vector<int> data;
        data.reserve(n);

        std::mt19937 gen(42);

        std::vector<double> probs(n);
        double sum = 0.0;

        for (int i = 1; i <= n; i++) {
            probs[i - 1] = 1.0 / std::pow(i, s);
            sum += probs[i - 1];
        }

        for (int i = 0; i < n; i++) {
            probs[i] /= sum;
        }

        std::discrete_distribution<int> dist(probs.begin(), probs.end());

        for (int i = 0; i < n; i++) {
            data.push_back(dist(gen));
        }

        return data;
    }

    // ================= UNIFORM =================
    static std::vector<int> generate_uniform(int n, int min = 1, int max = 1000000) {
        std::vector<int> data;
        data.reserve(n);

        std::mt19937 gen(42);
        std::uniform_int_distribution<> dist(min, max);

        for (int i = 0; i < n; ++i) {
            data.push_back(dist(gen));
        }

        return data;
    }

    // ================= SORTED =================
    static std::vector<int> generate_sorted(int n) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            data[i] = i;
        }
        return data;
    }

    // ================= REVERSE =================
    static std::vector<int> generate_reverse_sorted(int n) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            data[i] = n - i;
        }
        return data;
    }
};

#endif