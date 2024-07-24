#pragma once
#include "SFML/Graphics.hpp"
class MainWindow {
public:
    MainWindow();
    void Run();
private:
    void HandelEvents();
    void DrawVisualizationArea();
    void DrawCommandsArea();
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::RectangleShape> visualisationRectangle;
    std::unique_ptr<sf::RectangleShape> commandRectangle;
};
