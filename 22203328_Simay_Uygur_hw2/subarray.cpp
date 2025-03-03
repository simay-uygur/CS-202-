/**
* Title: subarray
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the executable file that contains main method.
*/

#include "SubArrPlay.h"
#include <iostream>
#include <fstream>

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

    int eachNumCardN, mNum, kNum;
    inFile >> eachNumCardN >> mNum >> kNum;

    int* aArray = new int[eachNumCardN];
    int* bArray = new int[eachNumCardN];

    for(int i = 0; i < eachNumCardN; i++) {
        inFile >> aArray[i];
    }

    for(int i = 0; i < eachNumCardN; i++) {
        inFile >> bArray[i];
    }

    SubArrPlay game(aArray, bArray, eachNumCardN, mNum, kNum);
    int score = game.play();

    if(outFile.is_open()) {
        outFile << score << "";
    }
    cout << score;

    delete[] aArray;
    delete[] bArray;

    return 0;
}
 
