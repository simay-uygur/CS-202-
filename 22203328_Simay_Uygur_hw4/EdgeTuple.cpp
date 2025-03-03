/**
* Title: EdgeTuple.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 4
* Description : The pair class for storing the edges by first and second element.
*/

#include "EdgeTuple.h"

EdgeTuple::EdgeTuple(int source, int destination) : source(source), destination(destination){}

EdgeTuple::EdgeTuple() : source(1e9), destination(1e9) {}

