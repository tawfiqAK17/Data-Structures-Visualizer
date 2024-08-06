#pragma once

#include "DataStructure.hpp"

class BinarySearchTree : public DataStructure {
public:
    struct Node {
        explicit Node(int val);
        int val;
        Node *left;
        Node *right;
    };
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() override;
    bool Insert(int val);
    bool InsertRandom(int number);

    Node* GetRoot() const;
    unsigned long GetSizeInBytes() override;
private:
    Node* RecursiveInsert(Node *node, int val);
private:
    Node *root = nullptr;
};
