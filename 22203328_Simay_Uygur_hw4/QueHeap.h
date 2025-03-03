/**
* Title: QueueHeap.h
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 4
* Description : A custom heap-based priority queue for BFS traversal and distance calculations.
*/

#ifndef QUEHEAP_H
#define QUEHEAP_H

struct queStruct {
    int order;
    int index;

    queStruct(int o, int i) : order(o), index(i) {}
    queStruct(): order(1e9), index(1e9) {}
};
class QueHeap {
private:
    queStruct* heap;
    int totalSize;
    int currentSize;

    void heapify(int index);
    void swapElements(int index1, int index2);

public:
    QueHeap(int size);
    ~QueHeap();

    void addElementToHeap(int order, int index);
    void deleteElementTopFromHeap();
    queStruct getTopElValue();
    bool heapIsEmpty() const;

};

#endif
