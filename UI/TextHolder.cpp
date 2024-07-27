//
// Created by tawfiq on 26/07/24.
//

#include <iostream>
#include "TextHolder.hpp"

TextHolder::TextHolder(sf::RenderWindow *_window, sf::Vector2f position, sf::Vector2f size, sf::String place_holder,
                       sf::Font *_font) : window(_window){
    rectangle = std::make_unique<sf::RectangleShape>(sf::RectangleShape(size));
    rectangle->setPosition(position);
    rectangle->setFillColor({ 250, 250, 250, 250});
    rectangle->setOutlineThickness(1);
    rectangle->setOutlineColor(sf::Color::Black);

    text = std::make_unique<sf::Text>(sf::Text(place_holder, *_font));
    text->setCharacterSize(rectangle->getSize().y / 3);
    text->setPosition(rectangle->getPosition() + sf::Vector2f(
            rectangle->getSize().x / 2 - text->getCharacterSize() / 2 * text->getString().getSize() / 2,
            rectangle->getSize().y / 2 - text->getCharacterSize() / 2));
    text->setFillColor(sf::Color::Green);
}

void TextHolder::SetText(std::string new_text) {
    text->setString(new_text);
    text->setPosition(rectangle->getPosition() + sf::Vector2f(
            rectangle->getSize().x / 2 - text->getCharacterSize() / 2 * new_text.size() / 2,
            rectangle->getSize().y / 2 - text->getCharacterSize() / 2));
}

bool TextHolder::HandelClickEvent(sf::Vector2i mouse_position) {
    if (mouse_position.x > GetPosition().x && mouse_position.x < GetPosition().x + GetSize().x
        && mouse_position.y > GetPosition().y && mouse_position.y < GetPosition().y + GetSize().y
            ) {
        ChangeState(true);
        return true;
    }
    return false;
}

void TextHolder::Draw() const {
    if (inUse)
        text->setFillColor({0, 0, 0, 255});
    else
        text->setFillColor({0, 0, 0, 100});
    window->draw(*rectangle);
    window->draw(*text);
}

bool TextHolder::GetState() const {
    return inUse;
}

void TextHolder::ChangeState(bool _inUse) {
    inUse = _inUse;
}

sf::Vector2f TextHolder::GetPosition() const {
    return rectangle->getPosition();
}

sf::Vector2f TextHolder::GetSize() const {
    return rectangle->getSize();
}

sf::String TextHolder::GetText() {
    return text->getString();
}
