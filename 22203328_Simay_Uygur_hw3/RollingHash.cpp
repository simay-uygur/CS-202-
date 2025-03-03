/**
* Title: substrings.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description :header for q1
*/

#include "RollingHash.h"
#include <algorithm>

const long long MOD1 = 1e9 + 7;  //global variable okey mi
const long long MOD2 = 1e9 + 9;

RollingHash::RollingHash(long long base, int maxPatternLen, const char *text, int textLen)
        : BASE(base), maxLen(maxPatternLen), n(textLen), groupedCounts(nullptr){  //, text(text)

    powers1 = new long long *[4];
    powers2 = new long long *[4];
    for (int i = 0; i < 4; ++i) {
        powers1[i] = new long long[maxLen];
        powers2[i] = new long long[maxLen];
    }

    precomputePowers();
    precomputeHashesForLengths(text, n, maxPatternLen - 5);
    sortHashArrays();
}

RollingHash::~RollingHash() {
    for (int i = 0; i < 4; ++i) {
        delete[] powers1[i];
        delete[] powers2[i];
    }
    delete[] powers1;
    delete[] powers2;

    for (int i = 0; i < 6; ++i) {
        delete[] hashArrays[i];
    }
    delete[] hashArrays;
}

void RollingHash::precomputePowers() {

    for (int i = 0; i < 4; ++i) {
        powers1[i][0] = i + 1;
        powers2[i][0] = i + 1;
    }


    for (int j = 1; j < maxLen; ++j) {
        for (int i = 0; i < 4; ++i) {
            powers1[i][j] = (powers1[i][j - 1] * BASE) % MOD1;
            powers2[i][j] = (powers2[i][j - 1] * BASE) % MOD2;
        }
    }
}

void RollingHash::precomputeHashesForLengths(const char *text, int n, int minLength) {   // copying olur mu
    const int range = 6;
    hashArrays = new HashTuple *[range];

    for (int offset = 0; offset < range; ++offset) {
        int len = minLength + offset;
        hashArrays[offset] = new HashTuple[n - len + 1];


        HashTuple hash(0, 0);
        for (int i = 0; i < len; ++i) {
            int charValue = text[i] - 'a';
            hash.hash1 = (hash.hash1 + powers1[charValue][len - i - 1]) % MOD1;
            hash.hash2 = (hash.hash2 + powers2[charValue][len - i - 1]) % MOD2;
        }
        hashArrays[offset][0] = hash;


        for (int i = 1; i <= n - len; ++i) {
            HashTuple prevHash = hashArrays[offset][i - 1];

            int leftCharValue = text[i - 1] - 'a';
            prevHash.hash1 = (prevHash.hash1 - powers1[leftCharValue][len - 1] + MOD1) % MOD1;
            prevHash.hash2 = (prevHash.hash2 - powers2[leftCharValue][len - 1] + MOD2) % MOD2;

            int rightCharValue = text[i + len - 1] - 'a';
            prevHash.hash1 = (prevHash.hash1 * BASE % MOD1 + powers1[rightCharValue][0]) % MOD1;
            prevHash.hash2 = (prevHash.hash2 * BASE % MOD2 + powers2[rightCharValue][0]) % MOD2;

            hashArrays[offset][i] = prevHash;
        }
    }
}


void RollingHash::sortHashArrays() {
    for (int i = 0; i < 6; ++i) {
        int size = n - (maxLen - 5 + i) + 1;

        std::sort(hashArrays[i], hashArrays[i] + size,
                  [](const HashTuple &a, const HashTuple &b) {
                      return a.hash1 < b.hash1 || (a.hash1 == b.hash1 && a.hash2 < b.hash2);    // hope it is correct- - hoca dedi ekle diye eşitlik durumunu
                  });


        int groupCount = 0;
        HashTuple *groupedHashes = new HashTuple[size];
        int *counts = new int[size];

        HashTuple currentHash = hashArrays[i][0];
        int count = 1;

        for (int j = 1; j < size; ++j) {
            if (hashArrays[i][j].hash1 == currentHash.hash1 && hashArrays[i][j].hash2 == currentHash.hash2) {
                count++;
            } else {
                groupedHashes[groupCount] = currentHash;
                counts[groupCount] = count;
                groupCount++;

                currentHash = hashArrays[i][j];
                count = 1;
            }
        }


        groupedHashes[groupCount] = currentHash;
        counts[groupCount] = count;
        groupCount++;


        delete[] hashArrays[i];
        hashArrays[i] = new HashTuple[groupCount];
        groupedCountsSize[i] = groupCount;
        for (int j = 0; j < groupCount; ++j) {
            hashArrays[i][j] = groupedHashes[j];
        }


        if (groupedCounts == nullptr) {
            groupedCounts = new int *[6];
        }
        groupedCounts[i] = new int[groupCount];
        for (int j = 0; j < groupCount; ++j) {
            groupedCounts[i][j] = counts[j];
        }

        delete[] groupedHashes;
        delete[] counts;
    }
}

HashTuple RollingHash::computePatternHash(const char *pattern, int patternLen) const {
    HashTuple patternHash(0, 0);
    for (int i = 0; i < patternLen; ++i) {
        int charValue = pattern[i] - 'a';
        patternHash.hash1 = (patternHash.hash1 + powers1[charValue][patternLen - i - 1]) % MOD1;
        patternHash.hash2 = (patternHash.hash2 + powers2[charValue][patternLen - i - 1]) % MOD2;
    }
    return patternHash;
}



void RollingHash::findMatchingHashes(int patternLen, HashTuple patternHash, int &count, const char *pattern) {
    if (patternLen > maxLen || patternLen < 1) {
        count = 0;
        return;
    }

    int ind = patternLen - (maxLen - 5);
    HashTuple *const &hashArray = hashArrays[ind];
    int *const &counts = groupedCounts[ind];
    int numGroups = groupedCountsSize[ind];


    int left = 0, right = numGroups - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (hashArray[mid].hash1 < patternHash.hash1) {
            left = mid + 1;
        } else if (hashArray[mid].hash1 > patternHash.hash1) {
            right = mid - 1;
        } else {

            if (hashArray[mid].hash2 == patternHash.hash2) {

                count = counts[mid];
                return;
            } else if (hashArray[mid].hash2 < patternHash.hash2) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    count = 0;
}


