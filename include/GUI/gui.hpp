#pragma once

#include <SFML/Graphics.hpp>
#include "WelcomeScreen.hpp"
#include "PlayerSelectionScreen.hpp"
#include "GameScreen.hpp"
#include "../include/Game.hpp"

class GUI {
public:
    GUI();
    void run();

private:
    enum class Screen {
        Welcome,
        PlayerSelection,
        Game
    };

    sf::RenderWindow window;
    Screen currentScreen;
    
    WelcomeScreen welcomeScreen;
    PlayerSelectionScreen playerSelectionScreen;
    GameScreen* gameScreen;
    
    coup::Game game;

    void handleEvents();
    void update();
    void draw();
};