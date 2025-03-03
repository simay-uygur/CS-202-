 /**
* Title: SubArrPlay
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the header file for the class of 4th question. 
*/

#ifndef INC_202_HW_2_SUBARRPLAY_H
#define INC_202_HW_2_SUBARRPLAY_H


#include "Heap.h"
#include "MaxHeap.h"

class SubArrPlay{

public:
    SubArrPlay(int* arrA, int* arrB, int eachCardSize, int mSubset, int kSubset);
    ~SubArrPlay();

    int play();

private:
    bool doesSatisfyCondition();

    Heap* minHeapA;
    MaxHeap* maxHeapB;

    int* A;
    int* B;

    int eachArrayLength;
    int mNumber;
    int kNumber;

};
#endif //INC_202_HW_2_SUBARRPLAY_H
