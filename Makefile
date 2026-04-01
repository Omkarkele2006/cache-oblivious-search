CXX = g++
CXXFLAGS = -O2 -march=native

SRC = src/benchmark/runner.cpp
OUT = runner

all:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)