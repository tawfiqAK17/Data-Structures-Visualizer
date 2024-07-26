#pragma once

#include "SFML/Graphics.hpp"
#include "NodeRect.h"
#include "../DataStructures/DataStructure.h"
#include "TextHolder.h"

class Visualizer {
public:
    Visualizer(sf::RenderWindow *_window, sf::Font *_font);
    virtual ~Visualizer();
    virtual void Parse();
    virtual void Draw();
    virtual void ZoomIn(sf::Vector2i mousePos);
    virtual void ZoomOut(sf::Vector2i mousePos);
    virtual void MethodButtonPressed(int idx, TextHolder *textHolder);
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

    std::vector<std::string> availableMethods;

protected:
    DataStructure *dataStructure;
    sf::RenderWindow* window;

    sf::Font *font;

    std::vector<std::unique_ptr<NodeRect>> nodes;
};
