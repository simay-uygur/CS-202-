CXX = g++
CXXFLAGS = -std=c++11 -Wall
CXXFLAGS = -std=c++11 -Wall -g   # For debugging
# or
CXXFLAGS = -std=c++11 -Wall -O2 # For optimization


all: substrings minimalset documents lexicographic insertionorders

substrings: substrings.cpp RollingHash.cpp HashTuple.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

minimalset: minimalset.cpp MinimalSubset.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

documents: documents.cpp DocumentHash.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
lexicographic: lexicographic.cpp LexicographicHash.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
insertionorders: insertionorders.cpp InsOrders.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
clean:
	rm -f substrings minimalset documents lexicographic insertionorders

.PHONY: all clean
