//
// Created by tawfiq on 29/07/24.
//

#include <cstdlib>
#include "LinkedList.h"

LinkedList::Node::Node(int val, LinkedList::Node *next) : val(val), next(next) {}

LinkedList::~LinkedList() {
    while (head){
        delete head;
        head = head->next;
    }
}


bool LinkedList::Push(int val) {
    head = new Node(val, head);
    size++;
    return true;
}

bool LinkedList::PushRandom(int number) {
    for (int i = 0; i < number; i++) {
        Push(rand() % 1000);
    }
    return true;
}

bool LinkedList::Remove(int val) {
    auto temp = head;
    if (head->val == val) {
        head = head->next;
        delete temp;
        size--;
        return true;
    }
    while (temp->next) {
        if (temp->next->val == val) {
            auto helper = temp->next;
            temp->next = temp->next->next;
            delete helper;
            size--;
            return true;
        }
        temp = temp->next;
    }
    if (temp->val == val) {
        delete temp;
        temp = nullptr;
        size--;
        return true;
    }
    return false;
}

bool LinkedList::Revers() {
    if (size == 0)
        return true;
    auto current = head;
    auto next = head->next;
    Node *previous = nullptr;
    while (true) {
        current->next = previous;
        previous = current;
        if (!next)
            break;
        current = next;
        next = current->next;
    }
    head = current;
    return true;
}

bool LinkedList::Clear() {
    while (head) {
        auto temp = head;
        head = temp->next;
        delete temp;
    }
    size = 0;
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
