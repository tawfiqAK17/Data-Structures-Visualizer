#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "NodeRect.hpp"
#include "Visualizer.hpp"
#include "../DataStructures/Array.hpp"

class ArrayVisualizer : public Visualizer {
public:
    ArrayVisualizer(sf::RenderWindow* _window, sf::Font *_font);
    void Parse() override;
    void ReParse(sf::Vector2f first_node_position, sf::Vector2f size) override;
    void Draw() override;
    void ZoomIn(sf::Vector2i mousePos) override;
    void ZoomOut(sf::Vector2i mousePos) override;
    unsigned long MethodButtonPressed(int idx, TextHolder *textHolder) override;

};
