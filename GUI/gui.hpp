#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameTurnScreen.hpp"
#include "Game.hpp"

class GUI {
private:
    // ====== Window and Font ======
    sf::RenderWindow window;
    sf::Font font;

    // כפתור Start Game
    sf::RectangleShape startGameButton;
    sf::Text startGameText;

    // ====== Screen State ======
    enum class ScreenState { Welcome, SelectPlayerCount, NameInput, Game };
    ScreenState state;
    bool justSwitchedScreen;

    // ====== Game Logic ======
    coup::Game game; 
    GameTurnScreen* gameTurnScreen;
    bool gameStarted;
    bool readyClicked;

    // ====== Player Info ======
    std::vector<std::string> playerNames;
    int selectedPlayerCount;
    int currentInputIndex;
    int activeNameBoxIndex;

    // ====== UI Components ======

    // Welcome screen
    sf::Text titleText;
    sf::RectangleShape startButton;
    sf::Text startText;
    sf::RectangleShape exitButton;
    sf::Text exitText;

    // Player count screen
    sf::Text playerCountTitle;
    std::vector<sf::RectangleShape> playerCountButtons;
    std::vector<sf::Text> playerCountTexts;

    // Back button (shared)
    sf::RectangleShape backButton;
    sf::Text backText;

    // Name input screen
    sf::Text nameInputTitle;
    std::vector<sf::RectangleShape> nameInputBoxes;
    std::vector<sf::Text> nameInputTexts;
    std::vector<sf::Text> nameLabels;
    std::vector<std::string> nameBuffers;

    // Ready button
    sf::RectangleShape readyButton;
    sf::Text readyText;

    // ====== Internal Methods ======
    void initWelcome();
    void initSelectPlayerCount();
    void initNameInput();
    void initGame();

    void handleEvent();
    void update();
    void draw();

    void startGameIfReady();  

public:
    GUI();
    void run();
};
