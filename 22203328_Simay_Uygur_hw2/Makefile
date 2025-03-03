

CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: least5 game subarray prefixsubarray

least5: least5.cpp Heap.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

game: game.cpp CardGame.cpp BST.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

subarray: subarray.cpp SubArrPlay.cpp Heap.cpp MaxHeap.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

prefixsubarray: prefixsubarray.cpp PrefixArrPlay.cpp Heap.cpp MaxHeap.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f least5 game subarray prefixsubarray

.PHONY: all clean
