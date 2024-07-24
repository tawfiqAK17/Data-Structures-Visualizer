#include "Node.h"

template<class T>
Node<T>::Node(T data, sf::Vector2f position) {
    nodeRect = std::make_unique<sf::RectangleShape>(sf::RectangleShape({50, 50}));
    nodeRect->setPosition(position);
}

template<class T>
void Node<T>::Draw(sf::RenderWindow *window) {
    window->draw(*nodeRect);
}
