#include <iostream>
#include "ArrayVisualizer.hpp"


#define MAX_NODE_WIDTH 600

ArrayVisualizer::ArrayVisualizer(sf::RenderWindow *_window, sf::Font *_font) : Visualizer(_window, _font) {

    dataStructure = new Array;

    methodsWithArgs.emplace_back("Push_back");
    methodsWithArgs.emplace_back("Remove");
    methodsWithArgs.emplace_back("Add Random");

    methodsWithOutArgs.emplace_back("Clear");

}

void ArrayVisualizer::Parse() {
    sf::Vector2f currentPos = sf::Vector2f(window->getSize().x / 4 + 50, 500);

    for (int i = 0; i < dataStructure->GetSize(); i++) {
        Array *const pArray = dynamic_cast<Array *>(dataStructure);
        std::unique_ptr<NodeRect> node = std::make_unique<NodeRect>(
                NodeRect(font, (*pArray)[i], currentPos));

        currentPos += sf::Vector2f(node->GetSize().x, 0);
        nodes.push_back(std::move(node));
    }
}

void ArrayVisualizer::ReParse(sf::Vector2f first_node_position, sf::Vector2f size) {
    nodes.clear();
    sf::Vector2f currentPos = first_node_position;

    for (int i = 0; i < dataStructure->GetSize(); i++) {
        Array *const pArray = dynamic_cast<Array *>(dataStructure);
        std::unique_ptr<NodeRect> node = std::make_unique<NodeRect>(
                NodeRect(font, (*pArray)[i], currentPos, size));
        currentPos += sf::Vector2f(node->GetSize().x, 0);
        nodes.push_back(std::move(node));
    }
}

void ArrayVisualizer::Draw() {
    for (auto &node: nodes) {
        if (node->GetPosition().x > window->getSize().x ||
            node->GetPosition().x + node->GetSize().x < 0 ||
            node->GetPosition().y > window->getSize().y || node->GetPosition().y + node->GetSize().y < 0)
            continue;
        node->Draw(window);
    }
}

void ArrayVisualizer::ZoomIn(sf::Vector2i mousePos) {
    if (dataStructure->GetSize() == 0)
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

void ArrayVisualizer::ZoomOut(sf::Vector2i mousePos) {
    if (dataStructure->GetSize() == 0)
        return;
    int amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    nodes[0]->MoveRight(amount);
    auto currentPosition = nodes[0]->GetPosition() + sf::Vector2f(0, nodes[0]->GetSize().y / 8);

    for (auto &node: nodes) {
        node->ZoomOut(currentPosition);
        currentPosition += sf::Vector2f(node->GetRect()->getSize().x, 0);
    }
}

void ArrayVisualizer::MethodButtonPressed(int idx, TextHolder *textHolder) {
    if (textHolder) { // call to a method with args
        int number = std::stoi(textHolder->GetText().toAnsiString());
        switch (idx) {
            case 0:
                dynamic_cast<Array *>(dataStructure)->Add(number);
                break;
            case 1:
                dynamic_cast<Array *>(dataStructure)->remove(number);
                break;
            case 2:
                for (int i = 0; i < number; i++) {
                    dynamic_cast<Array *>(dataStructure)->Add(rand());
                }
                break;
        }
    } else { // call to a method without args
        switch (idx) {
            case 0:
                dynamic_cast<Array *>(dataStructure)->Clear();
                break;
        }
    }
    if (nodes.empty())
        Parse();
    else {
        ReParse(nodes[0]->GetPosition(), nodes[0]->GetSize());
    }
}

