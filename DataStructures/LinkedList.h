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
    bool Push(int val);
    bool Pop();
    bool Remove();
    bool Revers();
    unsigned long GetSizeInBytes() override;

    [[nodiscard]] Node* GetHead() const;
private:
    Node *head = nullptr;
};

