#include "../include/GUI/WelcomeScreen.hpp"
#include <iostream>

WelcomeScreen::WelcomeScreen() : startGame(false), exit(false) {
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    initializeComponents();
}

void WelcomeScreen::initializeComponents() {
    // Title
    titleText.setFont(font);
    titleText.setString("Coup Game");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(300, 100);

    // Start Button
    startButton.setSize(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300, 250);

    startButtonText.setFont(font);
    startButtonText.setString("Start Game");
    startButtonText.setCharacterSize(24);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(330, 260);

    // Exit Button
    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(300, 350);

    exitButtonText.setFont(font);
    exitButtonText.setString("Exit");
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setPosition(370, 360);
}

void WelcomeScreen::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(startButton);
    window.draw(startButtonText);
    window.draw(exitButton);
    window.draw(exitButtonText);
}

bool WelcomeScreen::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Check start button
            if (startButton.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                startGame = true;
                return true;
            }

            // Check exit button
            if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                exit = true;
                window.close();
                return true;
            }
        }
    }
    return false;
}