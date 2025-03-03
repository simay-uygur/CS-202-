/**
* Title: minimalsubset
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : main for q2
*/

#include "MinimalSubset.h"
#include <iostream>
#include <fstream>

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
    bool outFexist = (argc == 3);
    if (outFexist) {
        outputFile.open(argv[2]);
        if (!outputFile.is_open()) {
            cerr << "Error: Could not open file " << argv[2] << endl;
            return 1;
        }
    }

    int n;
    inputFile >> n;
    char ** strings = new char *[n];

    for (int i = 0; i < n; ++i) {

        strings[i] = new char[100000];   //heap kafayı yer mi acep
        inputFile >> strings[i];
    }

    int numReverse = 0, minSubSize = 0;


    MinimalSubset subs(n, strings);  //kopyalamıyordur umarım
    subs.calculateMinSubsetAndRev(numReverse, minSubSize);

    if (outFexist) {
        outputFile << numReverse << endl;
        outputFile << minSubSize << endl;
    }

    cout << numReverse << endl;
    cout << minSubSize << endl;

    inputFile.close();
    if (outFexist) {
        outputFile.close();
    }

    for (int i = 0; i < n; ++i) {
        delete strings[i];
    }

    delete[] strings;

    return 0;
}

