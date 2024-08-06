#pragma once

#include "SFML/Graphics.hpp"

class StaticText {
public:
    StaticText(sf::RenderWindow* _window, sf::Vector2f position, sf::Vector2f size, sf::String _text, sf::Font *_font);
    void SetText(std::string new_text);
    void Draw();

private:
    sf::RenderWindow *window;
    std::unique_ptr<sf::RectangleShape> rectangle;
    std::unique_ptr<sf::Text> text;
};
