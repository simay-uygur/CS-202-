/**
* Title: hashtuple
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : the related tuple structure for double hashing in q1
*/

#include "HashTuple.h"

HashTuple::HashTuple() : hash1(0), hash2(0) {}

HashTuple::HashTuple(long long int h1, long long int h2) : hash1(h1), hash2(h2) {}

bool HashTuple::operator==(const HashTuple &other) const {
    return hash1 == other.hash1 && hash2 == other.hash2;
}
