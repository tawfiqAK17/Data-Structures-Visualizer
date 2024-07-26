#pragma once
#include "SFML/Graphics.hpp"

class NodeRect {
public:
    NodeRect(sf::Font *font, int data, sf::Vector2f position);
    void Draw(sf::RenderWindow *window);
    void ZoomIn(sf::Vector2f position);
    void ZoomOut(sf::Vector2f position);
    void MoveLeft(int amount = 50);
    void MoveRight(int amount = 50);
    void MoveUp(int amount = 50);
    void MoveDown(int amount = 50);
    [[nodiscard]] sf::RectangleShape* GetRect() const;
    [[nodiscard]] sf::Vector2f GetPosition() const;
    [[nodiscard]] sf::Vector2f GetSize() const;

private:
    std::unique_ptr<sf::RectangleShape> nodeRect;
    std::unique_ptr<sf::Text> nodeText;
};
