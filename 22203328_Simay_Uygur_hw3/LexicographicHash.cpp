/**
* Title: LexicographicHash.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : Header of lexicographichash
*/

#include "LexicographicHash.h"
#include <iostream>

LexicographicHash::LexicographicHash(int tableSize,  int* const& inputArray )
        : hashTableSize(tableSize), numOfValidInputs(0), hashTable(inputArray) {

    adjacencyMatrix = new bool*[hashTableSize];
    validateNums();


    counts = new int[hashTableSize];
    constructAdjacencyM();
    setCountArr();

}

LexicographicHash::~LexicographicHash() {

    if (adjacencyMatrix != nullptr) {
        for (int i = 0; i < hashTableSize; ++i) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }


}

void LexicographicHash::validateNums(){
    for (int i = 0; i < hashTableSize; ++i) {
        if(hashTable[i] != -1){
            numOfValidInputs++;
        }
    }
}

void LexicographicHash::constructAdjacencyM(){

    for (int i = 0; i <hashTableSize; ++i) {
        adjacencyMatrix[i] = new bool[hashTableSize];
        int count = 0;
        if(hashTable[i] == -1 ) continue;

        int index = hashTable[i] % hashTableSize;
        if(index == i || hashTable[i] == -1){
            for (int j = 0; j < hashTableSize; ++j) {
                adjacencyMatrix[i][j] = false;
            }
            if(index == i){
                counts[i] = 0;
            } else{
                counts[i] = -1;
            }
        }
        else{
            while (index != i){
                adjacencyMatrix[i][index] = true;
                index++;
                index = index % hashTableSize;
                count++;
            }
            counts[i] = count;
        }

    }
}

void LexicographicHash::setCountArr(){
    for (int i = 0; i < hashTableSize; ++i) {
        int count = 0;
        for (int j = 0; j < hashTableSize; ++j) {
            if(adjacencyMatrix[i][j]){
                count++;
            }
            if(hashTable[i] == -1){
                count = -1;
                break;
            }
        }
        counts[i] = count;
    }
}

bool LexicographicHash::compareLexicographicOrder(int firstNumber, int secondNumber) {
    return (firstNumber < secondNumber);
}

int LexicographicHash::calculateHashAndReturn(int *&arrayR, bool &isImpossible) {


    for (int i = 0; i < hashTableSize; ++i) {
        if(hashTable[i] == -1){
            arrayR[i] = -1;
        }
    }

    for (int i = 0; i < numOfValidInputs; ++i) {

        int ind = findMinLexicographicIndexWithZeroCount();

        if(ind == -1 ){
            isImpossible = true;
            return -1;
        }

        arrayR[i] = hashTable[ind];
        counts[ind] = -1;

        for (int j = 0; j < hashTableSize; ++j) {
            if(adjacencyMatrix[j][ind]){
                counts[j] = counts[j] - 1 ;
            }
        }

    }

    return numOfValidInputs;
}

int LexicographicHash::findMinLexicographicIndexWithZeroCount() {
    int minIndex = -1;
    int minValue = -1;

    for (int i = 0; i < hashTableSize; ++i) {
        if (counts[i] == 0) {
            if (minValue == -1 || compareLexicographicOrder(hashTable[i], minValue)) {
                minValue = hashTable[i];
                minIndex = i;
            }
        }
    }

    return minIndex;
}
/*

void LexicographicHash::printAdjacencyMatrix() const {
    std::cout << "Adjacency Matrix:" << std::endl;
    for (int i = 0; i < hashTableSize; ++i) {
        for (int j = 0; j < hashTableSize; ++j) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void LexicographicHash::printCountsArray() const {
    std::cout << "Counts Array:" << std::endl;
    for (int i = 0; i < hashTableSize; ++i) {
        std::cout << "Index " << i << ": " << counts[i] << std::endl;
    }
}
*/
/*
  int totalDigitsFirst = findTotalDigits(firstNumber);
  int totalDigitsSecond = findTotalDigits(secondNumber);

  int divisorFirst = computeExponential(10, totalDigitsFirst - 1);
  int divisorSecond = computeExponential(10, totalDigitsSecond - 1);

  while (divisorFirst > 0 && divisorSecond > 0) {
      int leadingDigitFirst = firstNumber / divisorFirst;
      int leadingDigitSecond = secondNumber / divisorSecond;

      if (leadingDigitFirst != leadingDigitSecond) {
          return (leadingDigitFirst < leadingDigitSecond);
      }

      firstNumber %= divisorFirst;
      secondNumber %= divisorSecond;

      divisorFirst /= 10;
      divisorSecond /= 10;
  }

  return (totalDigitsFirst < totalDigitsSecond);

   */
