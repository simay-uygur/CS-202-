/**
* Title: substrings.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : header for q2
*/



#ifndef MINIMALSUBSET_H
#define MINIMALSUBSET_H

#include "HashTuple.h"
#include <cstring>
#include <algorithm>


struct HashStructure {
    long long hash1;
    long long hash2;
    int stringId;
    bool isVisited;

    HashStructure()
            : hash1(0), hash2(0), stringId(-1), isVisited(false) {}

    HashStructure(long long h1, long long h2, int id,int isVisited)
            : hash1(h1), hash2(h2), stringId(id), isVisited(isVisited) {}

};

class MinimalSubset {
public:
    MinimalSubset(int totalStrNum, char** const& charArr);
    ~MinimalSubset();
    void calculateMinSubsetAndRev(int& reverseCount, int& minSubsetCount);

private:
    long long** precomputedPowers1;
    long long** precomputedPowers2;

    long long MOD1;
    long long MOD2;
    long long BASE;

    HashStructure* hashValsAllPatterns;
    HashStructure* hashValOnePattern;

    int numOfStrings;

    char** charArrays;

    void precomputePowsAccordingBase();
    int binarySearch(long long searchHash1, long long searchHash2);

};

#endif
