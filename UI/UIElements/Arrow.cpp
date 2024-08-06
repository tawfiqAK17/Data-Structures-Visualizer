#include <valarray>
#include <iostream>
#include "Arrow.h"

Arrow::Arrow(NodeRect &from, NodeRect &to) : from(from), to(to) {
    rectangle = std::make_unique<sf::RectangleShape>();
    sf::Vector2f fromCenter = sf::Vector2f(from.GetPosition().x + from.GetSize().x / 2, from.GetPosition().y + from.GetSize().y / 2); // center of the first node
    sf::Vector2f toCenter = sf::Vector2f(to.GetPosition().x + to.GetSize().x / 2, to.GetPosition().y + to.GetSize().y / 2); // center of the first node

    double length = std::sqrt(pow(std::abs(fromCenter.x - toCenter.x), 2) + pow(std::abs(fromCenter.y - toCenter.y), 2));

    double acosInput = std::min(1.0, std::max(-1.0, std::abs(from.GetPosition().x - to.GetPosition().x) / length));
    double angle = acos(acosInput); // in radian
    if(from.GetPosition().x < to.GetPosition().x)
        rectangle->setRotation(static_cast<float>(angle) * (180 / M_PI));
    else
        rectangle->setRotation(static_cast<float>(-angle) * (180 / M_PI) + 180);

    rectangle->setSize({static_cast<float>(length), from.GetSize().y / 20.f}); // 1 / 20 of the node height is the arrow height
    rectangle->setPosition(fromCenter);

    rectangle->setFillColor(sf::Color::Black);

}

void Arrow::Draw(sf::RenderWindow *window) {
    window->draw(*rectangle);
}

void Arrow::RePosition() {
    sf::Vector2f fromCenter = sf::Vector2f(from.GetPosition().x + from.GetSize().x / 2, from.GetPosition().y + from.GetSize().y / 2); // center of the first node
    sf::Vector2f toCenter = sf::Vector2f(to.GetPosition().x + to.GetSize().x / 2, to.GetPosition().y + to.GetSize().y / 2); // center of the first node

    double length = std::sqrt(pow(std::abs(fromCenter.x - toCenter.x), 2) + pow(std::abs(fromCenter.y - toCenter.y), 2));

    double acosInput = std::min(1.0, std::max(-1.0, std::abs(from.GetPosition().x - to.GetPosition().x) / length));
    double angle = acos(acosInput); // in radian
    if(from.GetPosition().x < to.GetPosition().x)
        rectangle->setRotation(static_cast<float>(angle) * (180 / M_PI));
    else
        rectangle->setRotation(static_cast<float>(-angle) * (180 / M_PI) + 180);

    rectangle->setSize({static_cast<float>(length), from.GetSize().y / 20.f}); // 1 / 20 of the node height is the arrow height
    rectangle->setPosition(fromCenter);
}

void Arrow::MoveLeft(int amount) {
    rectangle->setPosition(rectangle->getPosition() - sf::Vector2f (amount, 0));
}

void Arrow::MoveRight(int amount) {
    rectangle->setPosition(rectangle->getPosition() + sf::Vector2f (amount, 0));
}

void Arrow::MoveUp(int amount) {
    rectangle->setPosition(rectangle->getPosition() - sf::Vector2f (0, amount));
}

void Arrow::MoveDown(int amount) {
    rectangle->setPosition(rectangle->getPosition() + sf::Vector2f (0, amount));
}

sf::Vector2f Arrow::GetSize() const {
    return rectangle->getSize();
}

sf::Vector2f Arrow::GetPosition() const {
    return rectangle->getPosition();
}

