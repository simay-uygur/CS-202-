/**
* Title: substrings.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : Header of rollinghash
*/

#ifndef ROLLINGHASH_H
#define ROLLINGHASH_H

#include "HashTuple.h"

class RollingHash {
public:
    RollingHash(long long base, int maxPatternLen, const char *text, int textLen);
    ~RollingHash();

    HashTuple computePatternHash(const char *pattern, int patternLen) const;
    void findMatchingHashes(int patternLen, HashTuple patternHash,int &count, const char *pattern);

private:
    void precomputePowers();
    void precomputeHashesForLengths(const char *text, int n, int minLength);
    void sortHashArrays();

    long long BASE;
    int maxLen, n;
  

    long long **powers1;
    long long **powers2;
    int** groupedCounts;
    int groupedCountsSize[6];


    HashTuple **hashArrays;
};

#endif
