/**
* Title: PrefixArrPlay
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the header file fro playing in the third question. doesSatisfy method checks the first sortem m elements and compare one by one, and returns true if winning condition satisfied for that length.
*/

#include "PrefixArrPlay.h"

PrefixArrPlay::PrefixArrPlay(int *arrA, int *arrB, int eachCardSize, int mSubset): eachArrayLength(eachCardSize), mNumber(mSubset), arrayA(arrA), arrayB(arrB),minHeapA(nullptr), maxHeapB(nullptr){
}

PrefixArrPlay::~PrefixArrPlay() {

}

int PrefixArrPlay::play() {
    int subLength ;

    subLength = binarySearchSolutionArr(eachArrayLength, mNumber) +1;
    return subLength;
}

bool PrefixArrPlay::doesSatisfyCondition(int endIndex, int mNumber){

    minHeapA = new Heap(arrayA,mNumber,mNumber);
    maxHeapB = new MaxHeap(arrayB, mNumber, mNumber);

    for (int j = mNumber; j < endIndex+1; ++j) {
        minHeapA->addElementToHeap(arrayA[j]);
        minHeapA->deleteElementTopFromHeap();

        maxHeapB->addElementToHeap(arrayB[j]);
        maxHeapB->deleteElementTopFromHeap();
    }
    int size = 1000005;
    tempArr1 = new int[size];
    tempArr2 = new int[size];
    
    minHeapA->copyHeapArrToAnother(tempArr1, mNumber);
    maxHeapB->copyHeapArrToAnother(tempArr2, mNumber);

    int siz = mNumber-1;
    mergeSort(tempArr1, 0, siz);
    mergeSort(tempArr2, 0, siz);

    int count = 0, length = endIndex + 1;
    for(int i=0; i < length && count < mNumber; i++){
        if(tempArr1[i] > tempArr2[i]){
            count++;
        }
    }
    delete maxHeapB;
    delete minHeapA;
    delete[] tempArr1;
    delete[] tempArr2;

    if(count >= mNumber) return true;

    return false;
}

int PrefixArrPlay::binarySearchSolutionArr(int totalN, int M) {
    if (totalN <= 0 || M <= 0 || M > totalN) {
        return -1;
    }

    int leftIndexSub = 0;
    int rightIndexSub = totalN - 1;
    int result = totalN;

    while (leftIndexSub <= rightIndexSub) {
        int mid = leftIndexSub + (rightIndexSub - leftIndexSub) / 2;

        if (doesSatisfyCondition(mid, M)) {
            result = mid;
            rightIndexSub = mid - 1;
        } else {
            leftIndexSub = mid + 1;
        }
    }

    return result;
}

void PrefixArrPlay::merge(int theArray[], int first, int mid, int last) {
    int tempArray[1000005];
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = first1;
    for (; (first1 <= last1) && (first2 <= last2); ++index) {
        if (theArray[first1] < theArray[first2]) {
            tempArray[index] = theArray[first1];
            ++first1;
        } else {
            tempArray[index] = theArray[first2];
            ++first2;
        }
    }

    for (; first1 <= last1; ++first1, ++index)
        tempArray[index] = theArray[first1];

    for (; first2 <= last2; ++first2, ++index)
        tempArray[index] = theArray[first2];

    for (index = first; index <= last; ++index)
        theArray[index] = tempArray[index];
}

void PrefixArrPlay::mergeSort(int theArray[], int first, int second) {
    if (first < second) {
        int mid = (first + second) / 2;
        mergeSort(theArray, first, mid);
        mergeSort(theArray, mid + 1, second);

        merge(theArray, first, mid, second);
    }

}

