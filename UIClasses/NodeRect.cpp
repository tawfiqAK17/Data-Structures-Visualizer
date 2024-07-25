#include "NodeRect.h"


NodeRect::NodeRect(int data, sf::Vector2f position) {
    nodeRect = std::make_unique<sf::RectangleShape>(sf::RectangleShape());
    nodeRect->setSize(sf::Vector2f (200, 90));
    nodeRect->setPosition(position);
    nodeRect->setOutlineThickness(1);
    nodeRect->setOutlineColor(sf::Color::Black);
    nodeRect->setFillColor({255, 218, 185, 255});


    nodeFont = std::make_unique<sf::Font>(sf::Font());
    nodeFont->loadFromFile("font.ttf");

    nodeText = std::make_unique<sf::Text>(sf::Text(std::to_string(data), *nodeFont));
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

void NodeRect::ZomIn(sf::Vector2f position) {
    nodeRect->setSize(nodeRect->getSize() + sf::Vector2f(nodeRect->getSize().x / 4, nodeRect->getSize().y / 4));
    nodeRect->setPosition(position);
}

void NodeRect::ZomOut(sf::Vector2f position) {
    nodeRect->setSize(nodeRect->getSize() - sf::Vector2f(nodeRect->getSize().x / 4, nodeRect->getSize().y / 4));
    nodeRect->setPosition(position);
}

sf::Vector2f NodeRect::GetPosition() const {
    return nodeRect->getPosition();
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

sf::Vector2f NodeRect::GetSize() const {
    return nodeRect->getSize();
}
