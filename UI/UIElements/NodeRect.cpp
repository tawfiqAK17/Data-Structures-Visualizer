#include "NodeRect.hpp"


NodeRect::NodeRect(sf::Font *font, int data, sf::Vector2f position, sf::Vector2f size) {
    nodeRect = std::make_unique<sf::RectangleShape>(sf::RectangleShape());
    nodeRect->setSize(size);
    nodeRect->setPosition(position);
    nodeRect->setOutlineThickness(1);
    nodeRect->setOutlineColor(sf::Color::Black);
    nodeRect->setFillColor({255, 218, 185, 255});

    nodeText = std::make_unique<sf::Text>(sf::Text(std::to_string(data), *font));
    nodeText->setFillColor(sf::Color::Black);
}


void NodeRect::Draw(sf::RenderWindow *window) {
    nodeText->setCharacterSize(nodeRect->getSize().y / 3);
    nodeText->setPosition(nodeRect->getPosition() + sf::Vector2f (nodeRect->getSize().x / 2 - nodeText->getCharacterSize() / 2 * nodeText->getString().getSize() / 2, nodeRect->getSize().y / 2 - nodeText->getCharacterSize() / 2));

    window->draw(*nodeRect);
    window->draw(*nodeText);
}

sf::RectangleShape *NodeRect::GetRect() const {

    return nodeRect.get();
}

void NodeRect::MoveLeft(int amount) {
    nodeRect->setPosition(nodeRect->getPosition() - sf::Vector2f (amount, 0));
}

void NodeRect::MoveRight(int amount) {
    nodeRect->setPosition(nodeRect->getPosition() + sf::Vector2f (amount, 0));
}

void NodeRect::MoveUp(int amount) {
    nodeRect->setPosition(nodeRect->getPosition() - sf::Vector2f (0, amount));
}

void NodeRect::MoveDown(int amount) {
    nodeRect->setPosition(nodeRect->getPosition() + sf::Vector2f (0, amount));
}

void NodeRect::SetPosition(sf::Vector2f position) {
    nodeRect->setPosition(position);
}

void NodeRect::SetSize(sf::Vector2f size) {
    nodeRect->setSize(size);
}

sf::Vector2f NodeRect::GetSize() const {
    return nodeRect->getSize();
}

sf::Vector2f NodeRect::GetPosition() const {
    return nodeRect->getPosition();
}
