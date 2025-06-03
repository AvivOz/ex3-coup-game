#pragma once
#include <SFML/Graphics.hpp>

// Forward declarations
class WelcomeScreen;
class PlayerSelectionScreen;
class GameScreen;

enum class Screen {
    Welcome,
    PlayerSelection,
    Game
};

class GUI {
private:
    sf::RenderWindow window;
    Screen currentScreen;
    WelcomeScreen* welcomeScreen;
    PlayerSelectionScreen* playerSelectionScreen;
    GameScreen* gameScreen;

public:
    GUI();
    ~GUI();
    void handleEvents();
    void update();
    void render();
    void switchToGame();
    void run();  
};