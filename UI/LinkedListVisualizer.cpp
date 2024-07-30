#include <iostream>
#include "LinkedListVisualizer.h"
#include "../DataStructures/LinkedList.h"

LinkedListVisualizer::LinkedListVisualizer(sf::RenderWindow *_window, sf::Font *_font) : Visualizer(_window, _font) {
    dataStructure = new LinkedList;

    methodsWithArgs.emplace_back("Push");
    methodsWithArgs.emplace_back("Push random");
    methodsWithArgs.emplace_back("Remove");
    methodsWithOutArgs.emplace_back("Pop");
    methodsWithOutArgs.emplace_back("Revers");
    methodsWithOutArgs.emplace_back("Clear");
}

void LinkedListVisualizer::ParseNodes() {
    sf::Vector2f currentPos = sf::Vector2f(window->getSize().x / 4 + 50, 500);

    auto head = dynamic_cast<LinkedList *>(dataStructure)->GetHead();
    if (!head)
        return;
    auto temp = head;
    while (temp) {
        std::unique_ptr<NodeRect> node = std::make_unique<NodeRect>(
                NodeRect(font, temp->val, currentPos));

        currentPos += sf::Vector2f(3 * node->GetSize().x / 2, 0);
        nodes.push_back(std::move(node));
        temp = temp->next;
    }

    ParseArrows();
}

void LinkedListVisualizer::ReParseNodes(sf::Vector2f first_node_position, sf::Vector2f size) {
    nodes.clear();
    sf::Vector2f currentPos = first_node_position;
    auto temp = dynamic_cast<LinkedList *>(dataStructure)->GetHead();
    while (temp) {
        std::unique_ptr<NodeRect> node = std::make_unique<NodeRect>(
                NodeRect(font, temp->val, currentPos, size));
        currentPos += sf::Vector2f(3 * node->GetSize().x / 2, 0);
        nodes.push_back(std::move(node));
        temp = temp->next;
    }
    ParseArrows();
}

void LinkedListVisualizer::ZoomIn(sf::Vector2i mousePos) {
    if (dataStructure->GetSize() == 0)
        return;
    if (nodes[0]->GetSize().x < MAX_NODE_WIDTH) {
        int amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
        nodes[0]->MoveLeft(amount);
        auto currentPosition = nodes[0]->GetPosition() - sf::Vector2f(0, nodes[0]->GetSize().y / 8);

        for (auto &node: nodes) {
            node->ZoomIn(currentPosition);
            currentPosition = node->GetPosition() + sf::Vector2f(3 * node->GetRect()->getSize().x / 2, 0);
        }
        ParseArrows();
    }
}

void LinkedListVisualizer::ZoomOut(sf::Vector2i mousePos) {
    if (dataStructure->GetSize() == 0)
        return;
    int amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    nodes[0]->MoveRight(amount);
    auto currentPosition = nodes[0]->GetPosition() + sf::Vector2f(0, nodes[0]->GetSize().y / 8);

    for (auto &node: nodes) {
        node->ZoomOut(currentPosition);
        currentPosition = node->GetPosition() + sf::Vector2f(3 * node->GetRect()->getSize().x / 2, 0);
    }
    ParseArrows();
}

std::pair<unsigned long, bool> LinkedListVisualizer::MethodButtonPressed(int idx, TextHolder *textHolder) {
    std::pair<unsigned long, bool> executionInfo = {};
    if (textHolder) { // call to a method with args
        int parameter = textHolder->GetStringAsInt();
        switch (idx) {
            case 0:
                executionInfo = Benchmark([this, parameter]() {
                    return dynamic_cast<LinkedList *>(dataStructure)->Push(parameter);
                });
                break;
            case 1:
                executionInfo = Benchmark([this, parameter]() {
                    return dynamic_cast<LinkedList *>(dataStructure)->PushRandom(parameter);
                });
                break;
            case 2:
                executionInfo = Benchmark([this, parameter]() {
                    return dynamic_cast<LinkedList *>(dataStructure)->Remove(parameter);
                });
                break;
        }
    } else {
        switch (idx) {
            case 0:
                executionInfo = Benchmark([this]() {
                    return dynamic_cast<LinkedList *>(dataStructure)->Pop();
                });
                break;
            case 1:
                executionInfo = Benchmark([this]() {
                    return dynamic_cast<LinkedList *>(dataStructure)->Revers();
                });
                break;
            case 2:
                executionInfo = Benchmark([this]() {
                    return dynamic_cast<LinkedList *>(dataStructure)->Clear();
                });
                break;
        }
    }
    if (nodes.empty()) {
        ParseNodes();
    }
    else {
        ReParseNodes(nodes[0]->GetPosition(), nodes[0]->GetSize());
    }
    return executionInfo;
}
