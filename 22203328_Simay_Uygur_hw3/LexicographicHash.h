/**
* Title: lexic
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : header for q4
*/

#ifndef LEXICOGRAPHICHASH_H
#define LEXICOGRAPHICHASH_H

class LexicographicHash {
private:
    int hashTableSize;
    int numOfValidInputs;
    int* hashTable;
    bool ** adjacencyMatrix;
    int* counts;

    void validateNums();
    void constructAdjacencyM();
    void setCountArr();


public:

    LexicographicHash(int tableSize,  int* const& inputArray);
    ~LexicographicHash();

    bool compareLexicographicOrder(int firstNumber, int secondNumber);

    int calculateHashAndReturn(int* & arrayR, bool & isImpossible);
    int findMinLexicographicIndexWithZeroCount();

};

#endif
