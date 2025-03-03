/**
* Title: least5
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This file handles the input and output file reading/writing operations. In a loop, it checks a , r, and g and calss related Heap methods. 
*/

#include "Heap.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

    char* inputName = argv[1];
    ifstream inFile(inputName);
    ofstream outFile;

    if (!inFile.is_open()) {
        cout << "Error opening input file: " << inputName << endl;
        return 1;
    }

    if (argc == 3) {  // third is output == 3
        char* outputName = argv[2];
        outFile.open(outputName);

    }

    int totalInstNum = 0 ,addElementKey;
    inFile >> totalInstNum;
    char methodCallChar;
    Heap minHeap;


    for (int i = 0; i < totalInstNum; ++i) {
        inFile >> methodCallChar;
        switch (methodCallChar) {
            case 'a':
                inFile >> addElementKey;
                minHeap.addElementToHeap(addElementKey);
                break;
            case 'r':
                minHeap.deleteElementTopFromHeap();
                break;
            case 'g':
                minHeap.queryFiveElementsHeap(outFile);
                break;
            default:
                break;
        }
    }

    inFile.close();
    if (outFile.is_open()) {
        outFile.close();
    }

    return 0;
}
