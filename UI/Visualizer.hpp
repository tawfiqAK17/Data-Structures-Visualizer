#pragma once

#include "SFML/Graphics.hpp"
#include "NodeRect.hpp"
#include "../DataStructures/DataStructure.hpp"
#include "TextHolder.hpp"
#include "Arrow.h"

#define MAX_NODE_WIDTH 600

class Visualizer {
public:
    Visualizer(sf::RenderWindow *_window, sf::Font *_font);
    virtual ~Visualizer();
    virtual void ParseNodes() = 0;
    virtual void ReParseNodes(sf::Vector2f first_node_position, sf::Vector2f size) = 0;
    void ParseArrows();
    void Draw();
    virtual void ZoomIn(sf::Vector2i mousePos) = 0;
    virtual void ZoomOut(sf::Vector2i mousePos) = 0;
    virtual std::pair<unsigned long, bool> MethodButtonPressed(int idx, TextHolder *textHolder) = 0;
    std::pair<unsigned long, bool> Benchmark(const std::function<bool(void)>& function);
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
    std::vector<std::unique_ptr<Arrow>> arrows;
};
