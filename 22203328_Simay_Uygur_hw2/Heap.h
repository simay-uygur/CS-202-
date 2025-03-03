/**
* Title: Heap (min-heap)
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description :This is the header file of the min heap implementation for question 1. 
*/

#ifndef INC_202_HW_2_HEAP_H
#define INC_202_HW_2_HEAP_H

#include <cstdio>
#include <fstream>

class Heap{
public:
    void addElementToHeap(int key);
    void deleteElementTopFromHeap();
    void queryFiveElementsHeap(std::ofstream& outFile);

    Heap();
    ~Heap();

    Heap(int *keys, int size, int wanted);

    int getTopElValue();
    void copyHeapArrToAnother(int arr[],int arSize);
    int getSizeHeap();
private:
    int totalSize = 1000005;
    int currentSize = 0;
    int heap[1000005];
    int queryArr[5];


    int parentInd(int childIndex);

    void swapElements(int index1,int index2, int* arr, int size);
    bool heapIsEmpty() const;

    void heapify(int* arr,int index, int size );

    void fillQuery();

};
#endif //INC_202_HW_2_HEAP_H


