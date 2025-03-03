/**
* Title: CardGame
* Author: Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 2
* Description : This is the header file of Cardgame class. This class sets the AVL trees according to the players' cards and starts the game with optimal playing.
*/

#ifndef INC_202_HW_2_CARDGAME_H
#define INC_202_HW_2_CARDGAME_H

#include "BST.h"


class CardGame{

public:
    CardGame(int* boboArray, int* holoArray, int eachPlayerCardNum);
    ~CardGame();
    void play(int& boboScore, int& holoskoScore);

private:

    BST* boboTree;
    BST* holoskoTree;

    int boScore = 0;
    int hoScore = 0;
    int cardNumPlayer = 0;

    void mergeSort(int*& theArray, int first, int sec);
    void merge(int*& theArray, int first, int mid, int last);
};
#endif
