#include <iostream>
#include <memory>
#include <utility>
#include "MainWindow.h"

#define IN_USE_BUTTON_COLOR {64, 64, 64, 250}
#define NON_IN_USE_BUTTON_COLOR { 176, 176, 176, 250}
MainWindow::ZoomButton::ZoomButton(sf::RenderWindow *_window, sf::Vector2f position, sf::Vector2f size, sf::String text,
                                   sf::Font *font) : Button(_window, position, size, text, font, nullptr) {

}

bool MainWindow::ZoomButton::HandelClickEvent(sf::Vector2i mouse_position) {
    if ((float) mouse_position.x > GetPosition().x && (float) mouse_position.x < GetPosition().x + GetSize().x
        && (float) mouse_position.y > GetPosition().y && (float) mouse_position.y < GetPosition().y + GetSize().y
            ) {
        ChangeTheState();
        return true;
    }
    return false;
}

void MainWindow::ZoomButton::ChangeTheState() {
    if (inUse) {
        inUse = false;
        buttonRect->setFillColor(NON_IN_USE_BUTTON_COLOR);
        return;
    }
    inUse = true;
    buttonRect->setFillColor(IN_USE_BUTTON_COLOR);
}

bool MainWindow::ZoomButton::InUse() {
    return inUse;
}


MainWindow::MainWindow() {
    InitiateFields();
}

void MainWindow::InitiateFields() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Data Structures Visualizer",
                                                sf::Style::Titlebar | sf::Style::Close);
    window->setPosition({0, 0});

    font = std::make_unique<sf::Font>(sf::Font());
    font->loadFromFile("font.ttf");
    visualisationArea = std::make_unique<sf::RectangleShape>(sf::RectangleShape(
            {static_cast<float>(window->getSize().x) * 3.f / 4, static_cast<float>(window->getSize().y)}));
    visualisationArea->setPosition(window->getSize().x / 4, 0);
    visualisationArea->setFillColor({242, 243, 244, 200});
    visualisationArea->setOutlineThickness(2);
    visualisationArea->setOutlineColor(sf::Color::Black);

    controlsArea = std::make_unique<sf::RectangleShape>(
            sf::RectangleShape({static_cast<float>(window->getSize().x) / 4, static_cast<float>(window->getSize().y)}));
    controlsArea->setPosition(0, 0);
    controlsArea->setFillColor({169, 169, 169, 255});

    InitiateButtons();
}

void MainWindow::InitiateButtons() {
    zoomInButton = std::make_unique<ZoomButton>(
            ZoomButton(window.get(),
                       sf::Vector2f(visualisationArea->getPosition().x + 10, visualisationArea->getSize().y - 120),
                       {100, 50}, "Zoom in", font.get()));

    zoomOutButton = std::make_unique<ZoomButton>(
            ZoomButton(window.get(), zoomInButton->GetPosition() + sf::Vector2f(zoomInButton->GetSize().x, 0),
                       {100, 50}, "Zoom out",
                       font.get()));

    vec = new Vector(window.get(), font.get());
    vec->Parse();
    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), sf::Vector2f(window->getSize().x - 3 * 50 - 10, window->getSize().y - 120),
                           {50, 50}, "left", font.get(), [this]() {
                                vec->MoveLeft();
                            })));
    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), sf::Vector2f(window->getSize().x - 2 * 50 - 10, window->getSize().y - 120),
                           {50, 50}, "down", font.get(), [this]() {
                                vec->MoveDown();
                            })));
    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), sf::Vector2f(window->getSize().x - 1 * 50 - 10, window->getSize().y - 120),
                           {50, 50}, "right", font.get(), [this]() {
                                vec->MoveRight();
                            })));
    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), sf::Vector2f(window->getSize().x - 2 * 50 - 11, window->getSize().y - (120 + 50)),
                           {50, 50}, "up", font.get(), [this]() {
                                vec->MoveUp();
                            })));
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
        if (event.type == sf::Event::MouseButtonPressed) {
            HandelMouseEvent(sf::Mouse::getPosition(*window));
        }
        if (event.type == sf::Event::KeyPressed)
            switch (event.key.code) {
                case sf::Keyboard::Left:
                    vec->MoveLeft();
                    break;
                case sf::Keyboard::Right:
                    vec->MoveRight();
                    break;
                case sf::Keyboard::Up:
                    vec->MoveUp();
                    break;
                case sf::Keyboard::Down:
                    vec->MoveDown();
                    break;
                case sf::Keyboard::O:
                    vec->ZoomIn(sf::Mouse::getPosition(*window));
                    break;
                case sf::Keyboard::I:
                    vec->ZoomOut(sf::Mouse::getPosition(*window));
                    break;
            }
    }
}
void MainWindow::HandelMouseEvent(sf::Vector2i mouse_position) {
    for (auto &button: buttons) {
        if (button->HandelClickEvent(mouse_position)) {
            return;
        }
    }
    if (zoomInButton->HandelClickEvent(mouse_position)) {
        if (zoomOutButton->InUse())
            zoomOutButton->ChangeTheState();
        return;
    }
    if (zoomOutButton->HandelClickEvent(mouse_position)) {
        if (zoomInButton->InUse()) {
            zoomInButton->ChangeTheState();
        }
        return;
    }

    if (mouse_position.x > visualisationArea->getPosition().x) {
        if (zoomInButton->InUse())
            vec->ZoomIn(mouse_position);
        if (zoomOutButton->InUse())
            vec->ZoomOut(mouse_position);
    }
}

void MainWindow::DrawVisualizationArea() const {
    window->draw(*visualisationArea);
    vec->Draw();
    zoomInButton->Draw();
    zoomOutButton->Draw();
    for (auto &button: buttons) {
        button->Draw();
    }

}

void MainWindow::DrawCommandsArea() const {
    window->draw(*controlsArea);
}
