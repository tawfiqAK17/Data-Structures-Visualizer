#include <iostream>
#include "LinkedListVisualizer.h"
#include "../../DataStructures/LinkedList.h"

LinkedListVisualizer::LinkedListVisualizer(sf::RenderWindow *_window, sf::Font *_font) : Visualizer(_window, _font) {
    dataStructure = new LinkedList;

    methodsWithArgs.emplace_back("Push");
    methodsWithArgs.emplace_back("Push random");
    methodsWithArgs.emplace_back("Remove");
    methodsWithArgs.emplace_back("Find");
    methodsWithOutArgs.emplace_back("Pop");
    methodsWithOutArgs.emplace_back("Revers");
    methodsWithOutArgs.emplace_back("Clear");
}

void LinkedListVisualizer::Parse(std::optional<sf::Vector2f> first_node_position, sf::Vector2f nodeSize) {
    nodes.clear();
    arrows.clear();
    sf::Vector2f currentPos;
    if (first_node_position.has_value())
        currentPos = first_node_position.value();
    else
        currentPos = sf::Vector2f(window->getSize().x / 4 + 20, window->getSize().y / 2);
    auto temp = dynamic_cast<LinkedList *>(dataStructure)->GetHead();
    while (temp) {
        std::unique_ptr<NodeRect> node = std::make_unique<NodeRect>(
                NodeRect(font, temp->val, currentPos, nodeSize));
        currentPos += sf::Vector2f(3 * node->GetSize().x / 2, 0);
        nodes.push_back(std::move(node));
        if (nodes.size() > 1)
            arrows.push_back(std::make_unique<Arrow>(Arrow(*nodes[nodes.size() - 1], *nodes[nodes.size() - 2])));
        temp = temp->next;
    }
}

void LinkedListVisualizer::ZoomIn(sf::Vector2i mousePos) {
    if (dataStructure->GetSize() == 0)
        return;
    auto size = sf::Vector2f(nodes[0]->GetSize() + sf::Vector2f(nodes[0]->GetSize().x / 4, nodes[0]->GetSize().y / 4));
    float amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    auto position = nodes[0]->GetPosition() - sf::Vector2f(amount, 0);

    Parse(position, size);
}

void LinkedListVisualizer::ZoomOut(sf::Vector2i mousePos) {
    if (dataStructure->GetSize() == 0)
        return;
    auto size = sf::Vector2f(nodes[0]->GetSize() - sf::Vector2f(nodes[0]->GetSize().x / 4, nodes[0]->GetSize().y / 4));
    float amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    auto position = nodes[0]->GetPosition() + sf::Vector2f(amount, 0);

    Parse(position, size);
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
            case 3:
                executionInfo = Benchmark([this, parameter]() {
                    return dynamic_cast<LinkedList *>(dataStructure)->Find(parameter);
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
        Parse({}, {100, 90});
    } else {
        Parse(nodes[0]->GetPosition(), nodes[0]->GetSize());
    }
    return executionInfo;
}
