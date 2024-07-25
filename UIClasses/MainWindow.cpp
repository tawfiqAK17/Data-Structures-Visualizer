#include <iostream>
#include <memory>
#include "MainWindow.h"

MainWindow::MainWindow() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Data Structures Virtulizer",
                                                sf::Style::Titlebar | sf::Style::Close);
    window->setPosition({0, 0});


    visualisationRectangle = std::make_unique<sf::RectangleShape>(sf::RectangleShape(
            {static_cast<float>(window->getSize().x) * 3.f / 4, static_cast<float>(window->getSize().y)}));
    visualisationRectangle->setPosition(window->getSize().x / 4, 0);
    visualisationRectangle->setFillColor({242, 243, 244, 200});
    visualisationRectangle->setOutlineThickness(2);
    visualisationRectangle->setOutlineColor(sf::Color::Black);

    commandsRectangle = std::make_unique<sf::RectangleShape>(
            sf::RectangleShape({static_cast<float>(window->getSize().x) / 4, static_cast<float>(window->getSize().y)}));
    commandsRectangle->setPosition(0, 0);
    commandsRectangle->setFillColor({169, 169, 169, 255});

    vec = new Vector(window.get());
    vec->Parse();
}

void MainWindow::Run() {
    while (window->isOpen()) {
        HandelEvents();
        window->clear();
        DrawVisualizationArea();
        DrawCommandsArea();
        window->display();
    }
}

void MainWindow::HandelEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed)
            switch (event.key.code) {
                case sf::Keyboard::I:
                    vec->ZomIn(sf::Mouse::getPosition());
                    break;
                case sf::Keyboard::O:
                    vec->ZomOut(sf::Mouse::getPosition());
                    break;
                case sf::Keyboard::Right:
                    vec->MoveLeft();
                    break;
                case sf::Keyboard::Left:
                    vec->MoveRight();
                    break;
                case sf::Keyboard::Up:
                    vec->MoveUp();
                    break;
                case sf::Keyboard::Down:
                    vec->MoveDown();
                    break;
            }
    }
}


void MainWindow::DrawVisualizationArea() const {
    window->draw(*visualisationRectangle);

    vec->Draw();
}

void MainWindow::DrawCommandsArea() const {
    window->draw(*commandsRectangle);
}
