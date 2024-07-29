//
// Created by tawfiq on 29/07/24.
//

#include "LinkedList.h"

LinkedList::Node::Node(int val, LinkedList::Node *next) : val(val), next(next) {}

bool LinkedList::Push(int val) {
    head = new Node(val, head);
    size++;
    return true;
}

LinkedList::Node *LinkedList::GetHead() const {
    return head;
}

unsigned long LinkedList::GetSizeInBytes() {
    return size * sizeof(Node);
}

bool LinkedList::Pop() {
    if (size == 0)
        return false;
    auto temp = head;
    head = head->next;
    delete temp;
    size--;
    return true;
}
