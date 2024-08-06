#include <iostream>
#include "ArrayVisualizer.hpp"



ArrayVisualizer::ArrayVisualizer(sf::RenderWindow *_window, sf::Font *_font) : Visualizer(_window, _font) {

    dataStructure = new Array;

    methodsWithArgs.emplace_back("Add");
    methodsWithArgs.emplace_back("Add Random");
    methodsWithArgs.emplace_back("Remove");
    methodsWithArgs.emplace_back("Remove at");
    methodsWithArgs.emplace_back("Find");

    methodsWithOutArgs.emplace_back("Bubble sort");
    methodsWithOutArgs.emplace_back("Selection sort");
    methodsWithOutArgs.emplace_back("Merge sort");
    methodsWithOutArgs.emplace_back("Quick sort (not yet)");
    methodsWithOutArgs.emplace_back("Clear");

}

void ArrayVisualizer::Parse(std::optional<sf::Vector2f> first_node_position, sf::Vector2f nodeSize) {
    nodes.clear();
    sf::Vector2f currentPos;
    if (first_node_position.has_value())
        currentPos = first_node_position.value();
    else
        currentPos = sf::Vector2f(window->getSize().x / 4 + 20, window->getSize().y / 2);

    Array *const pArray = dynamic_cast<Array *>(dataStructure);
    for (int i = 0; i < dataStructure->GetSize(); i++) {
        std::unique_ptr<NodeRect> node = std::make_unique<NodeRect>(
                NodeRect(font, (*pArray)[i], currentPos, nodeSize));
        currentPos += sf::Vector2f(node->GetSize().x, 0);
        nodes.push_back(std::move(node));
    }
}

void ArrayVisualizer::ZoomIn(sf::Vector2i mousePos) {
    if (dataStructure->GetSize() == 0)
        return;
    auto size = sf::Vector2f(nodes[0]->GetSize() + sf::Vector2f(nodes[0]->GetSize().x / 4, nodes[0]->GetSize().y / 4));
    float amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    auto position = nodes[0]->GetPosition() - sf::Vector2f(amount, 0);

    Parse(position, size);
}

void ArrayVisualizer::ZoomOut(sf::Vector2i mousePos) {
    if (dataStructure->GetSize() == 0)
        return;
    auto size = sf::Vector2f(nodes[0]->GetSize() - sf::Vector2f(nodes[0]->GetSize().x / 4, nodes[0]->GetSize().y / 4));
    float amount = ((mousePos.x - nodes[0]->GetPosition().x) / nodes[0]->GetSize().x) * nodes[0]->GetSize().x / 4;
    auto position = nodes[0]->GetPosition() + sf::Vector2f(amount, 0);

    Parse(position, size);
}

std::pair<unsigned long, bool> ArrayVisualizer::MethodButtonPressed(int idx, TextHolder *textHolder) {
    std::pair<unsigned long, bool> executionInfo = {};
    if (textHolder) { // call to a method with args
        int parameter = textHolder->GetStringAsInt();
        switch (idx) {
            case 0:
                executionInfo = Benchmark(
                        [this, parameter]() { return dynamic_cast<Array *>(dataStructure)->Add(parameter); });
                break;
            case 1:
                executionInfo = Benchmark(
                        [this, parameter]() { return dynamic_cast<Array *>(dataStructure)->AddRandom(parameter); });
                break;
            case 2:
                executionInfo = Benchmark(
                        [this, parameter]() { return dynamic_cast<Array *>(dataStructure)->Remove(parameter); });
                break;
            case 3:
                executionInfo = Benchmark(
                        [this, parameter]() { return dynamic_cast<Array *>(dataStructure)->RemoveAt(parameter); });
                break;
            case 4:
                executionInfo = Benchmark(
                        [this, parameter]() { return dynamic_cast<Array *>(dataStructure)->Find(parameter); });
                break;
        }
    } else { // call to a method without args
        switch (idx) {
            case 0:
                executionInfo = Benchmark([this]() { return dynamic_cast<Array *>(dataStructure)->BubbleSort(); });
                break;
            case 1:
                executionInfo = Benchmark([this]() { return dynamic_cast<Array *>(dataStructure)->SelectionSort(); });
                break;
            case 2:
                executionInfo = Benchmark([this]() { return dynamic_cast<Array *>(dataStructure)->MergeSort(); });
                break;
            case 4:
                executionInfo = Benchmark([this]() { return dynamic_cast<Array *>(dataStructure)->Clear(); });
                break;
        }
    }
    if (nodes.empty())
        Parse({}, {100, 90});
    else {
        Parse(nodes[0]->GetPosition(), nodes[0]->GetSize());
    }
    return executionInfo;
}


