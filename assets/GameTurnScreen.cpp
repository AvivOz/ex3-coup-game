#include "GameTurnScreen.hpp"
#include <iostream>

using namespace coup;

GameTurnScreen::GameTurnScreen(std::vector<coup::Player*>& players, coup::Game& game)
    : players(players), game(game), currentTurnIndex(0), quitRequested(false), selectingArrestTarget(false)
{
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    turnText.setFont(font);
    turnText.setCharacterSize(24);
    turnText.setFillColor(sf::Color::White);
    turnText.setPosition(50, 30);

    initButtons();
}

void GameTurnScreen::initButtons() {
    std::vector<std::string> actions = {"Gather", "Tax", "Arrest", "Sanction", "Coup", "Skip Turn"};
    float startX = 50;
    float spacing = 120;
    float y = 500;
    float buttonWidth = 100;
    float buttonHeight = 40;

    actionButtons.clear();
    actionTexts.clear();

    std::cout << "[DEBUG] Initializing buttons..." << std::endl;

    for (size_t i = 0; i < actions.size(); ++i) {
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        button.setFillColor(sf::Color(100, 100, 255));
        float x = startX + i * spacing;
        button.setPosition(x, y);
        
        sf::Text label;
        label.setFont(font);
        label.setString(actions[i]);
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::White);
        
        // מרכוז הטקסט בתוך הכפתור
        sf::FloatRect textBounds = label.getLocalBounds();
        label.setOrigin(textBounds.left + textBounds.width/2.f, 
                       textBounds.top + textBounds.height/2.f);
        label.setPosition(x + buttonWidth/2.f, y + buttonHeight/2.f);
        
        actionButtons.push_back(button);
        actionTexts.push_back(label);

        std::cout << "[DEBUG] Created button '" << actions[i] 
                  << "' at x=" << x << ", y=" << y << std::endl;
    }

    // Initialize quit button
    quitButton.setSize(sf::Vector2f(80, 35));
    quitButton.setFillColor(sf::Color::Red);
    quitButton.setPosition(700, 10);

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(18);
    quitText.setFillColor(sf::Color::White);

    sf::FloatRect quitBounds = quitText.getLocalBounds();
    quitText.setOrigin(quitBounds.left + quitBounds.width/2.f, 
                       quitBounds.top + quitBounds.height/2.f);
    quitText.setPosition(
        quitButton.getPosition().x + quitButton.getSize().x/2.f,
        quitButton.getPosition().y + quitButton.getSize().y/2.f
    );

    std::cout << "[DEBUG] Initialized quit button at x=700, y=10" << std::endl;
}

void GameTurnScreen::handleEvent(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    sf::Event event;
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(
                event.mouseButton.x,
                event.mouseButton.y
            ));
            
            // בדיקת לחיצה על כפתור Quit
            if (quitButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "[DEBUG] Quit button clicked!" << std::endl;
                quitRequested = true;  // שינוי חשוב - לא סוגרים את החלון, רק מסמנים שרוצים לצאת
                return;
            }

            // בדיקת לחיצה על כפתורי פעולה
            for (size_t i = 0; i < actionButtons.size(); ++i) {
                if (actionButtons[i].getGlobalBounds().contains(mousePos)) {
                    std::string action = actionTexts[i].getString().toAnsiString();  // חשוב להשתמש ב-toAnsiString()
                    std::cout << "[DEBUG] Action button clicked: " << action << std::endl;
                    
                    try {
                        if (action == "Gather") {
                            players[currentTurnIndex]->gather();
                            advanceTurn();
                        }
                        else if (action == "Tax") {
                            players[currentTurnIndex]->tax();
                            advanceTurn();
                        }
                        else if (action == "Arrest") {
                            Player* target = players[(currentTurnIndex + 1) % players.size()];
                            players[currentTurnIndex]->arrest(*target);
                            advanceTurn();
                        }
                        else if (action == "Sanction") {
                            Player* target = players[(currentTurnIndex + 1) % players.size()];
                            players[currentTurnIndex]->sanction(*target);
                            advanceTurn();
                        }
                        else if (action == "Coup") {
                            Player* target = players[(currentTurnIndex + 1) % players.size()];
                            players[currentTurnIndex]->coup(*target);
                            advanceTurn();
                        }
                        else if (action == "Skip Turn") {
                            advanceTurn();
                        }
                        std::cout << "[DEBUG] Action completed successfully" << std::endl;
                    }
                    catch (const std::exception& e) {
                        std::cerr << "[ERROR] Action failed: " << e.what() << std::endl;
                    }
                    return;
                }
            }
        }
    }
}

void GameTurnScreen::handleAction(const std::string& action) {
    Player* current = players[currentTurnIndex]; // בחר את השחקן הנוכחי

    try {
        if (action == "Gather") {
            current->gather();
        } else if (action == "Tax") {
            current->tax();
        } else if (action == "Arrest") {
            Player* target = players[(currentTurnIndex + 1) % players.size()]; // בחר את השחקן הבא בתור
            current->arrest(*target);
        } else if (action == "Sanction") {
            Player* target = players[(currentTurnIndex + 1) % players.size()];
            current->sanction(*target);
        } else if (action == "Coup") {
            Player* target = players[(currentTurnIndex + 1) % players.size()];
            current->coup(*target);
        } else if (action == "Skip Turn") {
            // לא עושים כלום
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Action failed: " << e.what() << std::endl;
    }

    advanceTurn();  // לאחר כל פעולה נעבור לתור הבא
}

void GameTurnScreen::draw(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    window.clear(sf::Color(30, 30, 30));

    // Draw turn text
    turnText.setString("Current Turn: " + players[currentTurnIndex]->get_name());
    window.draw(turnText);

    // Draw player info
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

    // Draw action buttons
    for (size_t i = 0; i < actionButtons.size(); ++i) {
        window.draw(actionButtons[i]);
        window.draw(actionTexts[i]);
    }

    // Draw quit button
    window.draw(quitButton);
    window.draw(quitText);

    // Draw arrest target selection if active
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

void GameTurnScreen::advanceTurn() {
    game.next_turn();
    currentTurnIndex = (currentTurnIndex + 1) % players.size();
    while (!players[currentTurnIndex]->alive()) {
        currentTurnIndex = (currentTurnIndex + 1) % players.size();
    }
}