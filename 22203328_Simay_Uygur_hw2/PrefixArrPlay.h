/**
* Title: PrefixArrPlay
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the header file fro playing in the third question.
*/

#ifndef INC_202_HW_2_PREFIXARRPLAY_H
#define INC_202_HW_2_PREFIXARRPLAY_H

#include "Heap.h"
#include "MaxHeap.h"

class PrefixArrPlay {

public:
    PrefixArrPlay(int* arrA, int* arrB, int eachCardSize, int mSubset);
    ~PrefixArrPlay();
    int play();
private:
    int eachArrayLength;
    int mNumber;
    int kNumber;
    int* arrayA;
    int* arrayB;
    Heap* minHeapA;
    MaxHeap* maxHeapB;
    int* tempArr1;
    int* tempArr2;

    bool doesSatisfyCondition(int endIndex, int mNumber);

    int binarySearchSolutionArr(int N, int M);
    void merge(int theArray[], int first, int mid, int last);
    void mergeSort(int theArray[], int first, int sec);

};

#endif //INC_202_HW_2_PREFIXARRPLAY_H
