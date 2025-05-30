#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Game.hpp"
#include "../include/Player.hpp"

class GameScreen {
public:
    GameScreen(coup::Game& game, const std::vector<coup::Player*>& players);
    void draw(sf::RenderWindow& window);
    bool handleEvent(sf::RenderWindow& window, sf::Event& event);
    bool shouldQuit() const { return quit; }

private:
    coup::Game& game;
    const std::vector<coup::Player*>& players;
    
    sf::Font font;
    sf::Text currentPlayerText;
    std::vector<sf::Text> playerInfoTexts;
    
    std::vector<sf::RectangleShape> actionButtons;
    std::vector<sf::Text> actionTexts;
    
    sf::RectangleShape quitButton;
    sf::Text quitButtonText;
    
    bool quit;
    int currentPlayerIndex;

    void initializeComponents();
    void updatePlayerInfo();
    void advanceTurn();
};