/**
* Title: lexicographic.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : main of q4
*/
#include <iostream>
#include <fstream>
#include "LexicographicHash.h"

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

    int tableSize;
    inputFile >> tableSize;

    int *inputArray = new int[tableSize];
    for (int i = 0; i < tableSize; ++i) {
        inputFile >> inputArray[i];
    }

    LexicographicHash lexHash(tableSize, inputArray);

    int *resultArray = new int[tableSize];

    bool isImpossible = false;
    for (int i = 0; i < tableSize; ++i) {
        resultArray[i] = -1;
    }

    lexHash.calculateHashAndReturn(resultArray, isImpossible);

    if (isImpossible) {
        cout << "Impossible" << endl;
        if (hasOutputFile) {
            outputFile << "Impossible" << endl;
        }
    } else {
        int index = -1;
        for (int i = 0; i < tableSize; ++i) {
            if (resultArray[i] != -1) {
                cout << resultArray[i];
                outputFile << resultArray[i];
                index = i;
                break;
            }
        }

        for (int i = index + 1; i < tableSize; ++i) {

            if (resultArray[i] != -1) {
                cout << " ";
                if (hasOutputFile) {
                    outputFile << " ";
                }
                cout << resultArray[i];
                if (hasOutputFile) {
                    outputFile << resultArray[i];
                }
            }
        }
        cout << endl;
        if (hasOutputFile) {
            outputFile << endl;
        }


    }

    delete[] inputArray;
    delete[] resultArray;

    inputFile.close();

    if (hasOutputFile) {
        outputFile.close();

    }

    return 0;

}
