#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../include/Player.hpp"
#include "../include/Game.hpp"

class GameTurnScreen {
public:
    GameTurnScreen(std::vector<coup::Player*>& players, coup::Game& game);

    void draw(sf::RenderWindow& window);
    void handleEvent(sf::RenderWindow& window);
    bool didRequestQuit() const;

private:
    std::vector<coup::Player*>& players;
    coup::Game& game;
    int currentTurnIndex;
    bool quitRequested = false;

    sf::Font font;
    sf::Text turnText;

    std::vector<sf::RectangleShape> actionButtons;
    std::vector<sf::Text> actionTexts;

    sf::RectangleShape quitButton;
    sf::Text quitText;

    // arrest target selection UI
    bool selectingArrestTarget = false;
    std::vector<sf::Text> arrestTargetButtons;

    void initButtons();
    void updatePlayerDisplays();
    void advanceTurn();
};