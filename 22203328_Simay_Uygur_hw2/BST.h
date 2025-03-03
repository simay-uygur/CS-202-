/**
* Title: Binary Search Trees
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 1
* Description : This is the header file of the binary search tree implementation. It has a TreeNode as a node and that node keeps its key, right and left child.
*/

#ifndef INC_202_HW_2_BST_H
#define INC_202_HW_2_BST_H

#include <string>


class BST {
public:

    struct TreeNode {
        int key;
        TreeNode* left;
        TreeNode* right;
        TreeNode():key(-1), left(nullptr), right(nullptr){}
        TreeNode(int keyVal, TreeNode* leftChild, TreeNode* rightChild): key(keyVal), left(leftChild), right(rightChild){}
    };

    BST(int keys[], int size);
    BST();
    ~BST();
    void insertKey(int key);
    void deleteKey(int key);
    void displayInorder();

    void constructBalancedBst(int* array, int arSize);

    TreeNode *getRoot() const;
    void setRoot(TreeNode *root);
    void insertWithoutPrint( const int key);
    int maxTreeHeight(TreeNode* root);

    int searchForLessBiggest(int key);

    int getMaxElementPublic();
    int getMinElementPublic();

private:
    TreeNode* root;

    void insertWithoutPItem(TreeNode *& treePtr, const int key);
    int calculateHeightTree(TreeNode* node);
    void countNodesAtLevel(TreeNode* node, int level, int curLevel, int& count);
    void printNodesAtLevel(TreeNode* node, int level, int currentLevel,int& currentCount,int totalCount );
    void deleteItemWithoutPrint(TreeNode*& treePtr, int key);

    void insertItem(TreeNode *& treePtr, const int key);
    void deleteItem(TreeNode *&treePtr, int key);
    void deleteNodeItem(TreeNode *&nodePtr);
    void processLeftmost(TreeNode *&nodePtr, int &treeItem);
    void processRightmost(TreeNode *&nodePtr, int &treeItem);
    void inorder(TreeNode* treePtr, int& visitedCount, int totalNodes);
    int countNodesAll(TreeNode* node);
    bool containsSpecificKey(int key);
    int findLevel(TreeNode* root, int key, int level = 1);
    int levelDifference(TreeNode* root, int key1, int key2);
    TreeNode* findNode(TreeNode* root, int target);

    void constructBalancedBST(int *array, int arSize, int arrIndexStart, int arrIndexEnd);

    int getMaxElement(TreeNode* current);
    int getMinElement(TreeNode* current);
    void deleteTreeRec(TreeNode* cur);
};


#endif

