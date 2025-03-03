/**
* Title: insertionorders
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : main of q5
*/

#include <iostream>
#include <fstream>
#include "InsOrders.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " <input_file> [output_file]" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    ofstream outputFile;
    bool hasOutputFile = (argc == 3);
    if (hasOutputFile) {
        outputFile.open(argv[2]);
        if (!outputFile.is_open()) {
            cerr << "Error: Could not open file " << argv[2] << endl;
            return 1;
        }
    }

    int size;
    inputFile >> size;

    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        inputFile >> arr[i];
    }

    InsOrders io;
    long long result = io.calculateInsertionOrderPermutations(size, arr);

    cout << result << endl;
    if (hasOutputFile) {
        outputFile << result ;
    }

    delete[] arr;

    inputFile.close();
    if (hasOutputFile) {
        outputFile.close();
    }

    return 0;
}

