#include "AvlTree.h"
#include <algorithm>
#include <cstdlib>

AvlTree::Node::Node(int val) : val(val), left(nullptr), right(nullptr), height(1) {}



AvlTree::~AvlTree() {
   Clear();
}

bool AvlTree::Insert(int val) {
    root = RecursiveInsert(root, val);
    size++;
    return true;
}

AvlTree::Node *AvlTree::RecursiveInsert(Node *node, int val) {
    if (!node) {
        return new Node(val);
    }
    if (val < node->val)
        node->left = RecursiveInsert(node->left, val);
    if (val >= node->val)
        node->right = RecursiveInsert(node->right, val);
    UpdateHeight(node);
    return ApplyRotation(node);
}

bool AvlTree::InsertRandom(int number) {
    for (int i = 0; i < number; i++)
        Insert(rand() % 1000);
    return true;
}

bool AvlTree::Remove(int val) {   
    bool success = true;
    if (!root)
        return false;
    root = RecursiveRemove(root, val, success);
    if (success)
        size--;
    return success;
}

AvlTree::Node* AvlTree::RecursiveRemove(Node *node, int val, bool &success) {
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
    UpdateHeight(node);
    return ApplyRotation(node);
}

int AvlTree::GetSeccesorVal(Node *node) {
    auto temp = node->right;
    while (temp->left) 
       temp = temp->left; 
    return temp->val;
}

bool AvlTree::Find(int val) {
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
bool AvlTree::Clear() {
    RecursiveClear(root);
    root = nullptr;
    size = 0;
    return true;
}


void AvlTree::RecursiveClear(Node *root) {
    if (!root)
        return;
    if (root->left)
        RecursiveClear(root->left);
    if (root->right)
        RecursiveClear(root->right);
    delete root;
}

AvlTree::Node *AvlTree::LeftRotation(Node *node) {
    auto right = node->right;
    auto left = right->left;
    right->left = node;
    node->right = left;
    UpdateHeight(node);
    UpdateHeight(right);
    return right;
}
AvlTree::Node *AvlTree::RightRotation(Node *node) {
    auto left = node->left;
    auto right = left->right;
    left->right = node;
    node->left = right; 
    UpdateHeight(node);
    UpdateHeight(left);
    return left;
}

int AvlTree::Height(Node *node) {
    return node ? node->height : 0;
}
int AvlTree::Balance(Node *node) {
    return Height(node->left) - Height(node->right);
}
void AvlTree::UpdateHeight(Node *node) {
        node->height = std::max(Height(node->left), Height(node->right)) + 1; 
}

AvlTree::Node *AvlTree::ApplyRotation(Node *node) {
    int balance = Balance(node);
    if (balance > 1) {
        if (Balance(node->left) < 0)
            node->left = LeftRotation(node->left);
        return RightRotation(node);
    }
    if (balance < -1) {
        if (Balance(node->right) > 0)
            node->right = RightRotation(node->right);
        return LeftRotation(node);
    }
    return node;
}
AvlTree::Node *AvlTree::GetRoot() const {
    return root;
}

unsigned long AvlTree::GetSizeInBytes() {
    return size * sizeof(Node);
}
