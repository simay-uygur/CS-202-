/**
* Title: documenthash.h
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : struct of doctuple class and related methods to calculate
*/

#ifndef DOCUMENT_HASH_H
#define DOCUMENT_HASH_H


struct DocTuple {
    long long hash1, hash2;
    int stringId;
    int count;
    int length;
    bool isVisited;

    DocTuple() : hash1(0), hash2(0), stringId(-1), count(0), length(0),isVisited(false)  {}

    DocTuple(long long h1, long long h2, int id, int count, int len, bool visited)
            : hash1(h1), hash2(h2), stringId(id), count(count), length(len), isVisited(visited) {}
};
class DocumentHash {
public:
    DocumentHash(int numOfStrings, char** const& docStrings);
    ~DocumentHash();

    int calculateCommonDocNums();

private:
    long long** precomputedPowers1;
    long long** precomputedPowers2;
    DocTuple* allPermutations;
    DocTuple* allPatternsHash;

    const long long MOD1 = 1e9 + 7;
    const long long MOD2 = 1e9 + 9;
    const long long BASE = 31;

    int numOfStrings;
    char** docStrings;
    char* currentPatternChars;
    DocTuple* currentPatternTuple;
    int totalCharsLength;


    void precomputePowsAccordingBase();
    void computeStringHashes();
    void addOneChar(int &startIndex, int patternLength);
    void deleteOneChar(int &startIndex, int patternLength);
    void cyclicShift(int &startIndex, int patternLegth);
    void changeOneChar(int &startIndex, int patternLength);

    void setCountsForElements();

    int processAndCountUnique();
};

#endif
