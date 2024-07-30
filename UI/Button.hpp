#pragma once

#include <functional>
#include "SFML/Graphics.hpp"

class Button {
public:
    Button(sf::RenderWindow* _window, sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font *font, std::function<void(void)> action);
    virtual bool HandelClickEvent(sf::Vector2i mouse_position);
    void SetText(std::string text);
    void Draw();
    [[nodiscard]] sf::Vector2f GetPosition() const;
    [[nodiscard]] sf::Vector2f GetSize() const;

protected:
    sf::RenderWindow *window;
    std::unique_ptr<sf::Text> buttonText;
    std::unique_ptr<sf::RectangleShape> buttonRect;
    std::function<void()> onClick = nullptr;
};