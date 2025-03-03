/**
* Title: SubArrPlay
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This class contains the class that has the playing method for question 4.
*/

#include "SubArrPlay.h"

SubArrPlay::SubArrPlay(int *arrA, int *arrB, int eachCardSize, int mSubset, int kSubset):
minHeapA(nullptr) ,maxHeapB(nullptr), A(arrA), B(arrB), eachArrayLength(eachCardSize), mNumber(mSubset), kNumber(kSubset) {
}

SubArrPlay::~SubArrPlay() {
    delete maxHeapB;
    delete minHeapA;
}

int SubArrPlay::play() {
    int mx = mNumber, minNum = kNumber;

    if(kNumber > mx) {
        mx = kNumber;
        minNum = mNumber;
    }

    bool isDone = false;
    int minLength = eachArrayLength + 1;

    for (int i = 0; i <= eachArrayLength - mx; ++i) {
        delete minHeapA;
        delete maxHeapB;
        minHeapA = new Heap();
        maxHeapB = new MaxHeap();

        if(kNumber > mNumber) {

            for(int j = i; j < minNum + i; j++) {
                maxHeapB->addElementToHeap(B[j]);
                minHeapA->addElementToHeap(A[j]);
            }

            for(int j = minNum + i; j < mx + i; j++) {
                maxHeapB->addElementToHeap(B[j]);
                int minA = minHeapA->getTopElValue();
                if(A[j] > minA) {
                    minHeapA->addElementToHeap(A[j]);
                    minHeapA->deleteElementTopFromHeap();
                }
            }

            isDone = doesSatisfyCondition();
            if(isDone && minLength > mx) {
                minLength = mx;
            }

            for(int j = mx + i; j < eachArrayLength; j++) {
                int maxB = maxHeapB->getTopElValue();
                int minA = minHeapA->getTopElValue();
                if(B[j] < maxB) {
                    maxHeapB->addElementToHeap(B[j]);
                    maxHeapB->deleteElementTopFromHeap();
                }
                if(A[j] > minA) {
                    minHeapA->addElementToHeap(A[j]);
                    minHeapA->deleteElementTopFromHeap();
                }
                isDone = doesSatisfyCondition();
                if(isDone) {
                    if(minLength > j - i + 1) {
                        minLength = j - i + 1;
                    }
                }
            }
        } else {

            for(int j = i; j < minNum + i; j++) {
                maxHeapB->addElementToHeap(B[j]);
                minHeapA->addElementToHeap(A[j]);
            }

            for(int j = minNum + i; j < mx + i; j++) {
                minHeapA->addElementToHeap(A[j]);
                int maxB = maxHeapB->getTopElValue();
                if(B[j] < maxB) {
                    maxHeapB->addElementToHeap(B[j]);
                    maxHeapB->deleteElementTopFromHeap();
                }
            }

            isDone = doesSatisfyCondition();
            if(isDone && minLength > mx) {
                minLength = mx;
            }

            for(int j = mx + i; j < eachArrayLength; j++) {
                int maxB = maxHeapB->getTopElValue();
                int minA = minHeapA->getTopElValue();
                if(B[j] < maxB) {
                    maxHeapB->addElementToHeap(B[j]);
                    maxHeapB->deleteElementTopFromHeap();
                }
                if(A[j] > minA) {
                    minHeapA->addElementToHeap(A[j]);
                    minHeapA->deleteElementTopFromHeap();
                }
                isDone = doesSatisfyCondition();
                if(isDone) {
                    if(minLength > j - i + 1) {
                        minLength = j - i + 1;
                    }
                }
            }
        }
    }

    return minLength == eachArrayLength + 1 ? -1 : minLength;
}

bool SubArrPlay::doesSatisfyCondition() {
    return minHeapA->getTopElValue() > maxHeapB->getTopElValue() ;
}
