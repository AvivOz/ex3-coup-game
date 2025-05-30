#pragma once

#include <SFML/Graphics.hpp>

class WelcomeScreen {
public:
    WelcomeScreen();
    void draw(sf::RenderWindow& window);
    bool handleEvent(sf::RenderWindow& window, sf::Event& event);
    bool shouldStartGame() const { return startGame; }
    bool shouldExit() const { return exit; }

private:
    sf::Font font;
    sf::Text titleText;
    sf::RectangleShape startButton;
    sf::Text startButtonText;
    sf::RectangleShape exitButton;
    sf::Text exitButtonText;
    
    bool startGame;
    bool exit;

    void initializeComponents();
};