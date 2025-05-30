#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameTurnScreen.hpp"
#include "../include/Game.hpp"

class GUI {
public:
    GUI();
    void run();

private:
    enum class ScreenState {
        Welcome,
        SelectPlayerCount,
        NameInput,
        Game
    };

    sf::RenderWindow window;
    ScreenState state;
    bool justSwitchedScreen;
    int selectedPlayerCount;
    int currentInputIndex;
    int activeNameBoxIndex;
    GameTurnScreen* gameTurnScreen;
    bool readyClicked;
    bool gameStarted;

    coup::Game game;
    std::vector<std::string> playerNames;
    sf::Font font;

    // Welcome screen elements
    sf::Text titleText;
    sf::RectangleShape startButton;
    sf::Text startText;
    sf::RectangleShape exitButton;
    sf::Text exitText;

    // Player count selection elements
    sf::Text playerCountTitle;
    std::vector<sf::RectangleShape> playerCountButtons;
    std::vector<sf::Text> playerCountTexts;
    sf::RectangleShape backButton;
    sf::Text backText;

    // Name input elements
    sf::Text nameInputTitle;
    std::vector<sf::RectangleShape> nameInputBoxes;
    std::vector<sf::Text> nameInputTexts;
    std::vector<std::string> nameBuffers;
    std::vector<sf::Text> nameLabels;
    sf::RectangleShape startGameButton;
    sf::Text startGameText;

    void initWelcome();
    void initSelectPlayerCount();
    void initNameInput();
    void initGame();
    void handleEvent();
    void update();
    void draw();
    void startGameIfReady();
};