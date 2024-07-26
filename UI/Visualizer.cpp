
#include <iostream>
#include "Visualizer.h"

Visualizer::Visualizer(sf::RenderWindow *_window, sf::Font *_font) {
    window = _window;
    font = _font;
}

Visualizer::~Visualizer() {
    delete dataStructure;
}

void Visualizer::Parse() {

}

void Visualizer::Draw() {
    for (auto &node: nodes) {
        if (node->GetPosition().x > window->getSize().x ||
            node->GetPosition().x + node->GetSize().x < 0 ||
            node->GetPosition().y > window->getSize().y || node->GetPosition().y + node->GetSize().y < 0)
            continue;

        node->Draw(window);
    }
}

void Visualizer::ZoomIn(sf::Vector2i mousePos) {

}

void Visualizer::ZoomOut(sf::Vector2i mousePos) {

}

void Visualizer::MethodButtonPressed(int idx, TextHolder *textHolder) {
}

void Visualizer::MoveLeft() {
    if (dataStructure->GetSize() == 0)
        return;
    for (auto &node: nodes) {
        node->MoveLeft();
    }
}

void Visualizer::MoveRight() {
    if (dataStructure->GetSize() == 0)
        return;
    for (auto &node: nodes) {
        node->MoveRight();
    }
}

void Visualizer::MoveUp() {
    if (dataStructure->GetSize() == 0)
        return;
    for (auto &node: nodes) {
        node->MoveUp();
    }
}

void Visualizer::MoveDown() {
    if (dataStructure->GetSize() == 0)
        return;
    for (auto &node: nodes) {
        node->MoveDown();
    }
}
