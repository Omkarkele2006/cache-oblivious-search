#!/bin/bash

echo "Running benchmarks..."

./build/runner > experiments/results/output.csv

echo "Results saved to experiments/results/output.csv"