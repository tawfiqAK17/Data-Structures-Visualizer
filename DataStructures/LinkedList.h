#pragma once

#include <SFML/System/Vector2.hpp>
#include "DataStructure.hpp"


class LinkedList : public DataStructure{
private:
    struct Node {
        Node() = default;
        Node(int val, Node *next);
        int val;
        Node *next;
    };
public:
    ~LinkedList() override;
    bool Push(int val);
    bool PushRandom(int number);
    bool Pop();
    bool Remove(int val);
    bool Revers();
    bool Clear();
    unsigned long GetSizeInBytes() override;

    [[nodiscard]] Node* GetHead() const;
private:
    Node *head = nullptr;
};

