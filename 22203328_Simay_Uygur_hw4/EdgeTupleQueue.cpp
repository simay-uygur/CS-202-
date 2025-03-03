/**
* Title: EdgeTupleQueue.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 4
* Description : Source file of EdgeTupleQueue
*/

#include "EdgeTupleQueue.h"

EdgeTupleQueue::EdgeTupleQueue(int size) : totalSize(size), currentSize(0) {
    heap = new EdgeTuple[size];
}

EdgeTupleQueue::~EdgeTupleQueue() {
    delete[] heap;
}

void EdgeTupleQueue::addElementToHeap(const EdgeTuple& edge) {
    if (currentSize >= totalSize) return;

    heap[currentSize] = edge;
    int place = currentSize;
    int parent = (place - 1) / 2;

    currentSize++;
    while (place > 0 && heap[place].source < heap[parent].source){ // || (heap[place].source == heap[parent].source && heap[place].destination < heap[parent].destination) ) ){
        swapElements(place, parent);
        place = parent;
        parent = (place - 1) / 2;
    }
}

void EdgeTupleQueue::deleteElementTopFromHeap() {
    if (currentSize <= 0) return;
    heap[0] = heap[currentSize - 1];
    currentSize--;
    heapify(0);
}

EdgeTuple EdgeTupleQueue::getTopElValue() const {
    if (currentSize == 0) return EdgeTuple(-1, -1);
    return heap[0];
}

bool EdgeTupleQueue::heapIsEmpty() const {
    return currentSize == 0;
}

int EdgeTupleQueue::getSize() const {
    return currentSize;
}

void EdgeTupleQueue::heapify(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;


    if (left < currentSize && heap[left].source < heap[smallest].source) {
        smallest = left;
    }

    if (right < currentSize && heap[right].source < heap[smallest].source) {
        smallest = right;
    }

    if (smallest != index) {
        swapElements(index, smallest);
        heapify(smallest);
    }
}

void EdgeTupleQueue::swapElements(int index1, int index2) {
    EdgeTuple temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}
