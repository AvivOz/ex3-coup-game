#include "../include/GUI/gui.hpp"
#include "../include/playerFactory.hpp"
#include <iostream>

GUI::GUI() : window(sf::VideoMode(800, 600), "Coup Game"), 
             currentScreen(Screen::Welcome),
             gameScreen(nullptr) {
    window.setFramerateLimit(60);
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        switch (currentScreen) {
            case Screen::Welcome:
                if (welcomeScreen.handleEvent(window, event)) {
                    if (welcomeScreen.shouldExit()) {
                        window.close();
                    }
                    else if (welcomeScreen.shouldStartGame()) {
                        currentScreen = Screen::PlayerSelection;
                        playerSelectionScreen.reset();
                    }
                }
                break;

            case Screen::PlayerSelection:
                if (playerSelectionScreen.handleEvent(window, event)) {
                    if (playerSelectionScreen.isSelectionComplete()) {
                        // Create new game
                        game.reset();
                        const auto& names = playerSelectionScreen.getPlayerNames();
                        for (const auto& name : names) {
                            playerFactory(game, name);
                        }
                        
                        if (gameScreen != nullptr) {
                            delete gameScreen;
                        }
                        gameScreen = new GameScreen(game, game.get_players_list());
                        currentScreen = Screen::Game;
                    }
                }
                break;

            case Screen::Game:
                if (gameScreen && gameScreen->handleEvent(window, event)) {
                    if (gameScreen->shouldQuit()) {
                        delete gameScreen;
                        gameScreen = nullptr;
                        currentScreen = Screen::Welcome;
                    }
                }
                break;
        }
    }
}

void GUI::update() {
    // Additional update logic if needed
}

void GUI::draw() {
    window.clear(sf::Color(30, 30, 30));

    switch (currentScreen) {
        case Screen::Welcome:
            welcomeScreen.draw(window);
            break;

        case Screen::PlayerSelection:
            playerSelectionScreen.draw(window);
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
        draw();
    }
}