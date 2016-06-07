# Makefile for subroutine

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -march=native -fopenmp -fno-omit-frame-pointer -O2
CAIROFLAGS = `pkg-config --cflags --libs cairo`
BINS = subroutine

subroutine: subroutine 
	$(CXX) $(CXXFLAGS) $(CAIROFLAGS) -o subroutine subroutine.cpp
	./subroutine

clean:
	rm -Rf $(BINS)

