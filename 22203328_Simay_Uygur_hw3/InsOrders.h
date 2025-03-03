/**
* Title: insorders.h
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : header of insertion orders q5
*/

#ifndef INSERTION_ORDERS_H
#define INSERTION_ORDERS_H

class InsOrders {
private:
    long long twoAntiMPow;
    long long threeAntiMPow;
    long long sixAntiMPow;
    long long MOD ;
    int* resultArray;

public:
    InsOrders();
    ~InsOrders();

    void precompute();
    long long calculateInsertionOrderPermutations(int size, int *&inputArrInts);
    long long int calculateFactorial(int n);

    void fillResultArray(const int &size, int *&inputArrInts);
};

#endif
