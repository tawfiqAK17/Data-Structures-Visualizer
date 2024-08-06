#pragma once


#include "NodeRect.hpp"

class Arrow {
public:
    Arrow(NodeRect& from, NodeRect& to);
    void Draw(sf::RenderWindow *window);
    void RePosition();
    void MoveLeft(int amount = 50);
    void MoveRight(int amount = 50);
    void MoveUp(int amount = 50);
    void MoveDown(int amount = 50);
    [[nodiscard]] sf::Vector2f GetPosition() const;
    [[nodiscard]] sf::Vector2f GetSize() const;
private:
    std::unique_ptr<sf::RectangleShape> rectangle;

    NodeRect& from;
    NodeRect& to;
};