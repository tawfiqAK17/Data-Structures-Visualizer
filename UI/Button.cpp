#include "Button.h"

#include <utility>
#include <iostream>

Button::Button(sf::RenderWindow *_window, sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font *font,
               std::function<void(void)> action) : window(_window), onClick(std::move(action)) {
    buttonRect = std::make_unique<sf::RectangleShape>(sf::RectangleShape(size));
    buttonRect->setPosition(position);
    buttonRect->setFillColor({ 176, 176, 176, 250});
    buttonRect->setOutlineThickness(1);
    buttonRect->setOutlineColor(sf::Color::Black);

    buttonText = std::make_unique<sf::Text>(sf::Text(text, *font));
    buttonText->setCharacterSize(buttonRect->getSize().y / 3);
    buttonText->setPosition(buttonRect->getPosition() + sf::Vector2f(
            buttonRect->getSize().x / 2 - buttonText->getCharacterSize() / 2 * buttonText->getString().getSize() / 2,
            buttonRect->getSize().y / 2 - buttonText->getCharacterSize() / 2));
    buttonText->setFillColor(sf::Color::Black);

}

bool Button::HandelClickEvent(sf::Vector2i mouse_position) {
    if (mouse_position.x > GetPosition().x && mouse_position.x < GetPosition().x + GetSize().x
        && mouse_position.y > GetPosition().y && mouse_position.y < GetPosition().y + GetSize().y
    ) {
        if (onClick)
            onClick();
        return true;
    }
    return false;
}

void Button::Draw() {
    window->draw(*buttonRect);
    window->draw(*buttonText);
}

sf::Vector2f Button::GetPosition() const {
    return buttonRect->getPosition();
}

sf::Vector2f Button::GetSize() const {
    return buttonRect->getSize();
}
