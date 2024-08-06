
#include "Visualizer.hpp"
#include <iostream>
#include <chrono>

#define MAX_NODE_WIDTH 600

Visualizer::Visualizer(sf::RenderWindow *_window, sf::Font *_font) {
    window = _window;
    font = _font;
}

Visualizer::~Visualizer() {
    delete dataStructure;
}

std::pair<unsigned long, bool> Visualizer::Benchmark(const std::function<bool(void)> &function) {
    auto start = std::chrono::steady_clock::now();
    auto fun_return_state = function();
    auto end = std::chrono::steady_clock::now();
    return {std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(), fun_return_state};
}

void Visualizer::Draw() {
    for (auto &arrow: arrows) {
        if (arrow->GetPosition().x > window->getSize().x + arrow->GetSize().x||
            arrow->GetPosition().x + arrow->GetSize().x < 0 ||
            arrow->GetPosition().y > window->getSize().y || arrow->GetPosition().y + arrow->GetSize().y < 0)
            continue;
        arrow->Draw(window);
    }
    for (auto &node: nodes) {
        if (node->GetPosition().x > window->getSize().x ||
            node->GetPosition().x + node->GetSize().x < 0 ||
            node->GetPosition().y > window->getSize().y || node->GetPosition().y + node->GetSize().y < 0) {
            continue;
        }

        node->Draw(window);
    }
}

void Visualizer::MoveLeft() {
    for (auto &node: nodes) {
        node->MoveLeft();
    }
    for (auto &arrow: arrows) {
        arrow->MoveLeft();
    }
}

void Visualizer::MoveRight() {
    for (auto &node: nodes) {
        node->MoveRight();
    }
    for (auto &arrow: arrows) {
        arrow->MoveRight();
    }
}

void Visualizer::MoveUp() {
    for (auto &node: nodes) {
        node->MoveUp();
    }
    for (auto &arrow: arrows) {
        arrow->MoveUp();
    }
}

void Visualizer::MoveDown() {
    for (auto &node: nodes) {
        node->MoveDown();
    }
    for (auto &arrow: arrows) {
        arrow->MoveDown();
    }
}

size_t Visualizer::GetSizeInBytes() {
    return dataStructure->GetSizeInBytes();
}
