#pragma once
#include "SFML/Graphics.hpp"

class NodeRect {
public:
    NodeRect(sf::Font *font, int data, sf::Vector2f position, sf::Vector2f size = {10, 9});
    void Draw(sf::RenderWindow *window);
    void MoveLeft(int amount = 50);
    void MoveRight(int amount = 50);
    void MoveUp(int amount = 50);
    void MoveDown(int amount = 50);
    void SetPosition(sf::Vector2f position);
    void SetSize(sf::Vector2f size);
    [[nodiscard]] sf::RectangleShape* GetRect() const;
    [[nodiscard]] sf::Vector2f GetPosition() const;
    [[nodiscard]] sf::Vector2f GetSize() const;

private:
    std::unique_ptr<sf::RectangleShape> nodeRect;
    std::unique_ptr<sf::Text> nodeText;
};
