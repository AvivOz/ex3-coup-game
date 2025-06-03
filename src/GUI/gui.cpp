#include "GUI/gui.hpp"
#include "GUI/WelcomeScreen.hpp"      
#include "GUI/PlayerSelectionScreen.hpp"  
#include "GUI/GameScreen.hpp"         

GUI::GUI() : window(sf::VideoMode(800, 600), "Coup Game"), currentScreen(Screen::Welcome) {
    welcomeScreen = new WelcomeScreen();
    playerSelectionScreen = new PlayerSelectionScreen();
    gameScreen = new GameScreen();
}

GUI::~GUI() {
    delete welcomeScreen;
    delete playerSelectionScreen;
    delete gameScreen;
}

void GUI::switchToGame() {
    if (currentScreen != Screen::Game) {
        currentScreen = Screen::Game;
        const auto& playerNames = playerSelectionScreen->getPlayerNames();
        const auto& roles = playerSelectionScreen->getSelectedRoles();
        gameScreen->initializeGame(playerNames, roles);
    }
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        switch (currentScreen) {
            case Screen::Welcome:
                if (welcomeScreen->handleEvent(event, window)) {
                    if (welcomeScreen->shouldStartGame()) {
                        delete welcomeScreen;
                        welcomeScreen = nullptr;
                        currentScreen = Screen::PlayerSelection;
                        // איפוס מסך בחירת השחקנים לפני המעבר אליו
                        playerSelectionScreen->reset();
                    }
                }
                break;

            case Screen::PlayerSelection:
                if (playerSelectionScreen->handleEvent(event, window)) {
                    if (playerSelectionScreen->shouldStartGame()) {
                        switchToGame();
                    } else if (playerSelectionScreen->shouldGoBack()) {
                        currentScreen = Screen::Welcome;
                        welcomeScreen = new WelcomeScreen();
                        // איפוס מסך בחירת השחקנים כשחוזרים למסך הראשי
                        playerSelectionScreen->reset();
                    }
                }
                break;

            case Screen::Game:
                if (gameScreen->handleEvent(event, window)) {
                    if (gameScreen->shouldGoBack()) {
                        currentScreen = Screen::Welcome;
                        // איפוס מסך בחירת השחקנים כשחוזרים מהמשחק
                        playerSelectionScreen->reset();
                        if (!welcomeScreen) {
                            welcomeScreen = new WelcomeScreen();
                        }
                    }
                }
                break;
        }
    }
}

void GUI::update() {
    // No additional updates needed at this point
}

void GUI::render() {
    window.clear(sf::Color(50, 50, 50));

    switch (currentScreen) {
        case Screen::Welcome:
            if (welcomeScreen) {
                welcomeScreen->draw(window);
            }
            break;

        case Screen::PlayerSelection:
            if (playerSelectionScreen) {
                playerSelectionScreen->draw(window);
            }
            break;

        case Screen::Game:
            if (gameScreen) {
                gameScreen->draw(window);
            }
            break;
    }

    window.display();
}

void GUI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}