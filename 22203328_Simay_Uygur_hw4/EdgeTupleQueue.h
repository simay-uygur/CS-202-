/**
* Title: EdgeTupleQueue.h
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 4
* Description : A priority queue for managing EdgeTuple objects during MST computation. Using the minHeap implementation of the previous homework (second one in this semester).
*/

#ifndef EDGETUPLEQUEUE_H
#define EDGETUPLEQUEUE_H

#include "EdgeTuple.h"

class EdgeTupleQueue {
public:

    EdgeTupleQueue(int size);
    ~EdgeTupleQueue();


    void addElementToHeap(const EdgeTuple& edge);
    void deleteElementTopFromHeap();
    EdgeTuple getTopElValue() const;
    bool heapIsEmpty() const;
    int getSize() const;

private:
    int totalSize;
    int currentSize;
    EdgeTuple* heap;


    void heapify(int index);
    void swapElements(int index1, int index2);
};

#endif
