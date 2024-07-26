#include <iostream>
#include "Vector.h"


#define MAX_NODE_WIDTH 600

Vector::Vector(sf::RenderWindow *_window, sf::Font *_font) : Visualizer(_window, _font) {
    availableMethods.emplace_back("Push_back");
    availableMethods.emplace_back("Remove");
}

void Vector::Parse() {
    nodes.clear();
    int currentXPos = window->getSize().x / 4 + 50;
    for (auto element: dataStructure) {
        std::unique_ptr<NodeRect> node = std::make_unique<NodeRect>(
                NodeRect(font, element, {static_cast<float>(currentXPos), 500}));
        currentXPos += node->GetRect()->getSize().x;
        nodes.push_back(std::move(node));
    }
}

void Vector::Draw() {
    for (auto &node: nodes) {
        if (node->GetPosition().x > window->getSize().x ||
            node->GetPosition().x + node->GetSize().x < 0 ||
            node->GetPosition().y > window->getSize().y || node->GetPosition().y + node->GetSize().y < 0)
            continue;
        node->Draw(window);
    }
}

void Vector::ZoomIn(sf::Vector2i mousePos) {
    if (dataStructure.empty())
        return;
    if (nodes[0]->GetSize().x < MAX_NODE_WIDTH) {
        int amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
        nodes[0]->MoveLeft(amount);
        auto currentPosition = nodes[0]->GetPosition() - sf::Vector2f(0, nodes[0]->GetSize().y / 8);

        for (auto &node: nodes) {
            node->ZoomIn(currentPosition);
            currentPosition = node->GetPosition() + sf::Vector2f(node->GetRect()->getSize().x, 0);
        }
    }
}

void Vector::ZoomOut(sf::Vector2i mousePos) {
    if (dataStructure.empty())
        return;
    int amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    nodes[0]->MoveRight(amount);
    auto currentPosition = nodes[0]->GetPosition() + sf::Vector2f(0, nodes[0]->GetSize().y / 8);

    for (auto &node: nodes) {
        node->ZoomOut(currentPosition);
        currentPosition += sf::Vector2f(node->GetRect()->getSize().x, 0);
    }
}

void Vector::MethodButtonPressed(int idx, TextHolder *textHolder) {
    switch (idx) {
        case 0:
            dataStructure.push_back(std::stoi(textHolder->GetText().toAnsiString()));
            Parse();
            break;
        case 1:
            auto pos = std::find(dataStructure.begin(), dataStructure.end(), std::stoi(textHolder->GetText().toAnsiString()));
            if (pos == dataStructure.end())
                break;
            dataStructure.erase(pos);
            Parse();
            break;
    }
//    size = dataStructure.size();
}

size_t Vector::GetSize() {
    return dataStructure.size();
}
