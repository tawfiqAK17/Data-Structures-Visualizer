#pragma once
#include "SFML/Graphics.hpp"
#include "../DataStructures/Vector.h"

class MainWindow {
public:
    MainWindow();
    void Run();
private:
    void HandelEvents();
    void DrawVisualizationArea() const;
    void DrawCommandsArea() const;
private:
    Vector *vec;

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::RectangleShape> visualisationRectangle;
    std::unique_ptr<sf::RectangleShape> commandsRectangle;
};
