#pragma once

#include "SFML/Graphics.hpp"
#include "NodeRect.hpp"
#include "../DataStructures/DataStructure.hpp"
#include "TextHolder.hpp"

class Visualizer {
public:
    Visualizer(sf::RenderWindow *_window, sf::Font *_font);
    virtual ~Visualizer();
    virtual void Parse();
    virtual void ReParse(sf::Vector2f first_node_position, sf::Vector2f size);
    virtual void Draw();
    virtual void ZoomIn(sf::Vector2i mousePos);
    virtual void ZoomOut(sf::Vector2i mousePos);
    virtual void MethodButtonPressed(int idx, TextHolder *textHolder);
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

    size_t GetSizeInBytes();
    std::vector<std::string> methodsWithArgs;
    std::vector<std::string> methodsWithOutArgs;

protected:
    DataStructure *dataStructure;
    sf::RenderWindow* window;

    sf::Font *font;

    std::vector<std::unique_ptr<NodeRect>> nodes;
};
