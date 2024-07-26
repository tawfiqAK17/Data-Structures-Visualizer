#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "../UI/NodeRect.h"
#include "../UI/Visualizer.h"

class Vector : public Visualizer {
public:
    Vector(sf::RenderWindow* _window,sf::Font *_font);
    void Parse() override;
    void Draw() override;
    void ZoomIn(sf::Vector2i mousePos) override;
    void ZoomOut(sf::Vector2i mousePos) override;
    void MethodButtonPressed(int idx, TextHolder *textHolder) override;

    size_t GetSize();
private:
    std::vector<int> dataStructure;
};
