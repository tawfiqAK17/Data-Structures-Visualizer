#include <iostream>
#include <memory>
#include "MainWindow.h"

MainWindow::MainWindow() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Data Structures Virtulizer", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition({0, 0});


    visualisationRectangle = std::make_unique<sf::RectangleShape>(sf::RectangleShape({static_cast<float>(window->getSize().x) * 3.f / 4,static_cast<float>(window->getSize().y)}));
    visualisationRectangle->setPosition(window->getSize().x / 4, 0);
    visualisationRectangle->setFillColor({242, 243, 244, 200});
    visualisationRectangle->setOutlineThickness(2);
    visualisationRectangle->setOutlineColor(sf::Color::Black);

    commandRectangle = std::make_unique<sf::RectangleShape>(sf::RectangleShape({static_cast<float>(window->getSize().x) / 4,static_cast<float>(window->getSize().y)}));
    commandRectangle->setPosition(0, 0);
    commandRectangle->setFillColor({169, 169, 169, 255});
}

void MainWindow::Run() {
    while (window->isOpen()) {
        HandelEvents();
        window->clear();
        DrawCommandsArea();
        DrawVisualizationArea();
        window->display();
    }
}

void MainWindow::HandelEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void MainWindow::DrawVisualizationArea() {
    window->draw(*visualisationRectangle);
}

void MainWindow::DrawCommandsArea() {
    window->draw(*commandRectangle);
}
