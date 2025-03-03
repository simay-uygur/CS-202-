/**
* Title: Binary Search Trees
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 1
* Description : his is the header file of the binary search tree implementation. It has a TreeNode as a node and that node keeps its key, right and left child.
*/

#ifndef CS_202_HW_1_BST_H
#define CS_202_HW_1_BST_H

#include <string>


class BST {
public:

    struct TreeNode {
        int key;
        TreeNode* left;
        TreeNode* right;
        TreeNode(){}
        TreeNode(int keyVal, TreeNode* leftChild, TreeNode* rightChild): key(keyVal), left(leftChild), right(rightChild){}
    };

    BST(int keys[], int size);
    ~BST();
    void insertKey(int key);
    void deleteKey(int key);
    void displayInorder();
    void findFullBTLevel();
    void lowestCommonAncestor(int A, int B);
    void maximumSumPath();
    void maximumWidth();
    void pathFromAtoB(int A, int B);


    //my methods
    TreeNode *getRoot() const;
    void setRoot(TreeNode *root);
    void insertWithoutPrint( const int key);
    int maxTreeHeight(TreeNode* root);

private:
    TreeNode* root;

    void insertWithoutPItem(TreeNode *& treePtr, const int key);
    int calculateHeightTree(TreeNode* node);
    void countNodesAtLevel(TreeNode* node, int level, int curLevel, int& count);
    void printNodesAtLevel(TreeNode* node, int level, int currentLevel,int& currentCount,int totalCount );
    void deleteItemWithoutPrint(TreeNode*& treePtr, int key);
    TreeNode* lowestCommonRec(TreeNode* node, int a, int b);
    void insertItem(TreeNode *& treePtr, const int key);
    void deleteItem(TreeNode *&treePtr, int key);
    void deleteNodeItem(TreeNode *&nodePtr);
    void processLeftmost(TreeNode *&nodePtr, int &treeItem);
    void processRightmost(TreeNode *&nodePtr, int &treeItem);
    void insertIterative(int key); //silebilirim
    void inorder(TreeNode* treePtr, int& visitedCount, int totalNodes);
    int countNodesAll(TreeNode* node);
    bool containsSpecificKey(int key);
    void maxSumRec(TreeNode* node, int curSum, int& maxSum, TreeNode*& lastNode);
    int findFullBTLevelInt();
    int findLevel(TreeNode* root, int key, int level = 1);
    int levelDifference(TreeNode* root, int key1, int key2);
    void goUpwards(TreeNode* root, int deeperKey, int higherKey);
    TreeNode* findNode(TreeNode* root, int target);
    void goDownwards(TreeNode* root, int deeperKey, int higherKey);
};


#endif //CS_202_HW_1_BST_H

