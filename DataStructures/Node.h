#pragma once
#include "SFML/Graphics.hpp"
template<class T>
class Node {
public:
    Node(T data, sf::Vector2f position);
    void Draw(sf::RenderWindow *window);
private:
    std::unique_ptr<sf::RectangleShape> nodeRect;
};
