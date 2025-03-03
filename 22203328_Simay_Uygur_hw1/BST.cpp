/**
* Title: Binary Search Trees
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 1
* Description : A Binary Search Tree (BST) data structure is implemented by this code. It contains methods for finding keys, deleting nodes, inserting nodes (both repeatedly and recursively), and performing a variety of tree traversal and analysis tasks. Finding the path between two nodes, computing the maximum breadth, figuring out the maximum sum path, and identifying the lowest common ancestor are among the functions that the BST may do. It also has utility functions for level-based operations, node counting, and tree height computation.
*/

#include "BST.h"
#include <iostream>

using namespace std;

BST::BST(int keys[], int size) {
    if (size <= 0 || keys == nullptr) {
        root = nullptr;
        cout << "BST with size " << size << " is created." << endl;
        return;
    }

    TreeNode *newNode = new TreeNode(keys[0], nullptr, nullptr);
    setRoot(newNode);

    for (int i = 1; i < size; i++) {
        insertWithoutPrint(keys[i]);
    }
    cout << "BST with size " << size << " is created." << endl;
}

BST::~BST() {
    while (root != nullptr) {
        deleteItemWithoutPrint(root, root->key);
    }
}

void BST::insertWithoutPrint(const int key) {
    insertWithoutPItem(root, key);
}

void BST::insertWithoutPItem(TreeNode *&treePtr, const int key) {
    if (treePtr == nullptr) {
        treePtr = new TreeNode(key, nullptr, nullptr);
    } else if (key < treePtr->key) {
        insertWithoutPItem(treePtr->left, key);
    } else if (key > treePtr->key) {
        insertWithoutPItem(treePtr->right, key);
    } else {
        return;
    }
}

void BST::insertKey(int key) {
    insertItem(root, key);
}

void BST::insertItem(TreeNode *&treePtr, const int key) {
    if (treePtr == nullptr) {
        treePtr = new TreeNode(key, nullptr, nullptr);
        cout << "Key " << key << " is added." << endl;
    } else if (key < treePtr->key) {
        insertItem(treePtr->left, key);
    } else if (key > treePtr->key) {
        insertItem(treePtr->right, key);
    } else {
        cout << "Key " << key << " is not added. It exists!" << endl;
        return;
    }

}

void BST::deleteKey(int key) {
    deleteItem(root, key);
}

void BST::deleteItem(TreeNode *&treePtr, int key) {
    if (treePtr == nullptr) {
        cout << "Key " << key << " is not deleted. It does not exist!" << endl;
        return;
    } else if (key == treePtr->key) {
        deleteNodeItem(treePtr);
        cout << "Key " << key << " is deleted." << endl;
        //return de eklenebilir de gerek yok
    } else if (key < treePtr->key) {
        deleteItem(treePtr->left, key);
    } else {
        deleteItem(treePtr->right, key);
    }
}

void BST::deleteItemWithoutPrint(BST::TreeNode *&treePtr, int key) {
    if (treePtr == nullptr) {
        return;
    } else if (key == treePtr->key) {
        deleteNodeItem(treePtr);
    } else if (key < treePtr->key) {
        deleteItem(treePtr->left, key);
    } else {
        deleteItem(treePtr->right, key);
    }
}

void BST::deleteNodeItem(TreeNode *&nodePtr) {
    TreeNode *delPtr;
    int replacementItem;

    if ((nodePtr->left == nullptr) &&
        (nodePtr->right == nullptr)) {
        delete nodePtr;
        nodePtr = nullptr;
    } else if (nodePtr->left == nullptr) {
        delPtr = nodePtr;
        nodePtr = nodePtr->right;
        delPtr->right = nullptr;
        delete delPtr;
    } else if (nodePtr->right == nullptr) {
        processRightmost(nodePtr->left, replacementItem);
        nodePtr->key = replacementItem;
    } else {
        processLeftmost(nodePtr->right, replacementItem);
        nodePtr->key = replacementItem;
    }
}

void BST::processLeftmost(TreeNode *&nodePtr, int &treeItem) {
    if (nodePtr->left == nullptr) {
        treeItem = nodePtr->key;
        TreeNode *delPtr = nodePtr;
        nodePtr = nodePtr->right;
        delPtr->right = nullptr;
        delete delPtr;
    } else
        processLeftmost(nodePtr->left, treeItem);
}

void BST::processRightmost(TreeNode *&nodePtr, int &treeItem) {
    if (nodePtr->right == nullptr) {
        treeItem = nodePtr->key;
        TreeNode *delPtr = nodePtr;
        nodePtr = nodePtr->left;
        delPtr->left = nullptr;
        delete delPtr;
    } else {
        processRightmost(nodePtr->right, treeItem);
    }
}

void BST::displayInorder() {
    int totalNodes = countNodesAll(root);
    int visitedCount = 0;
    cout << "Inorder display is: ";
    inorder(root, visitedCount, totalNodes);
    cout << endl;
}

void BST::inorder(TreeNode *treePtr, int &visitedCount, int totalNodes) {
    if (treePtr != nullptr) {
        inorder(treePtr->left, visitedCount, totalNodes);

        cout << treePtr->key;
        visitedCount++;

        if (visitedCount < totalNodes) {
            cout << ", ";
        }

        inorder(treePtr->right, visitedCount, totalNodes);
    }
}

bool BST::containsSpecificKey(int key) {
    TreeNode *current = this->root;

    while (current != nullptr) {
        if (key == current->key) {
            return true;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}


int BST::findFullBTLevelInt() {
    if (root == nullptr) {
        return 0;
    }

    int h = maxTreeHeight(root);
    int fullLevel = 0;

    for (int i = 1; i <= h; i++) {
        int count = 0;
        countNodesAtLevel(root, i - 1, 0, count);  // i - 1
        int expectedNodesAtFullLevel = 1 << (i - 1);

        if (count != expectedNodesAtFullLevel && count != 0) {
            break;
        }

        fullLevel = i;
    }

    return fullLevel;
}

void BST::findFullBTLevel() {
    int fullLevel = findFullBTLevelInt();
    cout << "Full binary tree level is: " << fullLevel << endl;
}

void BST::lowestCommonAncestor(int A, int B) {
    bool foundA = containsSpecificKey(A);
    bool foundB = containsSpecificKey(B);

    if (!foundA || !foundB) {
        cout << "Error: One or both keys (A, B) do not exist in the tree." << endl;
    }

    TreeNode *found = lowestCommonRec(root, A, B);
    int foundKey = -1;
    if (found != nullptr)
        foundKey = found->key;
    cout << "Lowest common ancestor of " << A << " and " << B << " is: " << foundKey << endl;
}

BST::TreeNode *BST::lowestCommonRec(TreeNode *node, int a, int b) {

    if (node == nullptr || node->key == a || node->key == b || (a < node->key && b > node->key) ||
        (a > node->key && b < node->key)) {
        return node;
    } else if (a < node->key && b < node->key) {
        TreeNode *old = node;
        node = node->left;
        TreeNode *lowest = lowestCommonRec(node, a, b);
        if (lowest == nullptr) {
            return old;
        }
        return lowest;
    } else if (a > node->key && b > node->key) {
        TreeNode *old = node;
        node = node->right;
        TreeNode *lowest = lowestCommonRec(node, a, b);
        if (lowest == nullptr) {
            return old;
        }
        return lowest;
    }
    return nullptr;

}

void BST::maximumSumPath() {
    int maxSum = -10000000; //instead of int min

    cout << "Maximum sum path is: ";
    if (root == nullptr) return;
    TreeNode *endPathNode = nullptr;
    maxSumRec(root, 0, maxSum, endPathNode);

    TreeNode *current = root;
    //node keys are not equal assumtion
    while (current->key != endPathNode->key) {
        cout << current->key;
        cout << ", ";

        if (current->key > endPathNode->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << current->key;
    cout << endl;
}

void BST::maxSumRec(TreeNode *node, int curSum, int &maxSum, TreeNode *&lastNode) {
    if (node == nullptr)
        return;

    curSum += node->key;

    if (node->left == nullptr && node->right == nullptr) {
        if (curSum > maxSum) {
            maxSum = curSum;
            lastNode = node;
        }
        return;
    }

    maxSumRec(node->left, curSum, maxSum, lastNode);
    maxSumRec(node->right, curSum, maxSum, lastNode);
}

void BST::maximumWidth() {
    int h = calculateHeightTree(root);
    int maxWidth = 0;
    int maxWidthLevel = 0;

    for (int i = 0; i < h; i++) {
        int count = 0;
        countNodesAtLevel(root, i, 0, count);
        if (count > maxWidth) {
            maxWidth = count;
            maxWidthLevel = i;
        }
    }

    cout << "Maximum level is: ";
    int currentCountNode = 0;
    printNodesAtLevel(root, maxWidthLevel, 0, currentCountNode, maxWidth);

    cout << endl;
}

void BST::pathFromAtoB(int A, int B) {
    bool foundA = containsSpecificKey(A);
    bool foundB = containsSpecificKey(B);

    if (!foundA || !foundB) {
        cout << "Error: One or both keys (A, B) do not exist in the tree." << endl;
        return;
    }

    TreeNode *ancestor = lowestCommonRec(root, A, B);
    if(ancestor == nullptr) return ;

    int ansKey = ancestor->key;
    cout << "Path from " << A << " to " << B << " is: ";

    if (ansKey == A && ansKey == B) {
        cout << A << endl;
        return;
    }

    if (ansKey == A && ansKey != B) {
        cout << ansKey;
        cout << ", ";
        goDownwards(ancestor, B, A);

    } else if (ansKey == B && ansKey != A) {
        goUpwards(ancestor, A, B);
        //cout << ", ";
        cout<< ansKey;
    } else if ( A <ansKey && ansKey < B ){
        goUpwards(ancestor, A, ansKey);
        cout << ansKey;
        cout << ", ";
        goDownwards(ancestor, B, ansKey);
    } else if(B < ansKey && ansKey < A){
        goUpwards(ancestor, A, ansKey);
        cout<< ansKey;
        cout<<", ";
        goDownwards(ancestor, B, ansKey);
    }
    cout << endl;
}

int BST::calculateHeightTree(TreeNode *node) {
    if (node == nullptr)
        return 0;
    int max = calculateHeightTree(node->right);
    int left = calculateHeightTree(node->left);
    if (max < left)
        max = left;
    return 1 + max;
}

void BST::countNodesAtLevel(TreeNode *node, int level, int curLevel, int &count) {
    if (node == nullptr)
        return;

    if (curLevel == level) {
        count++;
        return;
    }

    countNodesAtLevel(node->left, level, curLevel + 1, count);
    countNodesAtLevel(node->right, level, curLevel + 1, count);
}

void BST::printNodesAtLevel(TreeNode *node, int level, int currentLevel, int &currentCount, int totalCount) {
    if (node == nullptr) return;
    if (currentLevel == level) {
        cout << node->key;
        currentCount++;
        if (currentCount < totalCount) {
            cout << ", ";
        }
        return;
    }
    printNodesAtLevel(node->left, level, currentLevel + 1, currentCount, totalCount);
    printNodesAtLevel(node->right, level, currentLevel + 1, currentCount, totalCount);
}

BST::TreeNode *BST::getRoot() const {
    return root;
}

void BST::setRoot(TreeNode *root) {
    BST::root = root;
}

int BST::maxTreeHeight(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = maxTreeHeight(root->left);
    int rightHeight = maxTreeHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int BST::countNodesAll(TreeNode *node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + countNodesAll(node->left) + countNodesAll(node->right);
}

int BST::findLevel(TreeNode *root, int key, int level) {
    if (root == nullptr) {
        return 0;
    }

    if (root->key == key) {
        return level;
    }

    if (key < root->key) {
        return findLevel(root->left, key, level + 1);
    } else {
        return findLevel(root->right, key, level + 1);
    }
}

//l1 -l2
int BST::levelDifference(TreeNode *root, int key1, int key2) {
    int level1 = findLevel(root, key1);
    int level2 = findLevel(root, key2);

    if (level1 == -1 || level2 == -1) {
        return 0;
    }

    return level1 - level2;
}

void BST::goUpwards(TreeNode* root, int deeperKey, int higherKey) {
    TreeNode* current = findNode(root, deeperKey);
    TreeNode* target = findNode(root, higherKey);
    if(target == nullptr|| current == nullptr) return;

    int levelDiff = levelDifference(root, deeperKey, higherKey); //d - h
    TreeNode* tempTraversalNode = target;
    while (levelDiff > 0  ) {

        tempTraversalNode = target;

        int count = levelDiff ;

        while(count > 0 && tempTraversalNode != nullptr){
            if(deeperKey < tempTraversalNode->key){
                tempTraversalNode = tempTraversalNode->left;
            } else {
                tempTraversalNode = tempTraversalNode->right;
            }
            count--;
        }
        levelDiff--;
        if(tempTraversalNode != nullptr || levelDiff!= 0) {
            cout << tempTraversalNode->key;
            cout << ", ";
        }

    }

}

void BST::goDownwards(TreeNode* root, int deeperKey, int higherKey){
    TreeNode* current = findNode(root, higherKey);
    if(current == nullptr) return;

    if (current->key > deeperKey) {
        current = current->left;
    } else {
        current = current->right;
    }
    if(current == nullptr) return; //to defense

    while (current->key != deeperKey){
        cout << current->key;

        if (current->key > deeperKey) {
            current = current->left;
        } else {
            current = current->right;
        }

        cout << ", ";
    }

    cout << current->key; //the last one
}

BST::TreeNode* BST::findNode(TreeNode* root, int target) {
    if (root == nullptr || root->key == target) {
        return root;
    }
    if (target < root->key) {
        return findNode(root->left, target);
    } else {
        return findNode(root->right, target);
    }
}

