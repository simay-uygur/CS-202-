/**
* Title: game
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the executable and main file for the holosko and bobo's game playing. This class creates a CardGame object and calls play method then returns resurt. Also this class handles input and output file writing and reading operations using fstream.
*/

#include "CardGame.h"
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

    int eachNumCardN;
    if(!(inFile >> eachNumCardN)) {
        return 1;
    }

    int* boboCards = new int[eachNumCardN];
    int* holoskoCards = new int[eachNumCardN];

    for(int i = 0; i < eachNumCardN; i++) {
        if(!(inFile >> boboCards[i])) {
            delete[] boboCards;
            delete[] holoskoCards;
            return 1;
        }
    }

    for(int i = 0; i < eachNumCardN; i++) {
        if(!(inFile >> holoskoCards[i])) {
            delete[] boboCards;
            delete[] holoskoCards;
            return 1;
        }
    }

    int bobScore, holScore;
    CardGame game(boboCards, holoskoCards, eachNumCardN);
    game.play(bobScore, holScore);

    if(outFile.is_open()) {
        outFile << bobScore << " " << holScore << endl;
    }
    cout << bobScore << " " << holScore << endl;

    delete[] boboCards;
    delete[] holoskoCards;

    return 0;
}
 
