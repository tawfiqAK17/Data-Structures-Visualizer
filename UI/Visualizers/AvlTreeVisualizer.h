

#pragma once
#include "SFML/Graphics.hpp"
#include "Visualizer.hpp"
#include "../../DataStructures/AvlTree.h"

class AvlTreeVisualizer : public Visualizer {
public:
    AvlTreeVisualizer(sf::RenderWindow* _window, sf::Font *_font);
    void RecursiveParse(AvlTree::Node *node, sf::Vector2f currentPos, sf::Vector2f nodeSize, int nodeIdx);
    void Parse(std::optional<sf::Vector2f> first_node_position, sf::Vector2f nodeSize) override;
    void ZoomIn(sf::Vector2i mousePos) override;
    void ZoomOut(sf::Vector2i mousePos) override;
    std::pair<unsigned long, bool> MethodButtonPressed(int idx, TextHolder *textHolder) override;
private:
    int CalculateTreeWidth(AvlTree::Node *root);
};


