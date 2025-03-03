/**
* Title: prefixsubarray
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the executable that has main method for question 4.
*/

#include <iostream>
#include <fstream>
#include "PrefixArrPlay.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        return 1;
    }

    char* inputName = argv[1];
    ifstream inFile(inputName);
    ofstream outFile;

    if (!inFile.is_open()) {
        return 1;
    }

    if(argc == 3) {
        char* outputName = argv[2];
        outFile.open(outputName);
        if (!outFile.is_open()) {
            return 1;
        }
    }

    int eachNumCardN, mNumber;
    inFile >> eachNumCardN >> mNumber;

    int* aArray = new int[eachNumCardN];
    int* bArray = new int[eachNumCardN];

    for(int i = 0; i < eachNumCardN; i++) {
        if(!(inFile >> aArray[i])) {
            delete[] aArray;
            delete[] bArray;
            return 1;
        }
    }

    for(int i = 0; i < eachNumCardN; i++) {
        if(!(inFile >> bArray[i])) {
            delete[] aArray;
            delete[] bArray;
            return 1;
        }
    }

    PrefixArrPlay prefGame(aArray, bArray, eachNumCardN, mNumber);
    int score = prefGame.play();

    if(outFile.is_open()) {
        outFile << score << "";
    }
    cout << score;

    delete[] aArray;
    delete[] bArray;

    return 0;
}
 
