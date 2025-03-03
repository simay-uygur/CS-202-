/**
* Title: Card Game
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the class for game executable. This class does the playing logic with play function. Constructor takes bobo and holosko's arrays and initializes. Then merge sorting the arrays, it creates a balanced bst. Playing optimally happens with searchForLessBiggest in the bst file. 
*/

#include "CardGame.h"

void CardGame::play(int& boboScore, int& holoskoScore) {
    bool isBoboTurn = true;
    int turns = 0;
    int boboMax = 0;
    int holoMax = 0;
    int holoLess = 0;
    int boboLess = 0;

    while(turns < cardNumPlayer){
        if(isBoboTurn){
            boboMax = boboTree->getMaxElementPublic();
            holoLess = holoskoTree->searchForLessBiggest(boboMax);
            holoskoTree->deleteKey(holoLess);
            boboTree->deleteKey(boboMax);

            if(boboMax > holoLess){
                boScore++;
            } else {
                hoScore++;
            }
        } else {
            holoMax = holoskoTree->getMaxElementPublic();
            boboLess = boboTree->searchForLessBiggest(holoMax);
            boboTree->deleteKey(boboLess);
            holoskoTree->deleteKey(holoMax);

            if(holoMax > boboLess){
                hoScore++;
            } else {
                boScore++;
            }

        }
        isBoboTurn = !isBoboTurn;
        turns++;

    }

    boboScore = boScore;
    holoskoScore = hoScore;

}

CardGame::CardGame(int *boboArray, int *holoArray, int eachPlayerCardNum) :cardNumPlayer(eachPlayerCardNum){
    boboTree = new BST();
    mergeSort(boboArray, 0, eachPlayerCardNum -1);
    boboTree->constructBalancedBst(boboArray, eachPlayerCardNum);

    mergeSort(holoArray, 0, eachPlayerCardNum -1);
    holoskoTree = new BST();
    holoskoTree->constructBalancedBst(holoArray, eachPlayerCardNum);
}

CardGame::~CardGame() {
    delete boboTree;
    delete holoskoTree;
}

void CardGame::mergeSort(int*& theArray, int first, int second) {
    if(first == second) return;

    int q = (first+second) / 2;
    mergeSort(theArray,first,q);
    mergeSort(theArray, q+1, second);

    merge(theArray, first, q, second);

}

void CardGame::merge(int *&theArray, int first, int mid, int last) {
    int tempArray[1000005]; 
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = first1;
    for (; (first1 <= last1) && (first2 <= last2); ++index) {
        if (theArray[first1] < theArray[first2]) {
            tempArray[index] = theArray[first1];
            ++first1;
        } else {
            tempArray[index] = theArray[first2];
            ++first2;
        }
    }

    for (; first1 <= last1; ++first1, ++index)
        tempArray[index] = theArray[first1];

    for (; first2 <= last2; ++first2, ++index)
        tempArray[index] = theArray[first2];

    for (index = first; index <= last; ++index)
        theArray[index] = tempArray[index];
}




