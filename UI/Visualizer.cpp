
#include "Visualizer.hpp"
#include <iostream>
#include <chrono>

Visualizer::Visualizer(sf::RenderWindow *_window, sf::Font *_font) {
    window = _window;
    font = _font;
}

Visualizer::~Visualizer() {
    delete dataStructure;
}

unsigned long Visualizer::Benchmark(const std::function<void(void)>& function) {
    auto start = std::chrono::steady_clock::now();
    function();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
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

void Visualizer::MoveLeft() {
    for (auto &node: nodes) {
        node->MoveLeft();
    }
}

void Visualizer::MoveRight() {
    for (auto &node: nodes) {
        node->MoveRight();
    }
}

void Visualizer::MoveUp() {
    for (auto &node: nodes) {
        node->MoveUp();
    }
}

void Visualizer::MoveDown() {
    for (auto &node: nodes) {
        node->MoveDown();
    }
}

size_t Visualizer::GetSizeInBytes() {
    return dataStructure->GetSizeInBytes();
}
