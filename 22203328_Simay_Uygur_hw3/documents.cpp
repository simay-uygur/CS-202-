/**
* Title: substrings.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : main for document hash
*/

#include <iostream>
#include <fstream>
#include "DocumentHash.h"
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
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


    int numOfStrings;
    inputFile >> numOfStrings;


    char** docStrings = new char*[numOfStrings];
    char* tempBuffer = new char[100000];

    for (int i = 0; i < numOfStrings; ++i) {
        inputFile >> tempBuffer;
        int length = strlen(tempBuffer);
        docStrings[i] = new char[length + 1];
        for (int j = 0; j < length; ++j) {
            docStrings[i][j] = tempBuffer[j];
        }
        docStrings[i][length] = '\0';
    }

    delete[] tempBuffer;


    DocumentHash docHash(numOfStrings, docStrings);


    int result = docHash.calculateCommonDocNums();


    cout << result << endl;
    if (hasOutputFile) {
        outputFile << result << endl;
    }


    for (int i = 0; i < numOfStrings; ++i) {
        delete[] docStrings[i];
    }
    delete[] docStrings;

    inputFile.close();
    if (hasOutputFile) {
        outputFile.close();
    }

    return 0;
}
