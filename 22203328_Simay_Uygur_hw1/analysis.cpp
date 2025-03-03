/**
* Title: Binary Search Trees
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 1
* Description : This code provides analysis functions for Binary Search Tree (BSTs).
 *Three primary analysis techniques are included:
 * 1. timeAnalysis(): Calculates the time required to add random integers to a BST * and, after 1000 insertions, outputs the time and tree height.
 * 2. timeBalanceAnalysis(): Measures the insertion time and applies a balanced insertion strategy to a more balanced BST.
 * 3. timeAnalysisSorted(): Examines the effectiveness of BST insertions using * sorted data, taking measurements of time and tree height per 1000 insertions. These functions facilitate the comparison of BST performance under various data distributions and insertion schemes.
*/

#include "analysis.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


void analysis::timeAnalysis() {
    const int TOTALNUM = 10000;
    const int INSERT = 1000;
    const int LOWER_BOUND = 100;
    const int UPPER_BOUND = 1000000;
    int numbers[TOTALNUM];


    for (int i = 0; i < TOTALNUM; ++i) {
        numbers[i] = i;
    }

    srand(static_cast<unsigned int>(time(NULL)));

    for (int i = 0; i < TOTALNUM; ++i) {
        numbers[i] = LOWER_BOUND + (rand() % (UPPER_BOUND - LOWER_BOUND + 1));
    }

    BST bst(nullptr, 0);
    clock_t start, end;

    for (int i = 0; i < TOTALNUM; i += INSERT) {
        start = clock();

        for (int j = i; j < i + INSERT && j < TOTALNUM; j++) {
            bst.insertWithoutPrint(numbers[j]);
        }

        end = clock();

        double timeSpent= double(end - start) / CLOCKS_PER_SEC;
        int height = bst.maxTreeHeight(bst.getRoot());

        std::cout << "After " << i + INSERT << " inserts:" << std::endl;
        std::cout << "Time taken: " << timeSpent<< " seconds" << std::endl;
        std::cout << "Tree height: " << height << std::endl << std::endl;
    }
}

void analysis::keepBalance(int *array, int arSize, BST &tree, int arrIndexStart, int arrIndexEnd, clock_t& startTimeClock) {
    static int count =0;
    if(arrIndexStart >= arSize || arrIndexEnd >= arSize || arrIndexStart > arrIndexEnd) return; //i am checking the edge cases

    int middleSearch = arrIndexStart + (arrIndexEnd - arrIndexStart) / 2;
    tree.insertWithoutPrint(array[middleSearch]);
    count++;

    if(count % 1000 == 0){
        clock_t end = clock();
        std::cout << "Time passed after inserting "<< count << " number of elements is ";

        std::cout << double(end - startTimeClock) / CLOCKS_PER_SEC<< " seconds." << std::endl;
        startTimeClock = clock();
    }

    keepBalance(array,10000, tree, arrIndexStart, middleSearch - 1, startTimeClock);
    keepBalance(array,10000, tree, middleSearch + 1, arrIndexEnd, startTimeClock);
}

void analysis::timeBalanceAnalysis() {
    const int TOTALNUM = 10000;
    const int INSERT = 1000;
    int numbers[TOTALNUM];

    for (int i = 0; i < TOTALNUM; ++i) {
        numbers[i] = i;
    }

    BST bst(nullptr, 0);
    clock_t start;

    for (int i = 0; i < TOTALNUM; i += INSERT) {
        start = clock();
        keepBalance(numbers,10000, bst, i, i+9999, start);

    }
}

void analysis::timeAnalysisSorted(){
    const int TOTALNUM = 10000;
    const int INSERT = 1000;
    int numbers[TOTALNUM];

    for (int i = 0; i < TOTALNUM; ++i) {
        numbers[i] = i;
    }

    BST bst(nullptr, 0);
    clock_t start, end;

    for (int i = 0; i < TOTALNUM; i += INSERT) {
        start = clock();
        for (int j = i; j < i + INSERT && j < TOTALNUM; j++) {
            bst.insertWithoutPrint(numbers[j]);
        }
        end = clock();
        double timeSpent= double(end - start) / CLOCKS_PER_SEC;
        int height = bst.maxTreeHeight(bst.getRoot());

        std::cout << "After " << i + INSERT << " inserts:" << std::endl;
        std::cout << "Time taken: " << timeSpent<< " seconds" << std::endl;
        std::cout << "Tree height: " << height << std::endl << std::endl;
    }
}
