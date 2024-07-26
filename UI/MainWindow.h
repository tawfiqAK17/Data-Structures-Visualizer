#pragma once
#include "SFML/Graphics.hpp"

#include "../DataStructures/Vector.h"
#include "Button.h"
#include "TextHolder.h"

class MainWindow {
private:
    class ZoomButton : public Button{
    public:
        ZoomButton(sf::RenderWindow* _window, sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font *font);
        bool HandelClickEvent(sf::Vector2i mouse_position) override;
        void ChangeTheState();
        bool InUse();
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
    void HandelMouseEvent(sf::Vector2i mouse_position);
    void HandelTexHolderEvents(sf::Event &event);
    void DrawComponents() const;

private:
    std::unique_ptr<sf::Font> font;
    std::unique_ptr<sf::RenderWindow> window;

    Visualizer *vec;

    std::unique_ptr<sf::RectangleShape> visualisationArea;
    std::unique_ptr<sf::RectangleShape> controlsArea;

    std::unique_ptr<ZoomButton> zoomInButton;
    std::unique_ptr<ZoomButton> zoomOutButton;
    std::vector<std::unique_ptr<Button>> buttons;
    std::vector<std::unique_ptr<TextHolder>> textHolders;

    TextHolder *inUseTextHolder = nullptr;

};
