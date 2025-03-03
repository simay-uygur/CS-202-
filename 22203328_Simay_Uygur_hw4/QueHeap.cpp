/**
* Title: QueueHeap.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 4
* Description : Source file of QueueHeap
*/

#include "QueHeap.h"


QueHeap::QueHeap(int size) : totalSize(size), currentSize(0) {
    heap = new queStruct[size];
}

QueHeap::~QueHeap() {
    delete[] heap;
}

void QueHeap::addElementToHeap(int order, int index) {
    if (currentSize >= totalSize) return;

    heap[currentSize] = queStruct(order, index);
    int place = currentSize;
    int parent = (place - 1) / 2;

    currentSize++;
    while (place > 0 && heap[place].order < heap[parent].order) {
        swapElements(place, parent);
        place = parent;
        parent = (place - 1) / 2;
    }
}

void QueHeap::deleteElementTopFromHeap() {
    if (currentSize <= 0) return;
    heap[0] = heap[currentSize - 1];
    currentSize--;
    heapify(0);
}

queStruct QueHeap::getTopElValue() {
    if (currentSize == 0) return queStruct(-1, -1);
    return heap[0];
}

bool QueHeap::heapIsEmpty() const {
    return currentSize == 0;
}

void QueHeap::heapify(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < currentSize && heap[left].order < heap[smallest].order) {
        smallest = left;
    }
    if (right < currentSize && heap[right].order < heap[smallest].order) {
        smallest = right;
    }
    if (smallest != index) {
        swapElements(index, smallest);
        heapify(smallest);
    }
}

void QueHeap::swapElements(int index1, int index2) {
    queStruct temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}