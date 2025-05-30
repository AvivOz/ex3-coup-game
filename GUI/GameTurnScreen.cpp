#include "GameTurnScreen.hpp"
#include <iostream>

using namespace coup;

GameTurnScreen::GameTurnScreen(std::vector<Player*>& playersRef, Game& gameRef)
    : players(playersRef), game(gameRef), currentTurnIndex(0), quitRequested(false), selectingArrestTarget(false) {
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    quitButton.setSize(sf::Vector2f(80, 35));
    quitButton.setFillColor(sf::Color::Red);
    quitButton.setPosition(700, 10);

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(18);
    quitText.setFillColor(sf::Color::White);
    sf::FloatRect bounds = quitText.getLocalBounds();
    quitText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    quitText.setPosition(
        quitButton.getPosition().x + quitButton.getSize().x / 2.f,
        quitButton.getPosition().y + quitButton.getSize().y / 2.f
    );

    initButtons();

    turnText.setFont(font);
    turnText.setCharacterSize(24);
    turnText.setFillColor(sf::Color::White);
    turnText.setString("Current turn: " + players[currentTurnIndex]->get_name());
    turnText.setPosition(50, 20);
}

void GameTurnScreen::initButtons() {
    std::vector<std::string> actions = {"Gather", "Tax", "Arrest", "Sanction", "Coup", "Skip Turn"};
    float startX = 50;
    float y = 500;

    for (size_t i = 0; i < actions.size(); ++i) {
        sf::RectangleShape button(sf::Vector2f(100, 40));
        button.setFillColor(sf::Color(100, 100, 255));
        button.setPosition(startX + i * 120, y);
        actionButtons.push_back(button);

        sf::Text label(actions[i], font, 18);
        label.setFillColor(sf::Color::White);
        label.setPosition(button.getPosition().x + 10, button.getPosition().y + 8);
        actionTexts.push_back(label);
    }
}

void GameTurnScreen::draw(sf::RenderWindow& window) {
    window.setView(window.getDefaultView()); 
    window.clear(sf::Color(30, 30, 30));

    window.draw(turnText);

    float startY = 80;
    for (size_t i = 0; i < players.size(); ++i) {
        sf::Text name(players[i]->get_name(), font, 22);
        name.setFillColor(sf::Color::White);
        name.setPosition(50, startY + i * 60);
        window.draw(name);

        sf::Text role(players[i]->get_role(), font, 20);
        role.setFillColor(sf::Color::Yellow);
        role.setPosition(250, startY + i * 60);
        window.draw(role);

        sf::Text coins("Coins: " + std::to_string(players[i]->coins()), font, 20);
        coins.setFillColor(sf::Color::Cyan);
        coins.setPosition(450, startY + i * 60);
        window.draw(coins);
    }

    for (size_t i = 0; i < actionButtons.size(); ++i) {
        window.draw(actionButtons[i]);
        window.draw(actionTexts[i]);
    }

    window.draw(quitButton);
    window.draw(quitText);

    if (selectingArrestTarget) {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(overlay);

        sf::Text title("Choose player to Arrest:", font, 24);
        title.setFillColor(sf::Color::Red);
        title.setPosition(100, 100);
        window.draw(title);

        for (const auto& txt : arrestTargetButtons) {
            window.draw(txt);
        }
    }

    window.display();
}

void GameTurnScreen::handleEvent(sf::RenderWindow& window) {

    window.setView(window.getDefaultView());
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        else if (event.type == sf::Event::MouseButtonPressed &&
                 event.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            std::cout << "[DEBUG] Mouse clicked at: " << mousePos.x << ", " << mousePos.y << std::endl;

            // Quit button
            if (quitButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "[DEBUG] Quit button clicked!\n";
                quitRequested = true;
                return;
            }

            // Arrest target selection (overlay)
            if (selectingArrestTarget) {
                for (size_t i = 0; i < arrestTargetButtons.size(); ++i) {
                    if (arrestTargetButtons[i].getGlobalBounds().contains(mousePos)) {
                        size_t actualIndex = i >= currentTurnIndex ? i + 1 : i;
                        try {
                            players[currentTurnIndex]->arrest(*players[actualIndex]);
                        } catch (const std::exception& e) {
                            std::cerr << "Arrest failed: " << e.what() << std::endl;
                        }
                        selectingArrestTarget = false;
                        advanceTurn();
                        return;
                    }
                }
                return;
            }

            // Action buttons
            for (size_t i = 0; i < actionButtons.size(); ++i) {
                if (actionButtons[i].getGlobalBounds().contains(mousePos)) {
                    std::string action = actionTexts[i].getString();
                    Player* current = players[currentTurnIndex];

                    try {
                        if (action == "Skip Turn") {
                            // no-op
                        }
                        else if (action == "Gather") {
                            current->gather();
                        }
                        else if (action == "Tax") {
                            current->tax();
                        }
                        else if (action == "Arrest") {
                            selectingArrestTarget = true;
                            arrestTargetButtons.clear();

                            for (size_t j = 0; j < players.size(); ++j) {
                                if (j == currentTurnIndex || !players[j]->alive()) continue;
                                sf::Text txt(players[j]->get_name(), font, 20);
                                txt.setFillColor(sf::Color::White);
                                txt.setPosition(100, 150 + arrestTargetButtons.size() * 40);
                                arrestTargetButtons.push_back(txt);
                            }
                            return;
                        }
                        else if (action == "Sanction") {
                            Player* target = players[(currentTurnIndex + 1) % players.size()];
                            current->sanction(*target);
                        }
                        else if (action == "Coup") {
                            Player* target = players[(currentTurnIndex + 1) % players.size()];
                            current->coup(*target);
                        }
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Action failed: " << e.what() << std::endl;
                    }

                    advanceTurn();
                    return;
                }
            }
        }
    }
}

void GameTurnScreen::advanceTurn() {
    game.next_turn();
    currentTurnIndex = (currentTurnIndex + 1) % players.size();
    turnText.setString("Current turn: " + players[currentTurnIndex]->get_name());
}

void GameTurnScreen::updatePlayerDisplays() {
    // לא דרוש כי הנתונים נשלפים ישירות מהשחקנים
}

bool GameTurnScreen::didRequestQuit() const {
    return quitRequested;
}
