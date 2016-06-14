# Makefile for subroutine

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -march=native -fopenmp -fno-omit-frame-pointer -O2
CAIROFLAGS = `pkg-config --cflags --libs cairo`
BINS = subroutine

$(BINS): $(BINS).cpp
	$(CXX) $(CXXFLAGS) $(CAIROFLAGS) -o $(BINS) $(BINS).cpp
	./subroutine

clean:
	rm -Rf $(BINS)

