/**
* Title: substrings.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : class for q2
*/

#include "MinimalSubset.h"
#include <algorithm>
#include <iostream>


MinimalSubset::MinimalSubset(int totalStrNum, char** const& charArr) {
    numOfStrings = totalStrNum;
    charArrays = charArr;

    precomputedPowers1 = new long long*[26];
    precomputedPowers2 = new long long*[26];
    for (int i = 0; i < 26; ++i) {
        precomputedPowers1[i] = new long long[100005]();
        precomputedPowers2[i] = new long long[100005]();
    }

    hashValOnePattern = new HashStructure[100005]();
    hashValsAllPatterns = new HashStructure[numOfStrings]();

    MOD1 = 1e9 + 7;
    MOD2 = 1e9 + 9;
    BASE = 31;

    precomputePowsAccordingBase();

    for (int j = 0; j < numOfStrings; ++j) {
        int patternLen = static_cast<int>(strlen(charArr[j]));
        char* pattern = charArr[j];

        HashStructure patternHash;
        for (int i = 0; i < patternLen; ++i) {
            int charValue = pattern[i] - 'a';

            if (charValue < 0 || charValue >= 26) {
                throw std::invalid_argument("Invalid character in input string.");
            }
            patternHash.hash1 = (patternHash.hash1 + precomputedPowers1[charValue][patternLen - i - 1]) % MOD1;
            patternHash.hash2 = (patternHash.hash2 + precomputedPowers2[charValue][patternLen - i - 1]) % MOD2;
        }

        hashValsAllPatterns[j] = HashStructure(patternHash.hash1, patternHash.hash2, j, false);

    }

    std::sort(hashValsAllPatterns, hashValsAllPatterns + numOfStrings,
              [](const HashStructure& a, const HashStructure& b) {
                  return a.hash1 < b.hash1 || (a.hash1 == b.hash1 && a.hash2 < b.hash2);
              });

}


MinimalSubset::~MinimalSubset() {

        delete[] hashValsAllPatterns;
        hashValsAllPatterns = nullptr;
        delete[] hashValOnePattern;
        hashValOnePattern = nullptr;


    for (int i = 0; i < 26; ++i) {
        delete[] precomputedPowers1[i];
        delete[] precomputedPowers2[i];
    }
    delete[] precomputedPowers1;
    delete[] precomputedPowers2;
}


void MinimalSubset::calculateMinSubsetAndRev(int &reverseCount, int &minSubsetCount) {
    reverseCount = 0;
    minSubsetCount = 0;

    for (int i = 0; i < numOfStrings; ++i) {
        HashStructure currentHash = hashValsAllPatterns[i];
        int index = currentHash.stringId;

        if(currentHash.isVisited) continue;

        hashValOnePattern[0].hash1 = currentHash.hash1;
        hashValOnePattern[0].hash2 = currentHash.hash2;

        char *pattern = charArrays[index];
        int patternLen = static_cast<int>(strlen(pattern));

        HashStructure patternHash = currentHash;

        int leftpointer = 0 ;
        int modulo = patternLen;

        for (int j = 1; j < patternLen; ++j) {
            int leftCharValue = pattern[leftpointer] - 'a' ;
            patternHash.hash1 = (patternHash.hash1 - precomputedPowers1[leftCharValue][patternLen - 1] + MOD1) % MOD1;
            patternHash.hash2 = (patternHash.hash2 - precomputedPowers2[leftCharValue][patternLen - 1] + MOD2) % MOD2;


            patternHash.hash1 = ((patternHash.hash1 * BASE) % MOD1 + precomputedPowers1[leftCharValue][0]) % MOD1;
            patternHash.hash2 = ((patternHash.hash2 * BASE) % MOD2 + precomputedPowers2[leftCharValue][0]) % MOD2;

            hashValOnePattern[j].hash1 = patternHash.hash1;
            hashValOnePattern[j].hash2 = patternHash.hash2;

            leftpointer = (leftpointer + 1) % modulo;
        }

        patternHash.hash1 = 0;
        patternHash.hash2 = 0;

        for (int j = 0; j < patternLen; ++j) {
            int charValue = pattern[j] - 'a' ;
            patternHash.hash1 = (patternHash.hash1 + precomputedPowers1[charValue][j]) % MOD1;
            patternHash.hash2  = (patternHash.hash2 + precomputedPowers2[charValue][j]) % MOD2;

        }
        hashValOnePattern[patternLen].hash1 = patternHash.hash1;
        hashValOnePattern[patternLen].hash2 = patternHash.hash2;

        int times = patternLen;

        for(int s= 0; s < patternLen; s++){
            if(hashValOnePattern[s].hash1 == patternHash.hash1 && hashValOnePattern[s].hash2 == patternHash.hash2){
                times = 0;
                break;
            }
        }

        leftpointer = patternLen - 1 ;

        for (int j = 1; j < times; ++j) {

            int leftCharValue = pattern[leftpointer] - 'a' ;
            patternHash.hash1 = (patternHash.hash1 - precomputedPowers1[leftCharValue][patternLen - 1] + MOD1) % MOD1;
            patternHash.hash2 = (patternHash.hash2 - precomputedPowers2[leftCharValue][patternLen - 1] + MOD2) % MOD2;

            patternHash.hash1 = (patternHash.hash1 * BASE % MOD1 + precomputedPowers1[leftCharValue][0]) % MOD1;
            patternHash.hash2 = (patternHash.hash2 * BASE % MOD2 + precomputedPowers2[leftCharValue][0]) % MOD2;

            hashValOnePattern[j+patternLen].hash1 = patternHash.hash1;
            hashValOnePattern[j+patternLen].hash2 = patternHash.hash2;

            leftpointer = (leftpointer - 1 + modulo) % modulo;

        }

        int firsthalf = 1, secondhalf=0;
        long long searchhash1 = 0, searchhash2 = 0;

        for (int j = 1; j <  patternLen + times; ++j) {
            if (j < patternLen) {

                searchhash1 = hashValOnePattern[j].hash1;
                searchhash2 = hashValOnePattern[j].hash2;

                int searchRes = binarySearch(searchhash1, searchhash2);
                if (searchRes != -1) firsthalf++;
            } else {

                searchhash1 = hashValOnePattern[j].hash1;
                searchhash2 = hashValOnePattern[j].hash2;

                int searchRes = binarySearch(searchhash1, searchhash2);
                if (searchRes != -1) secondhalf++;
            }
        }


        if(firsthalf < secondhalf ) reverseCount += firsthalf;
        else
            reverseCount += secondhalf;

        minSubsetCount++;
    }

}

void MinimalSubset::precomputePowsAccordingBase() {
    int length = 100005;

    for (int i = 0; i < 26 ; ++i) {
        precomputedPowers1[i][0] =  i+1;
        precomputedPowers2[i][0] =  i+1;
    }

    for (int i = 0; i < 26 ; ++i) {
        for (int j = 1; j < length; ++j) {
            precomputedPowers1[i][j] = (precomputedPowers1[i][j - 1] * BASE) % MOD1;
            precomputedPowers2[i][j] = (precomputedPowers2[i][j - 1] * BASE) % MOD2;
        }
    }

}

int MinimalSubset::binarySearch(long long searchHash1, long long searchHash2) {
    int left = 0;
    int right = numOfStrings - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (hashValsAllPatterns[mid].hash1 < searchHash1) {
            left = mid + 1;
        } else if (hashValsAllPatterns[mid].hash1 > searchHash1) {
            right = mid - 1;
        } else {

            if (hashValsAllPatterns[mid].hash2 == searchHash2 && hashValsAllPatterns[mid].hash1 == searchHash1) {
                hashValsAllPatterns[mid].isVisited = true;
                return mid;
            } else if (hashValsAllPatterns[mid].hash2 < searchHash2) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return -1;
}
