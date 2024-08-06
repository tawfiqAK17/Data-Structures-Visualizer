#pragma once


#include "Visualizer.hpp"

class LinkedListVisualizer : public Visualizer{
public:
    LinkedListVisualizer(sf::RenderWindow* _window, sf::Font *_font);
    void Parse(std::optional<sf::Vector2f> first_node_position, sf::Vector2f size) override;
    void ZoomIn(sf::Vector2i mousePos) override;
    void ZoomOut(sf::Vector2i mousePos) override;
    std::pair<unsigned long, bool> MethodButtonPressed(int idx, TextHolder *textHolder) override;
};
