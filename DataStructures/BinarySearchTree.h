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
    bool Remove(int val);
    bool Find(int val);
    bool Clear(); 

    Node* GetRoot() const;
    unsigned long GetSizeInBytes() override;
private:
    Node* RecursiveRemove(Node *node, int val, bool &success);
    int GetSeccesorVal(Node *node);
    Node* RecursiveInsert(Node *node, int val);
    void RecursiveClear(Node *root);
private:
    Node *root = nullptr;
};
