#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "../UIClasses/NodeRect.h"

class Vector {
public:
    Vector(sf::RenderWindow* _window);
    void Parse();
    void Draw();
    void ZomIn(sf::Vector2i mousePos);
    void ZomOut(sf::Vector2i mousePos);
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
private:
    std::vector<int> dataStructure{};
    sf::RenderWindow* window;

    std::vector<std::unique_ptr<NodeRect>> nodes;
};
