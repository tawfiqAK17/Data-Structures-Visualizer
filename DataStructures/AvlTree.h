#include "DataStructure.hpp"
class AvlTree : public DataStructure{
public:
    struct Node {
        Node(int val);
        int val;
        Node *left;
        Node *right;
        int height;
    };
public:
    ~AvlTree();
    bool Insert(int val);
    bool InsertRandom(int number);
    bool Remove(int val);
    bool Find(int val);
    bool Clear();
    Node *GetRoot() const;
    unsigned long GetSizeInBytes() override;
private:
    Node* RecursiveRemove(Node *node, int val, bool &success);
    int GetSeccesorVal(Node *node);
    Node* RecursiveInsert(Node *node, int val);
    void RecursiveClear(Node *root);

    Node *LeftRotation(Node *node);
    Node *RightRotation(Node *node);
    int Height(Node *node);
    void UpdateHeight(Node *node);
    int Balance(Node *node);
    Node *ApplyRotation(Node *node);
private:
    Node *root = nullptr;
};
