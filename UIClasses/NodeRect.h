#pragma once
#include "SFML/Graphics.hpp"

class NodeRect {
public:
    NodeRect(int data, sf::Vector2f position);
    void Draw(sf::RenderWindow *window);
    void ZomIn(sf::Vector2f position);
    void ZomOut(sf::Vector2f position);
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
    std::unique_ptr<sf::Font> nodeFont;
};
