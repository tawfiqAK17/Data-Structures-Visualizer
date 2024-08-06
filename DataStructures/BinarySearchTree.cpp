//
// Created by tawfiq on 30/07/24.
//

#include <cstdlib>
#include "BinarySearchTree.h"

BinarySearchTree::Node::Node(int val) : val(val), left(nullptr), right(nullptr) {};

BinarySearchTree::~BinarySearchTree() {

}

bool BinarySearchTree::Insert(int val) {
    root = RecursiveInsert(root, val);
    size++;
    return true;
}

BinarySearchTree::Node *BinarySearchTree::RecursiveInsert(Node *node, int val) {
    if (!node)
        return new Node(val);
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

BinarySearchTree::Node *BinarySearchTree::GetRoot() const {
    return root;
}

unsigned long BinarySearchTree::GetSizeInBytes() {
    return size * sizeof(Node);
}
