/**
* Title: Max Heap
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the header file of the max-heap.
*/

#ifndef INC_202_HW_2_MAXHEAP_H
#define INC_202_HW_2_MAXHEAP_H


class MaxHeap{
public:
    void addElementToHeap(int key);
    void deleteElementTopFromHeap();

    MaxHeap();
    MaxHeap(int size );
    ~MaxHeap();

    MaxHeap(int *keys, int size, int wanted);

    int getTopElValue();

    void copyHeapArrToAnother(int arr[], int arSize);
    int getSizeHeap();

private:
    int totalSize = 1000005;
    int currentSize = 0 ;
    int heap[1000005];

    void heapify(int* arr,int index, int size );
    void swapElements(int index1,int index2, int* arr, int size);
    bool heapIsEmpty() const;

    void increaseKey(int index, int insertedKey);
    int parentInd(int childInd);


};
#endif

