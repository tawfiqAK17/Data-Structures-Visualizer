#pragma once


#include <memory>
#include "SFML/Graphics.hpp"

class TextHolder {
public:
    TextHolder(sf::RenderWindow* _window, sf::Vector2f position, sf::Vector2f size, sf::String place_holder, sf::Font *_font);
    bool HandelClickEvent(sf::Vector2i mouse_position);
    void Draw() const;
    void ChangeState(bool _inUse);
    void SetText(std::string new_text);

    [[nodiscard]] int GetStringAsInt() const;
    [[nodiscard]] bool GetState() const;
    [[nodiscard]] sf::Vector2f GetPosition() const;
    [[nodiscard]] sf::Vector2f GetSize() const;
    sf::String GetText();
private:
    sf::RenderWindow *window;

    std::unique_ptr<sf::RectangleShape> rectangle;
    std::unique_ptr<sf::Text> text;
    bool inUse = false;
};
