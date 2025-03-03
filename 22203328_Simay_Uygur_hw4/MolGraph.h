/**
 * Title: MolGraph.h
 * Author: Simay Uygur
 * ID: 22203328
 * Section: 1
 * Homework: 4
 * Description: Header file for the MolGraph class. Contains node representing a single node (atom) in the adjacency list of the  graph. Contains an ID and a pointer to the next node.
 */

#ifndef MOLGRAPH_H
#define MOLGRAPH_H

#include <string>

#include "QueHeap.h"
#include "EdgeTupleQueue.h"
#include "EdgeTuple.h"


struct Node {
    int id;
    Node* next;

    Node(int id) : id(id), next(nullptr) {}
};
class MolGraph {
public:
    MolGraph(const std::string& filename);
    ~MolGraph();

    void minBondPath(int source, int destination);
    void getDiameter();
    void getMST();

private:
    int numAtoms;
    Node ** adjacencyListGraph;
    int* distArray;

    int searchMinPathBf(int source, int destination);
    int calculateGraphDiameter();
    void computeMST();

    void printPathFromParent(int *pArray, int source, int destination);

    void mergeSort(EdgeTuple *theArray, int first, int last);

    void clearDistances();
    void merge(EdgeTuple *theArray, int first, int mid, int last);
};

#endif
