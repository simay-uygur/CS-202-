/**
* Title: hashtuple.h
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : Header of hashtuple
*/


#ifndef HASHTUPLE_H
#define HASHTUPLE_H

class HashTuple {
public:
    long long hash1;
    long long hash2;

    HashTuple() ;
    HashTuple(long long h1, long long h2) ;

    bool operator==(const HashTuple &other) const ;
};

#endif
