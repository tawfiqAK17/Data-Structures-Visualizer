
#include <iostream>
#include <queue>
#include "BinarySearchTreeVisualizer.h"

int CalculateTreeWidth(BinarySearchTree::Node *root);

BinarySearchTreeVisualizer::BinarySearchTreeVisualizer(sf::RenderWindow *_window, sf::Font *_font) : Visualizer(_window,
                                                                                                                _font) {
    dataStructure = new BinarySearchTree;


    methodsWithArgs.emplace_back("Insert");
    methodsWithArgs.emplace_back("Insert random");

    std::cout << CalculateTreeWidth(dynamic_cast<BinarySearchTree *>(dataStructure)->GetRoot()) << "\n";
}


void BinarySearchTreeVisualizer::Parse(std::optional<sf::Vector2f> first_node_position, sf::Vector2f nodeSize) {
    nodes.clear();
    arrows.clear();
    sf::Vector2f currentPos;
    if (first_node_position.has_value())
        currentPos = first_node_position.value();
    else
        currentPos = sf::Vector2f(3 * window->getSize().x / 4 - 100, 20);
    if (dataStructure->GetSize() == 0)
        return;
    auto head = dynamic_cast<BinarySearchTree *>(dataStructure)->GetRoot();
    RecursiveParse(head, currentPos, nodeSize, 0);

    for (auto &arrow: arrows)
        arrow->RePosition();
}

void
BinarySearchTreeVisualizer::RecursiveParse(BinarySearchTree::Node *node, sf::Vector2f currentPos, sf::Vector2f nodeSize,
                                           int nodeIdx) {
    for (auto &node: nodes) {
        if (node->GetPosition() == currentPos) {
            node->SetPosition(currentPos - sf::Vector2f(node->GetSize().x, 0));
        }
    }

    int width = std::max(CalculateTreeWidth(node->left), CalculateTreeWidth(node->right));
    nodes.push_back(std::make_unique<NodeRect>(NodeRect(font, node->val, currentPos, nodeSize)));

    if (node->left) {
        RecursiveParse(node->left, currentPos + sf::Vector2f(-width * nodes[0]->GetSize().x, 2 * nodes[0]->GetSize().y),
                       nodeSize, nodeIdx + 1);

        arrows.push_back(std::make_unique<Arrow>(Arrow(*nodes[nodeIdx], *nodes[nodeIdx + 1])));
    }
    if (node->right) {
        int i = nodes.size();
        RecursiveParse(node->right, currentPos + sf::Vector2f(width * nodes[0]->GetSize().x, 2 * nodes[0]->GetSize().y),
                       nodeSize, i);

        arrows.push_back(std::make_unique<Arrow>(Arrow(*nodes[nodeIdx], *nodes[i])));
    }
}


void BinarySearchTreeVisualizer::ZoomIn(sf::Vector2i mousePos) {
    auto size = sf::Vector2f(nodes[0]->GetSize() + sf::Vector2f(nodes[0]->GetSize().x / 4, nodes[0]->GetSize().y / 4));

    float xAmount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    float yAmount = ((mousePos.y - nodes[0]->GetPosition().y) / nodes[0]->GetSize().y) * nodes[0]->GetSize().y / 4;
    auto position = nodes[0]->GetPosition() - sf::Vector2f(xAmount, yAmount);
    if (size.x < MAX_NODE_WIDTH)
        Parse(position, size);
}

void BinarySearchTreeVisualizer::ZoomOut(sf::Vector2i mousePos) {
    auto size = sf::Vector2f(nodes[0]->GetSize() - sf::Vector2f(nodes[0]->GetSize().x / 4, nodes[0]->GetSize().y / 4));

    float xAmount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    float yAmount = ((mousePos.y - nodes[0]->GetPosition().y) / nodes[0]->GetSize().y) * nodes[0]->GetSize().y / 4;
    auto position = nodes[0]->GetPosition() + sf::Vector2f(xAmount, yAmount);

    Parse(position, size);
}

std::pair<unsigned long, bool> BinarySearchTreeVisualizer::MethodButtonPressed(int idx, TextHolder *textHolder) {
    std::pair<unsigned long, bool> executionInfo = {};
    if (textHolder) { // call to a method with args
        int parameter = textHolder->GetStringAsInt();
        switch (idx) {
            case 0:
                executionInfo = Benchmark([this, parameter]() {
                    return dynamic_cast<BinarySearchTree *>(dataStructure)->Insert(parameter);
                });
                break;
            case 1:
                executionInfo = Benchmark([this, parameter]() {
                    return dynamic_cast<BinarySearchTree *>(dataStructure)->InsertRandom(parameter);
                });
                break;
        }
    }

    if (nodes.empty()) {
        Parse({}, {100, 90});
    } else {
        Parse(nodes[0]->GetPosition(), nodes[0]->GetSize());
    }
    return executionInfo;
}

int BinarySearchTreeVisualizer::CalculateTreeWidth(BinarySearchTree::Node *root) {
    if (!root) return 0;

    int maxWidth = 1;
    std::queue<BinarySearchTree::Node *> q;

    // Start with the root node
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at the current level
        maxWidth = std::max(maxWidth, levelSize);

        // Process all nodes at the current level
        for (int i = 0; i < levelSize; ++i) {
            auto currentNode = q.front();
            q.pop();

            if (currentNode->left) q.push(currentNode->left);
            if (currentNode->right) q.push(currentNode->right);
            if (!currentNode->right || !currentNode->left)
                maxWidth += 1;
        }
    }
    return maxWidth;
}

