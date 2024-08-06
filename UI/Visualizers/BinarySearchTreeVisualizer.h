
#pragma once

#include "Visualizer.hpp"
#include "../../DataStructures/BinarySearchTree.h"

class BinarySearchTreeVisualizer : public Visualizer {
public:
    BinarySearchTreeVisualizer(sf::RenderWindow* _window, sf::Font *_font);
    void RecursiveParse(BinarySearchTree::Node *node, sf::Vector2f currentPos, sf::Vector2f nodeSize, int nodeIdx);
    void Parse(std::optional<sf::Vector2f> first_node_position, sf::Vector2f nodeSize) override;
    void ZoomIn(sf::Vector2i mousePos) override;
    void ZoomOut(sf::Vector2i mousePos) override;
    std::pair<unsigned long, bool> MethodButtonPressed(int idx, TextHolder *textHolder) override;
private:
    int CalculateTreeWidth(BinarySearchTree::Node *root);
};


