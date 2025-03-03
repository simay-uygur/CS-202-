/**
* Title: Heap (min-heap)
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the source file of the min-heap. Adding elements and removing top element and if the heap property is destroyed, heapify corrects it. In addition and deletion, heapify function is called. Also there are helper functions to swap elements. fillQuery method arranges the query array to have 5 least elements by iterating first 31 elements of the heap and making querying asymptotically O(1). also there is a copying heap function fo a given array (for merge sort temporary array).
*/

#include "Heap.h"
#include <iostream>

Heap::Heap() {
}

Heap::~Heap() {

}

void Heap::addElementToHeap(int key) {
    if(currentSize >= totalSize) return;

    heap[currentSize] = key;

    int place = currentSize;
    int parent = (place - 1)/2;

    currentSize++;
    while ( (place > 0) && (heap[place] < heap[parent] ) ) {
        swapElements(place, parent, heap, currentSize);
        place = parent;
        parent = (place - 1)/2;
    }

    fillQuery();
}

void Heap::deleteElementTopFromHeap() {
    if (currentSize <= 0) return;
    heap[0] = heap[currentSize - 1];
    currentSize--;
    heapify(heap, 0, currentSize);
    fillQuery();
}

void Heap::queryFiveElementsHeap(std::ofstream& outFile) { //o(1) asymptotically
    if(currentSize < 5) {
        std::cout << -1 << std::endl;
        if(outFile.is_open())
            outFile << -1 << std::endl;

    } else {
        for(int i = 0; i < 5; i++) {
            std::cout << queryArr[i] << std::endl;
            if(outFile.is_open())
                outFile << queryArr[i] << std::endl;
        }
    }

}

int Heap::parentInd(int childInd) {
    return (childInd - 1) / 2;
}

void Heap::heapify(int *arr, int index, int size) {
    if(index >= size) return;
    int minimum = index;

    if(2*index + 1 < size && arr[2*index + 1] < arr[minimum]){
        minimum = 2* index + 1;
    }
    if(2*index + 2 < size && arr[2*index + 2] < arr[minimum]){
        minimum = 2* index + 2;
    }
    if(minimum != index){
        swapElements(index, minimum, arr, size);
        heapify(arr, minimum, size);
    }

}

void Heap::swapElements(int index1, int index2, int *arr, int size) {
    if(index1 >= size || index2 >= size){
        return;
    }

    int tempEl = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tempEl;
}

bool Heap::heapIsEmpty() const {
    return (currentSize == 0);
}

void Heap::fillQuery() {
    if (currentSize < 5) return;
    int min1;

    queryArr[0] = heap[0];

    if (heap[1] <= heap[2]) {
        queryArr[1] = heap[1];
        min1 = heap[2];
    } else {
        queryArr[1] = heap[2];
        min1 = heap[1];
    }

    int min2 = -1;
    int min3 = -1;

    for(int i = 3; i < currentSize && i < 31; i++) {
        if(heap[i] < min1) {
            min3 = min2;
            min2 = min1;
            min1 = heap[i];
        }
        else if(min2 == -1 || heap[i] < min2) {
            min3 = min2;
            min2 = heap[i];
        }
        else if(min3 == -1 || heap[i] < min3) {
            min3 = heap[i];
        }
    }

    queryArr[2] = min1;
    queryArr[3] = min2;
    queryArr[4] = min3;
}

Heap::Heap(int *keys, int size, int wanted): totalSize(size), currentSize(size) {
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

int Heap::getTopElValue() {
    return currentSize == 0 ? -1 : heap[0];
}

void Heap::copyHeapArrToAnother(int arr[], int arSize) {

    for (int i = 0; i < currentSize && i < arSize; ++i) {
        arr[i] = heap[i];
    }

}

int Heap::getSizeHeap(){
    return currentSize;
}

