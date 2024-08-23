#include <iostream>
#include <memory>
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

bool MainWindow::ZoomButton::InUse() const {
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
    font->loadFromFile("/home/tawfiq/CppProjects/DataStructuresVisualizer/UI/font.ttf");
    visualisationArea = std::make_unique<sf::RectangleShape>(sf::RectangleShape(
            {static_cast<float>(window->getSize().x) * 3.f / 4, static_cast<float>(window->getSize().y)}));
    visualisationArea->setPosition(static_cast<float>(window->getSize().x) / 4, 0);
    visualisationArea->setFillColor({242, 243, 244, 200});
    visualisationArea->setOutlineThickness(2);
    visualisationArea->setOutlineColor(sf::Color::Black);

    controlsArea = std::make_unique<sf::RectangleShape>(
            sf::RectangleShape({static_cast<float>(window->getSize().x) / 4, static_cast<float>(window->getSize().y)}));
    controlsArea->setPosition(0, 0);
    controlsArea->setFillColor({169, 169, 169, 255});

    visualizer = new ArrayVisualizer(window.get(), font.get());
    visualizer->Parse({}, {100, 90});

    availableDataStructures.emplace_back("Array");
    availableDataStructures.emplace_back("Linked list");
    availableDataStructures.emplace_back("Binary search tree");
    availableDataStructures.emplace_back("AVL tree");

    InitiateButtons();

}

void MainWindow::InitiateButtons() {
    selectADataStructure = std::make_unique<Button>(
            Button(window.get(),
                   sf::Vector2f(visualisationArea->getPosition().x + 10, 10),
                   {200, 50}, availableDataStructures[0], font.get(), [this]() {
                        selectingADataStructure = !selectingADataStructure;
                    }));
    for (int i = 0; i < availableDataStructures.size(); i++) {
        dataStructuresButtons.push_back(
                std::make_unique<Button>(
                        Button(window.get(), sf::Vector2f(selectADataStructure->GetPosition().x + 200,
                                                          selectADataStructure->GetPosition().y + 50.f * i),
                               {200, 50}, availableDataStructures[i], font.get(), [this, i]() {
                                    ChangeDataStructure(i);
                                    selectingADataStructure = false;
                                })
                )
        );
    }
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
                    Button(window.get(), sf::Vector2f(static_cast<float>(window->getSize().x) - 50 - 10,
                                                      static_cast<float>(window->getSize().y) - 120),
                           {50, 50}, "right", font.get(), [this]() {
                                visualizer->MoveRight();
                            })));

    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), buttons.back()->GetPosition() - sf::Vector2f(50, 0),
                           {50, 50}, "left", font.get(), [this]() {
                                visualizer->MoveLeft();
                            })));
    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), buttons.back()->GetPosition() - sf::Vector2f(50, 0),
                           {50, 50}, "down", font.get(), [this]() {
                                visualizer->MoveDown();
                            })));
    buttons.push_back(
            std::make_unique<Button>(
                    Button(window.get(), buttons.back()->GetPosition() - sf::Vector2f(50, 0),
                           {50, 50}, "up", font.get(), [this]() {
                                visualizer->MoveUp();
                            })));

    for (int i = 0; i < visualizer->methodsWithArgs.size(); i++) {
        textHolders.push_back(
                std::make_unique<TextHolder>(
                        TextHolder(window.get(), sf::Vector2f(10 + 10 + controlsArea->getSize().x / 2 - 20,
                                                              100.f + static_cast<float>(i) * (50 + 8)),
                                   sf::Vector2f(controlsArea->getSize().x / 2 - 20, 50), "0", font.get()
                        )));
        buttons.push_back(
                std::make_unique<Button>(
                        Button(window.get(), sf::Vector2f(10, 100.f + static_cast<float>(i) * (50 + 8)),
                               sf::Vector2f(controlsArea->getSize().x / 2 - 20, 50), visualizer->methodsWithArgs[i],
                               font.get(), [this, i]() {
                                    auto benchmark_result = visualizer->MethodButtonPressed(i, textHolders[i].get());
                                    if (benchmark_result.second)
                                        methodReturnState->SetText("Returned state: success");
                                    else
                                        methodReturnState->SetText("Returned state: failed");

                                    methodExecutionTime->SetText("Execution time: " + std::to_string(
                                            static_cast<float>(benchmark_result.first) / 1000.f) + " us");
                                })));

    }
    for (int i = 0; i < visualizer->methodsWithOutArgs.size(); i++) {
        buttons.push_back(
                std::make_unique<Button>(
                        Button(window.get(), sf::Vector2f(10, 100.f + static_cast<float>(i +
                                                                                         visualizer->methodsWithArgs.size()) *
                                                                      (50 + 8)),
                               sf::Vector2f(controlsArea->getSize().x / 2 - 20, 50), visualizer->methodsWithOutArgs[i],
                               font.get(), [this, i]() {
                                    auto benchmark_result = visualizer->MethodButtonPressed(i, nullptr);
                                    if (benchmark_result.second)
                                        methodReturnState->SetText("Returned state: success");
                                    else
                                        methodReturnState->SetText("Returned state: failed");
                                    methodExecutionTime->SetText("Execution time: " + std::to_string(
                                            static_cast<float>(benchmark_result.first) / 1000.f) + " us");
                                })));

    }
    methodReturnState = std::make_unique<StaticText>(
            StaticText(window.get(), sf::Vector2f(10, controlsArea->getSize().y - 120 - 50 - 20 - 50 - 20),
                       sf::Vector2f(controlsArea->getSize().x - 20, 50), "Returned state: Non", font.get()));
    methodExecutionTime = std::make_unique<StaticText>(
            StaticText(window.get(), sf::Vector2f(10, controlsArea->getSize().y - 120 - 50 - 20),
                       sf::Vector2f(controlsArea->getSize().x - 20, 50), "Execution time: 0 us", font.get()));
    sizeInBytes = std::make_unique<StaticText>(
            StaticText(window.get(), sf::Vector2f(10, controlsArea->getSize().y - 120),
                       sf::Vector2f(controlsArea->getSize().x - 20, 50), "Used memory: 0 Bytes", font.get()));
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
        if (event.type == sf::Event::MouseWheelMoved) {
            if (event.mouseWheel.delta > 0)
                visualizer->ZoomIn(sf::Mouse::getPosition(*window));
            else
                visualizer->ZoomOut(sf::Mouse::getPosition(*window));
        }
        if (event.type == sf::Event::KeyPressed) {
            HandelTexHolderEvents(event);
            switch (event.key.code) {
                case sf::Keyboard::Left:
                    visualizer->MoveLeft();
                    break;
                case sf::Keyboard::Right:
                    visualizer->MoveRight();
                    break;
                case sf::Keyboard::Up:
                    visualizer->MoveUp();
                    break;
                case sf::Keyboard::Down:
                    visualizer->MoveDown();
                    break;
            }
        }
    }
}

void MainWindow::HandelMouseEvent(sf::Vector2i mouse_position) {
    selectingADataStructure = false;
    for (auto &button: buttons) {
        if (button->HandelClickEvent(mouse_position)) {
            sizeInBytes->SetText("Used memory: " + std::to_string(visualizer->GetSizeInBytes()) + " Bytes");
            return;
        }
    }
    for (auto &textHolder: textHolders) {
        if (textHolder->HandelClickEvent(mouse_position)) {
            inUseTextHolder = textHolder.get();
            for (auto &otherTextHolder: textHolders) {
                if (textHolder->GetPosition() != otherTextHolder->GetPosition()) {
                    otherTextHolder->ChangeState(false);
                }
            }
            return;
        }
    }

    for (auto &button: dataStructuresButtons)
        if (button->HandelClickEvent(mouse_position))
            return;
    if (selectADataStructure->HandelClickEvent(mouse_position))
        return;
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

    if (100.f + static_cast<float>(mouse_position.x) > visualisationArea->getPosition().x) {
        if (zoomInButton->InUse())
            visualizer->ZoomIn(mouse_position);
        if (zoomOutButton->InUse())
            visualizer->ZoomOut(mouse_position);
    }
}

void MainWindow::ChangeDataStructure(int idx) {
    delete visualizer;
    visualizer = nullptr;
    switch (idx) {
        case 0:
            visualizer = new ArrayVisualizer(window.get(), font.get());
            break;
        case 1:
            visualizer = new LinkedListVisualizer(window.get(), font.get());
            break;
        case 2:
            visualizer = new BinarySearchTreeVisualizer(window.get(), font.get());
            break;
        case 3:
            visualizer = new AvlTreeVisualizer(window.get(), font.get());
            break;
    }
    visualizer->Parse({}, {100, 90});
    buttons.clear();
    textHolders.clear();
    InitiateButtons();
    selectADataStructure->SetText(availableDataStructures[idx]);
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
    visualizer->Draw();
    window->draw(*controlsArea);
    selectADataStructure->Draw();
    zoomInButton->Draw();
    zoomOutButton->Draw();
    methodReturnState->Draw();
    methodExecutionTime->Draw();
    sizeInBytes->Draw();
    for (auto &button: buttons) {
        button->Draw();
    }
    for (auto &textHolder: textHolders) {
        textHolder->Draw();
    }
    if (selectingADataStructure)
        for (auto &button: dataStructuresButtons) {
            button->Draw();
        }

}
