/**
* Title: Max Heap
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the min-heap source file which has adding/deleting operations of the heap structure. It also returns the top value of the heap which is the maximum value. Also this class has copy function that copies the heap elments to the given array. 
*/


#include "MaxHeap.h"

MaxHeap::MaxHeap(){

}

MaxHeap::MaxHeap(int size): totalSize(size), currentSize(0) {
}

MaxHeap::~MaxHeap() {
    currentSize = 0;
    totalSize = 0;
}


void MaxHeap::addElementToHeap(int key) {
    if(currentSize >= totalSize) return;
    heap[currentSize] = key;

    int place = currentSize;
    int parent = (place - 1)/2;

    currentSize++;

    while ((place > 0) && (heap[place] > heap[parent])) {
        swapElements(place, parent, heap, currentSize);
        place = parent;
        parent = (place - 1)/2;
    }
}

void MaxHeap::deleteElementTopFromHeap() {
    if (currentSize <= 0) return;

    heap[0] = heap[currentSize - 1];
    currentSize--;
    heapify(heap, 0, currentSize);
}

void MaxHeap::heapify(int *arr, int index, int size) {
    int largest = index;

    if(2*index + 1 < size && arr[2*index + 1] > arr[largest]) {
        largest = 2*index + 1;
    }
    if(2*index + 2 < size && arr[2*index + 2] > arr[largest]) {
        largest = 2*index + 2;
    }
    if(largest != index) {
        swapElements(index, largest, arr, size);
        heapify(arr, largest, size);
    }
}

void MaxHeap::swapElements(int index1, int index2, int *arr, int size) {
    if(index1 >= size || index2 >= size) {
        return;
    }

    int tempEl = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tempEl;
}

bool MaxHeap::heapIsEmpty() const {
    return (currentSize == 0);
}

int MaxHeap::parentInd(int childInd) {
    return (childInd - 1) / 2;
}

MaxHeap::MaxHeap(int *keys, int size, int wanted): totalSize(size), currentSize(size) {
    if (size <= 0 || keys == nullptr) {
        currentSize = 0;
        totalSize = 1000005; // or some default size
        return;
    }

    currentSize = 0;
    totalSize = 1000005;


    for (int i = 0; i < wanted; i++) {
        addElementToHeap(keys[i]);

    }
}

int MaxHeap::getTopElValue() {
    return currentSize == 0 ? -1 : heap[0];
}

void MaxHeap::copyHeapArrToAnother(int arr[], int arSize) {

    for (int i = 0; i < currentSize && i < arSize; ++i) {
        arr[i] = heap[i];
    }

}

int MaxHeap::getSizeHeap() {
    return currentSize;
}

