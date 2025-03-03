/**
* Title: substrings.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : the main part that handles IO and calls RollingHash method for Question 1.
*/



#include "RollingHash.h"
#include <iostream>
#include <cstring>
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
    bool writeToFile = (argc == 3);
    if (writeToFile) {
        outputFile.open(argv[2]);
        if (!outputFile.is_open()) {
            cerr << "Error: Could not open file " << argv[2] << endl;
            return 1;
        }
    }

    //constrainte tekrar bak
    char text[500000];
    inputFile.getline(text, sizeof(text));
    int textLength = strlen(text);

    int numPatterns;
    inputFile >> numPatterns;

    char pattern[300000];   //300000    total length of patterns 
    inputFile >> pattern;

    int minLength = strlen(pattern);
    int maxLength = minLength + 5;

    RollingHash rh(31, maxLength, text, textLength);

    HashTuple patternHash = rh.computePatternHash(pattern, static_cast<int>(strlen(pattern)));

    int count;

    rh.findMatchingHashes(static_cast<int>(strlen(pattern)), patternHash, count, pattern);

    if (writeToFile) {
        outputFile << count << endl;
    }
    cout << count << endl;

    for (int i = 1; i < numPatterns; ++i) {
        inputFile >> pattern;

        patternHash = rh.computePatternHash(pattern, static_cast<int>(strlen(pattern)));

        rh.findMatchingHashes(static_cast<int>(strlen(pattern)), patternHash, count, pattern);

        if (writeToFile) {
            outputFile << count << endl;
        }
        cout << count ;
        if(i < numPatterns -1 )cout <<  endl;
    }

    inputFile.close();
    if (writeToFile) {
        outputFile.close();
    }

    return 0;
}



