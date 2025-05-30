#include "../include/GUI/GameScreen.hpp"
#include <iostream>

GameScreen::GameScreen(coup::Game& game, const std::vector<coup::Player*>& players)
    : game(game), players(players), quit(false), currentPlayerIndex(0) {
    
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    initializeComponents();
}

void GameScreen::initializeComponents() {
    // Current Player Text
    currentPlayerText.setFont(font);
    currentPlayerText.setCharacterSize(30);
    currentPlayerText.setFillColor(sf::Color::White);
    currentPlayerText.setPosition(50, 30);

    // Player Info Texts
    for (size_t i = 0; i < players.size(); ++i) {
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setCharacterSize(20);
        playerText.setFillColor(sf::Color::White);
        playerText.setPosition(50, 100 + i * 40);
        playerInfoTexts.push_back(playerText);
    }

    // Action Buttons
    std::vector<std::string> actions = {"Gather", "Tax", "Arrest", "Sanction", "Coup", "Skip Turn"};
    float startX = 50;
    float y = 500;
    float spacing = 120;

    for (size_t i = 0; i < actions.size(); ++i) {
        sf::RectangleShape button(sf::Vector2f(100, 40));
        button.setFillColor(sf::Color::Blue);
        button.setPosition(startX + i * spacing, y);
        actionButtons.push_back(button);

        sf::Text text;
        text.setFont(font);
        text.setString(actions[i]);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);
        // מרכוז הטקסט בכפתור
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width/2, textBounds.height/2);
        text.setPosition(startX + i * spacing + 50, y + 20);
        actionTexts.push_back(text);
    }

    // Quit Button
    quitButton.setSize(sf::Vector2f(80, 40));
    quitButton.setFillColor(sf::Color::Red);
    quitButton.setPosition(700, 30);

    quitButtonText.setFont(font);
    quitButtonText.setString("Quit");
    quitButtonText.setCharacterSize(20);
    quitButtonText.setFillColor(sf::Color::White);
    sf::FloatRect quitBounds = quitButtonText.getLocalBounds();
    quitButtonText.setOrigin(quitBounds.width/2, quitBounds.height/2);
    quitButtonText.setPosition(740, 50);

    updatePlayerInfo();
}

void GameScreen::updatePlayerInfo() {
    currentPlayerText.setString("Current Turn: " + players[currentPlayerIndex]->get_name());

    for (size_t i = 0; i < players.size(); ++i) {
        std::string info = players[i]->get_name() + " (" + 
                          players[i]->get_role() + ") - Coins: " + 
                          std::to_string(players[i]->coins());
        if (!players[i]->alive()) {
            info += " (Dead)";
        }
        playerInfoTexts[i].setString(info);
    }
}

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(currentPlayerText);
    
    // Draw player info
    for (const auto& text : playerInfoTexts) {
        window.draw(text);
    }

    // Draw action buttons
    for (size_t i = 0; i < actionButtons.size(); ++i) {
        window.draw(actionButtons[i]);
        window.draw(actionTexts[i]);
    }

    // Draw quit button
    window.draw(quitButton);
    window.draw(quitButtonText);
}

bool GameScreen::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && 
        event.mouseButton.button == sf::Mouse::Left) {
        
        sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
        );

        // Check quit button
        if (quitButton.getGlobalBounds().contains(mousePos)) {
            quit = true;
            return true;
        }

        // Check action buttons
        for (size_t i = 0; i < actionButtons.size(); ++i) {
            if (actionButtons[i].getGlobalBounds().contains(mousePos)) {
                try {
                    std::string action = actionTexts[i].getString();
                    coup::Player* currentPlayer = players[currentPlayerIndex];
                    coup::Player* nextPlayer = players[(currentPlayerIndex + 1) % players.size()];

                    if (action == "Gather") {
                        currentPlayer->gather();
                        advanceTurn();
                    }
                    else if (action == "Tax") {
                        currentPlayer->tax();
                        advanceTurn();
                    }
                    else if (action == "Arrest") {
                        currentPlayer->arrest(*nextPlayer);
                        advanceTurn();
                    }
                    else if (action == "Sanction") {
                        currentPlayer->sanction(*nextPlayer);
                        advanceTurn();
                    }
                    else if (action == "Coup") {
                        currentPlayer->coup(*nextPlayer);
                        advanceTurn();
                    }
                    else if (action == "Skip Turn") {
                        advanceTurn();
                    }
                    
                    updatePlayerInfo();
                    return true;
                }
                catch (const std::exception& e) {
                    std::cerr << "Action failed: " << e.what() << std::endl;
                }
            }
        }
    }
    return false;
}

void GameScreen::advanceTurn() {
    game.next_turn();
    do {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    } while (!players[currentPlayerIndex]->alive());
}