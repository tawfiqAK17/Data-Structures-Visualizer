#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "../UIClasses/NodeRect.h"

class Vector {
public:
    Vector(sf::RenderWindow* _window,sf::Font *_font);
    void Parse();
    void Draw();
    void ZoomIn(sf::Vector2i mousePos);
    void ZoomOut(sf::Vector2i mousePos);
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
private:
    std::vector<int> dataStructure{};
    sf::RenderWindow* window;
    sf::Font *font;

    std::vector<std::unique_ptr<NodeRect>> nodes;
};
