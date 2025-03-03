/**
* Title: insorders.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : Header of insorders
*/
#include "InsOrders.h"
#include <iostream>

InsOrders::InsOrders() : twoAntiMPow(1), threeAntiMPow(1), sixAntiMPow(1), MOD(1000000009), resultArray(nullptr) {// MOD(1000000009)
    precompute();

}

void InsOrders::precompute() {

    twoAntiMPow = 500000005;
    threeAntiMPow = 666666673;
    sixAntiMPow = 833333341;

}

long long InsOrders::calculateInsertionOrderPermutations(int size, int *&inputArrInts) {

    resultArray = new int[size + 2];

    int validInputNumbers = 0;
    for (int i = 0; i < size; ++i) {
        if(inputArrInts[i] != -1){
            validInputNumbers++;
        }
    }

    fillResultArray(size, inputArrInts);
    long long permResult = -1;


    permResult = calculateFactorial(validInputNumbers);

    resultArray[size] = resultArray[0];
    resultArray[size + 1] = resultArray[1];

    for (int i = 0; i < size; ++i) {  //+ başa döndürecek bi bakmam lazım çarpmak da lazım *size-1 ile olacak o sanırım
        if (resultArray[i] == 0) {
            if (resultArray[i + 1] == 0 && resultArray[i + 2] == 2) { //002     divide by three pow3 umarım
                permResult = (permResult * threeAntiMPow) % MOD;
                i += 2; //umarım
            } else if ((resultArray[i + 1] == 1 && resultArray[i + 2] == 2) ||
                    (resultArray[i + 1] == 1 && resultArray[i + 2] == 1)) { //012 veya 011 divide by 6
                permResult = (permResult * sixAntiMPow) % MOD;
                i += 2;
            } else if ((resultArray[i + 1] == 1 && resultArray[i + 2] == 0) || (resultArray[i + 1] == 1 &&  resultArray[i + 2] == -1)) {
                permResult = (permResult * twoAntiMPow) % MOD;
                i += 1;
            }
        }
    }


    delete[] resultArray;
    return permResult;
}

long long InsOrders::calculateFactorial(int n) {
    long long factResult = 1;
    for (int i = 1; i <= n; ++i) {
        factResult = (factResult *i ) % MOD;
    }
    return factResult;
}

InsOrders::~InsOrders() {
    //delete gerek var mı
}


void InsOrders::fillResultArray(int const& size, int*& inputArrInts){
    for (int i = 0; i < size; ++i) {
        int modulo = inputArrInts[i] % size;
        int thePositionExpected = i - modulo;
        if (thePositionExpected < 0) {
            thePositionExpected += size;
        }
        resultArray[i] = thePositionExpected;
    }
}
