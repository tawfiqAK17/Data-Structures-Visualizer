#include <iostream>
#include <memory>
#include <utility>
#include "MainWindow.hpp"

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
    srand(time(0));

    InitiateFields();
}

void MainWindow::InitiateFields() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Data Structures Visualizer",
                                                sf::Style::Titlebar | sf::Style::Close);
    window->setPosition({0, 0});

    font = std::make_unique<sf::Font>(sf::Font());
    font->loadFromFile("UI/font.ttf");
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

    vec = new ArrayVisualizer(window.get(), font.get());
    vec->Parse();


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

    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), sf::Vector2f(window->getSize().x - 50 - 10, window->getSize().y - 120),
                           {50, 50}, "right", font.get(), [this]() {
                                vec->MoveRight();
                            })));

    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), buttons.back()->GetPosition() - sf::Vector2f(50, 0),
                           {50, 50}, "left", font.get(), [this]() {
                                vec->MoveLeft();
                            })));
    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), buttons.back()->GetPosition() - sf::Vector2f(50, 0),
                           {50, 50}, "down", font.get(), [this]() {
                                vec->MoveDown();
                            })));
    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), buttons.back()->GetPosition() - sf::Vector2f(50, 0),
                           {50, 50}, "up", font.get(), [this]() {
                                vec->MoveUp();
                            })));

    for (int i = 0; i < vec->methodsWithArgs.size(); i++) {
        textHolders.push_back(
                std::make_unique<TextHolder>(
                        TextHolder(window.get(), sf::Vector2f(10 + 10 + controlsArea->getSize().x / 2 - 20, 100 + i * (50 + 8)),
                                   sf::Vector2f(controlsArea->getSize().x / 2 - 20, 50), "0", font.get()
                        )));
        buttons.push_back(
                std::make_unique<Button>(
                        Button(window.get(), sf::Vector2f(10, 100 + i * (50 + 8)),
                               sf::Vector2f(controlsArea->getSize().x / 2 - 20, 50), vec->methodsWithArgs[i], font.get(), [this, i]() {
                                    vec->MethodButtonPressed(i, textHolders[i].get());
                                })));

    }
    for (int i = 0; i < vec->methodsWithOutArgs.size(); i++) {
        buttons.push_back(
                std::make_unique<Button>(
                        Button(window.get(), sf::Vector2f(10, 100 + (i + vec->methodsWithArgs.size()) * (50 + 8)),
                               sf::Vector2f(controlsArea->getSize().x / 2 - 20, 50), vec->methodsWithOutArgs[i], font.get(), [this, i]() {
                                    vec->MethodButtonPressed(i, nullptr);
                                })));

    }


}

void MainWindow::Run() {
    while (window->isOpen()) {
        window->clear();
        HandelEvents();
        DrawComponents();
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
        if (event.type == sf::Event::KeyPressed) {
            HandelTexHolderEvents(event);
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
            }
        }
    }
}

void MainWindow::HandelMouseEvent(sf::Vector2i mouse_position) {
    for (auto &button: buttons) {
        if (button->HandelClickEvent(mouse_position)) {
            return;
        }
    }
    for (auto &textHolder: textHolders) {
        if (textHolder->HandelClickEvent(mouse_position)) {
            inUseTextHolder = textHolder.get();
            for (auto &otherTextHolder: textHolders) {
                if (textHolder->GetPosition() != otherTextHolder->GetPosition()) {
                    otherTextHolder->ChangeState(false);
                    if (otherTextHolder->GetText().isEmpty())
                        otherTextHolder->SetText("0");
                }
            }
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

void MainWindow::HandelTexHolderEvents(sf::Event &event) {
    if (inUseTextHolder) {
        std::string text = inUseTextHolder->GetText().toAnsiString();
        bool hyphen = false;

        if (text[0] == '-') {
            hyphen = true;
            text = text.substr(1);
        }
        if (text.empty()) {
            text = "0";
        }
        if (event.key.code == sf::Keyboard::BackSpace) {
            if (text.size() == 1) {
                text = ("0");
                hyphen = false;
            } else
                text = (text.substr(0, text.size() - 1));
        }
        if (std::stoi(text) < 200'000'000) {
            switch (event.key.code) {
                case sf::Keyboard::Hyphen:
                    if (text == "0") {
                        text = ("-");
                        hyphen = false;
                    }
                    break;
                case sf::Keyboard::Num0:
                    text = (std::to_string(std::stoi(text) * 10 + 0));
                    break;
                case sf::Keyboard::Num1:
                    text = (std::to_string(std::stoi(text) * 10 + 1));
                    break;
                case sf::Keyboard::Num2:
                    text = (std::to_string(std::stoi(text) * 10 + 2));
                    break;
                case sf::Keyboard::Num3:
                    text = (std::to_string(std::stoi(text) * 10 + 3));
                    break;
                case sf::Keyboard::Num4:
                    text = (std::to_string(std::stoi(text) * 10 + 4));
                    break;
                case sf::Keyboard::Num5:
                    text = (std::to_string(std::stoi(text) * 10 + 5));
                    break;
                case sf::Keyboard::Num6:
                    text = (std::to_string(std::stoi(text) * 10 + 6));
                    break;
                case sf::Keyboard::Num7:
                    text = (std::to_string(std::stoi(text) * 10 + 7));
                    break;
                case sf::Keyboard::Num8:
                    text = (std::to_string(std::stoi(text) * 10 + 8));
                    break;
                case sf::Keyboard::Num9:
                    text = (std::to_string(std::stoi(text) * 10 + 9));
                    break;
            }
            if (hyphen)
                inUseTextHolder->SetText("-" + text);
            else
                inUseTextHolder->SetText(text);
        }
    }
}

void MainWindow::DrawComponents() const {
    window->draw(*visualisationArea);
    vec->Draw();
    window->draw(*controlsArea);
    zoomInButton->Draw();
    zoomOutButton->Draw();
    for (auto &button: buttons) {
        button->Draw();
    }
    for (auto &textHolder: textHolders) {
        textHolder->Draw();
    }

}
