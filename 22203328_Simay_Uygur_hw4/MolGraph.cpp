/**
* Title: MolGraph.cpp
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 4
* Description : Using adjacency list, it traverses with bfs finding thi minimum  bond between the pairs, calculates the diameter by using bfs for each vertex and taking the maximum. For the mst, it kinda uses prims algorithm but with a queue.
*/


#include "MolGraph.h"

/*#include "QueHeap.cpp"
#include "EdgeTupleQueue.cpp"
#include "EdgeTuple.cpp"*/
#include <fstream>
#include <iostream>



MolGraph::MolGraph(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'." << std::endl;
        return;
    }

    inputFile >> numAtoms;

    adjacencyListGraph = new Node*[numAtoms];

    for (int i = 0; i < numAtoms; ++i) {
        adjacencyListGraph[i] = nullptr;
    }


    int atomId, degree, neighborId;
    Node* curNode;
    for (int i = 0; i < numAtoms; ++i) {

        inputFile >> atomId;
        inputFile >> degree;
        adjacencyListGraph[atomId] = new Node(atomId);
        curNode = adjacencyListGraph[atomId];

        for (int i = 0; i < degree; ++i) {
            inputFile >> neighborId;
            Node* newNode = new Node(neighborId);
            curNode->next = newNode;
            curNode = newNode;
        }
    }

    distArray = new int[numAtoms];
    inputFile.close();
}


MolGraph::~MolGraph() {
    for (int i = 0; i < numAtoms; ++i) {
        Node* curNode = adjacencyListGraph[i];

        while (curNode) {
            Node* delNode = curNode;
            curNode = curNode->next;
            delete delNode;
        }
    }
    delete[] adjacencyListGraph;
    delete[] distArray;

}


void MolGraph::minBondPath(int source, int destination) {
    int distance = searchMinPathBf(source, destination);
    std::cout << std::endl;

    if (distance == -1) {
        std::cout << "No path exists between atoms " << source << " and " << destination << "." << std::endl;
    }

}
void MolGraph::getDiameter() {
    int dia = calculateGraphDiameter();
    std::cout << "Diameter of the molecule: " << dia << std::endl;
}

void MolGraph::getMST() {

    computeMST();
}

int MolGraph::searchMinPathBf(int source, int destination) {
    clearDistances();

    distArray[source] = 0;

    int* parArray = new int[numAtoms];
    for (int i = 0; i < numAtoms; ++i) {
        parArray[i] = -1;
    }

    QueHeap queueOrder(numAtoms + 10);
    int order = 0;
    queueOrder.addElementToHeap(order, source);

    while (!queueOrder.heapIsEmpty()) {
        queStruct current = queueOrder.getTopElValue();
        queueOrder.deleteElementTopFromHeap();

        for (Node* neighbor = adjacencyListGraph[current.index]; neighbor != nullptr; neighbor = neighbor->next) {
            if (distArray[neighbor->id] == -1) {
                distArray[neighbor->id] = distArray[current.index] + 1;
                parArray[neighbor->id] = current.index;
                queueOrder.addElementToHeap(++order, neighbor->id);

                if (neighbor->id == destination) {
                    int result = distArray[neighbor->id];
                    std::cout << "Minimum number of bonds to traverse from atom " << source
                              << " to atom " << destination << ": " << result << std::endl;

                    std::cout << "Path: ";
                    printPathFromParent(parArray, source, destination);
                    delete[] parArray;
                    return result;
                }
            }
        }
    }


    delete[] parArray;
    return -1;
}

void MolGraph::printPathFromParent(int* pArray, int source, int destination) {
    if (source == destination) {
        std::cout << source;
        return;
    }

    printPathFromParent(pArray, source, pArray[destination]);
    std::cout << " -> " << destination;
}


void MolGraph::computeMST() {
    clearDistances();
    distArray[0] = 0;

    int sizeQ = ((numAtoms * (numAtoms-1)) / 2) + 1;


    EdgeTupleQueue edgeQueue(sizeQ);  // old size= numAtoms + 10


    for (Node* neighbor = adjacencyListGraph[0]; neighbor != nullptr; neighbor = neighbor->next) {
        edgeQueue.addElementToHeap(EdgeTuple(0, neighbor->id));
    }

    EdgeTuple mstEdges[100005];
    int curInEdges = 0;
    int totalCost = 0;

    while (!edgeQueue.heapIsEmpty()) {
        EdgeTuple edge = edgeQueue.getTopElValue();
        edgeQueue.deleteElementTopFromHeap();

        if (distArray[edge.destination] != -1) continue;

        mstEdges[curInEdges] = edge;
        curInEdges++;
        totalCost++;

        distArray[edge.destination] = 0;

        for (Node* neighbor = adjacencyListGraph[edge.destination]; neighbor != nullptr; neighbor = neighbor->next) {
            if (distArray[neighbor->id] == -1) {
                edgeQueue.addElementToHeap(EdgeTuple(edge.destination, neighbor->id));

            }
        }
    }
    //swapping
    for (int i = 0; i < totalCost; ++i) {
        int source = mstEdges[i].source ;
        int dest = mstEdges[i].destination;
        if (mstEdges[i].source > mstEdges[i].destination) {
            mstEdges[i].source = dest;
            mstEdges[i].destination = source;
        }
    }

    std::cout << "Minimum Spanning Tree:" << std::endl;
    std::cout << "Cost: " << totalCost << std::endl;
    std::cout << "Edges:" << std::endl;

    int num = numAtoms - 1;
    mergeSort(mstEdges, 0, num);

    for (int i = 0; i < totalCost; ++i) {
        EdgeTuple edge = mstEdges[i];
        std::cout << edge.source << " - " << edge.destination << std::endl;
    }
}

int MolGraph::calculateGraphDiameter() {

    int diameter = 0;

    for (int start = 0; start < numAtoms; ++start) {

        clearDistances();

        QueHeap queueOrder(numAtoms + 10);
        queueOrder.addElementToHeap(0, start);

        distArray[start] = 0;
        int curOrder = 0;

        while (!queueOrder.heapIsEmpty()) {
            queStruct current = queueOrder.getTopElValue();
            queueOrder.deleteElementTopFromHeap();

            int currentNode = current.index;

            for (Node* neighbor = adjacencyListGraph[currentNode]; neighbor != nullptr; neighbor = neighbor->next) {
                if (distArray[neighbor->id] == -1) {
                    distArray[neighbor->id] = distArray[currentNode] + 1;
                    queueOrder.addElementToHeap(++curOrder, neighbor->id);

                    if (distArray[neighbor->id] > diameter) {
                        diameter = distArray[neighbor->id];
                    }
                }
            }
        }
    }


    return diameter;
}


void MolGraph::merge(EdgeTuple theArray[], int first, int mid, int last) {
    EdgeTuple* tempArray = new EdgeTuple[last - first + 1];
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = 0;


    while (first1 <= last1 && first2 <= last2) {
        if (theArray[first1].source < theArray[first2].source ||
            (theArray[first1].source == theArray[first2].source && theArray[first1].destination < theArray[first2].destination)) {
            tempArray[index++] = theArray[first1++];
        } else {
            tempArray[index++] = theArray[first2++];
        }
    }


    while (first1 <= last1) {
        tempArray[index++] = theArray[first1++];
    }
    while (first2 <= last2) {
        tempArray[index++] = theArray[first2++];
    }
    for (int i = 0; i < index; ++i) {
        theArray[first + i] = tempArray[i];
    }

    delete[] tempArray;
}

void MolGraph::mergeSort(EdgeTuple theArray[], int first, int last) {
    if (first < last) {
        int mid = (first + last) / 2;

        mergeSort(theArray, first, mid);
        mergeSort(theArray, mid + 1, last);

        merge(theArray, first, mid, last);
    }
}

void MolGraph::clearDistances() {
    for (int i = 0; i < numAtoms; ++i) {
        distArray[i] = -1;
    }
}
