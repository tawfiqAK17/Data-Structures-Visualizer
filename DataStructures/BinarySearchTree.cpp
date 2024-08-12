
#include <cstdlib>
#include "BinarySearchTree.h"

BinarySearchTree::Node::Node(int val) : val(val), left(nullptr), right(nullptr) {};

BinarySearchTree::~BinarySearchTree() {
   Clear();
}

bool BinarySearchTree::Insert(int val) {
    root = RecursiveInsert(root, val);
    size++;
    return true;
}

BinarySearchTree::Node *BinarySearchTree::RecursiveInsert(Node *node, int val) {
    if (!node) {
        return new Node(val);
    }
    if (val < node->val)
        node->left = RecursiveInsert(node->left, val);
    if (val >= node->val)
        node->right = RecursiveInsert(node->right, val);
    return node;
}

bool BinarySearchTree::InsertRandom(int number) {
    for (int i = 0; i < number; i++)
        Insert(rand() % 1000);
    return true;
}

bool BinarySearchTree::Remove(int val) {   
    bool success = true;
    if (!root)
        return false;
    root = RecursiveRemove(root, val, success);
    if (success)
        size--;
    return success;
}

BinarySearchTree::Node* BinarySearchTree::RecursiveRemove(Node *node, int val, bool &success) {
    if (!node) {
        success = false;
        return node;
    }
    if (val > node->val)
        node->right = RecursiveRemove(node->right, val, success);
    else if (val < node->val)
        node->left = RecursiveRemove(node->left, val, success);
    else {
        if (!node->left){
            auto temp = node->right;
            delete node;
            return temp;
        }
        if (!node->right){
            auto temp = node->left;
            delete node;
            return temp;
        }
        int succesor = GetSeccesorVal(node);
        node->val = succesor;
        node->right = RecursiveRemove(node->right, succesor, success);
    }
    return node;
}

int BinarySearchTree::GetSeccesorVal(Node *node) {
    auto temp = node->right;
    while (temp->left) 
       temp = temp->left; 
    return temp->val;
}

bool BinarySearchTree::Find(int val) {
    if (size == 0)
        return false;
    auto temp = root;
    while (temp) {
        if (val < temp->val)
            temp = temp->left;
        else if (val > temp->val)
            temp = temp->right;
        else 
            return true;
    }
    return false;
}
bool BinarySearchTree::Clear() {
    RecursiveClear(root);
    root = nullptr;
    size = 0;
    return true;
}


void BinarySearchTree::RecursiveClear(Node *root) {
    if (!root)
        return;
    if (!root->left && !root->right) {
      delete root;
      return;
    }
    if (root->left)
        RecursiveClear(root->left);
    if (root->right)
        RecursiveClear(root->right);
}
BinarySearchTree::Node *BinarySearchTree::GetRoot() const {
    return root;
}

unsigned long BinarySearchTree::GetSizeInBytes() {
    return size * sizeof(Node);
}
