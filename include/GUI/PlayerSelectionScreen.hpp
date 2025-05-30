#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PlayerSelectionScreen {
public:
    PlayerSelectionScreen();
    void draw(sf::RenderWindow& window);
    bool handleEvent(sf::RenderWindow& window, sf::Event& event);
    bool isSelectionComplete() const;
    const std::vector<std::string>& getPlayerNames() const;
    void reset();
    bool shouldGoBack() const { return goBack; }

private:
    sf::Font font;
    sf::Text titleText;
    std::vector<sf::RectangleShape> playerCountButtons;
    std::vector<sf::Text> playerCountTexts;
    std::vector<sf::RectangleShape> nameInputBoxes;
    std::vector<sf::Text> nameTexts;
    std::vector<std::string> playerNames;
    
    sf::RectangleShape backButton;
    sf::Text backButtonText;
    sf::RectangleShape startButton;
    sf::Text startButtonText;
    
    int selectedPlayerCount;
    int activeInputBox;
    bool namingPhase;
    bool goBack;
    bool startGame;

    void initializeComponents();
    void createPlayerInputs();
};