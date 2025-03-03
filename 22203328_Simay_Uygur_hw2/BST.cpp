/**
* Title: Binary Search Trees
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 1
* Description : Binary Search Tree (BST) data structure is implemented by this code. It contains methods for finding keys, deleting nodes, inserting nodes (both repeatedly and recursively), and performing a variety of tree traversal and analysis tasks. Finding the path between two nodes, computing the maximum breadth, figuring out the maximum sum path, and identifying the lowest common ancestor are among the functions that the BST may do. It also has utility functions for level-based operations, node counting, and tree height computation.
*/

#include "BST.h"
#include <iostream>

using namespace std;


BST::BST() : root(nullptr){}

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
        return;
    } else if (key == treePtr->key) {
        deleteNodeItem(treePtr);
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

void BST::constructBalancedBST(int* array, int arSize, int arrIndexStart, int arrIndexEnd) {
    if(arrIndexStart >= arSize || arrIndexEnd >= arSize || arrIndexStart > arrIndexEnd) return; //i am checking the edge cases

    int middleSearch = arrIndexStart + (arrIndexEnd - arrIndexStart) / 2;
    insertWithoutPrint(array[middleSearch]);

    constructBalancedBST(array, arSize, arrIndexStart, middleSearch - 1);
    constructBalancedBST(array,arSize, middleSearch + 1, arrIndexEnd );
}

void BST::constructBalancedBst(int *array, int arSize) {
    constructBalancedBST(array, arSize, 0, arSize-1);
}

int BST::searchForLessBiggest(int key) {
    TreeNode* cur = root;
    int num = 0;

    while (cur != nullptr ){ //no equality
        num = cur->key;
        if(cur->key < key ){
            if(cur->right != nullptr){
                if(cur->right->key > key){
                    return num;
                } else {
                    cur = cur->right;
                }
            } else {
                return num;
            }
        } else if(cur->key > key ){
            if(cur->left != nullptr){
                cur = cur->left;
            } else {
                return num;
            }
        }

    }

    return num;
}

int BST::getMaxElementPublic() {
    return getMaxElement(root);
}

int BST::getMinElementPublic() {
    return getMinElement(root);
}

int BST::getMaxElement(TreeNode* current) {
    if(current->right == nullptr)
        return current->key;

    return getMaxElement(current->right);
}

int BST::getMinElement(TreeNode* current) {
    if(current->left == nullptr) return current->key;
    return getMinElement(current->left);
}

void BST::deleteTreeRec(BST::TreeNode *cur) {
    if (cur != nullptr) {
        deleteTreeRec(cur->left);
        deleteTreeRec(cur->right);
        delete cur;
    }
}
