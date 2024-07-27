//
// Created by tawfiq on 27/07/24.
//

#include "StaticText.hpp"

StaticText::StaticText(sf::RenderWindow *_window, sf::Vector2f position, sf::Vector2f size, sf::String _text,
                       sf::Font *_font) : window(_window) {

    rectangle = std::make_unique<sf::RectangleShape>(sf::RectangleShape(size));
    rectangle->setPosition(position);
    rectangle->setFillColor({ 250, 250, 250, 250});
    rectangle->setOutlineThickness(1);
    rectangle->setOutlineColor(sf::Color::Black);

    text = std::make_unique<sf::Text>(sf::Text(_text, *_font));
    text->setCharacterSize(rectangle->getSize().y / 3);
    text->setPosition(rectangle->getPosition() + sf::Vector2f(
            rectangle->getSize().x / 2 - text->getCharacterSize() / 2 * text->getString().getSize() / 2,
            rectangle->getSize().y / 2 - text->getCharacterSize() / 2));
    text->setFillColor(sf::Color::Black);
}

void StaticText::SetText(std::string new_text) {
    text->setString(new_text);
    text->setPosition(rectangle->getPosition() + sf::Vector2f(
            rectangle->getSize().x / 2 - text->getCharacterSize() / 2 * new_text.size() / 2,
            rectangle->getSize().y / 2 - text->getCharacterSize() / 2));
}

void StaticText::Draw() {
    window->draw(*rectangle);
    window->draw(*text);
}
