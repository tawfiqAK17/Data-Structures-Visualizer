#pragma once
#include "SFML/Graphics.hpp"

#include "Visualizers/ArrayVisualizer.hpp"
#include "Visualizers/LinkedListVisualizer.h"
#include "Visualizers/BinarySearchTreeVisualizer.h"
#include "Visualizers/AvlTreeVisualizer.h"
#include "UIElements/Button.hpp"
#include "UIElements/TextHolder.hpp"
#include "UIElements/StaticText.hpp"

class MainWindow {
private:
    class ZoomButton : public Button{
    public:
        ZoomButton(sf::RenderWindow* _window, sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font *font);
        bool HandelClickEvent(sf::Vector2i mouse_position) override;
        void ChangeTheState();
        bool InUse() const;
    private:
        bool inUse = false;
    };
public:

    MainWindow();
    void Run();
private:
    void InitiateFields();
    void InitiateButtons();
    void HandelEvents();
    void ChangeDataStructure(int idx);
    void HandelMouseEvent(sf::Vector2i mouse_position);
    void HandelTexHolderEvents(sf::Event &event);
    void DrawComponents() const;

private:
    std::unique_ptr<sf::Font> font;
    std::unique_ptr<sf::RenderWindow> window;

    Visualizer *visualizer;
    std::vector<std::string> availableDataStructures;
    std::unique_ptr<Button> selectADataStructure;
    std::vector<std::unique_ptr<Button>> dataStructuresButtons;
    bool selectingADataStructure = false;

    std::unique_ptr<sf::RectangleShape> visualisationArea;
    std::unique_ptr<sf::RectangleShape> controlsArea;

    std::unique_ptr<ZoomButton> zoomInButton;
    std::unique_ptr<ZoomButton> zoomOutButton;
    std::vector<std::unique_ptr<Button>> buttons;
    std::vector<std::unique_ptr<TextHolder>> textHolders;

    std::unique_ptr<StaticText> methodReturnState;
    std::unique_ptr<StaticText> methodExecutionTime;
    std::unique_ptr<StaticText> sizeInBytes;

    TextHolder *inUseTextHolder = nullptr;

};
