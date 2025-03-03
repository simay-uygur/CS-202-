/**
* Title: Binary Search Trees
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 1
* Description :  The header file of time analysis class
*/

#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "BST.h"
#include <ctime>
class analysis {
public:
    void timeAnalysis();
    void keepBalance(int array[], int arSize, BST& tree, int st, int fin, clock_t& startTimeClock);
    void timeBalanceAnalysis();
    void timeAnalysisSorted(); //bunu da sadece sorted olursa
    
};
#endif
