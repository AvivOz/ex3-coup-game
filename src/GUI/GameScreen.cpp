#include "GUI/GameScreen.hpp"
#include <iostream>

using namespace coup;

GameScreen::GameScreen() : window(nullptr), shouldQuit(false) {
    if (!font.loadFromFile("assets/DejaVuSans.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    initializeComponents();
    initializePopupDialog();
}

GameScreen::~GameScreen() {
    for (auto player : players) {
        delete player;
    }
    players.clear();
}

void GameScreen::initializeComponents() {
    // אתחול טקסט סטטוס
    statusText.setFont(font);
    statusText.setCharacterSize(30);
    statusText.setFillColor(sf::Color::White);
    centerText(statusText, 50);

    // הגדרת מידות אחידות לכפתורים
    float actionButtonWidth = 150;
    float actionButtonHeight = 45;
    
    // אתחול כפתור QUIT - מיקום קבוע בצד שמאל למטה
    quitButton.setSize(sf::Vector2f(actionButtonWidth, actionButtonHeight));
    quitButton.setPosition(50, 500);  // מיקום קבוע
    quitButton.setFillColor(sf::Color(150, 50, 50));
    
    quitButtonText.setFont(font);
    quitButtonText.setString("QUIT");
    quitButtonText.setCharacterSize(24);
    quitButtonText.setFillColor(sf::Color::White);
    
    // מרכוז מדויק של הטקסט בתוך כפתור QUIT
    sf::FloatRect quitTextRect = quitButtonText.getLocalBounds();
    quitButtonText.setOrigin(
        quitTextRect.left + quitTextRect.width/2.0f,
        quitTextRect.top + quitTextRect.height/2.0f
    );
    quitButtonText.setPosition(
        quitButton.getPosition().x + quitButton.getSize().x/2.0f,
        quitButton.getPosition().y + quitButton.getSize().y/2.0f
    );

    // אתחול כפתור Skip Turn - מיקום קבוע בצד ימין למטה
    skipTurnButton.setSize(sf::Vector2f(actionButtonWidth, actionButtonHeight));
    skipTurnButton.setPosition(600, 500);  // מיקום קבוע
    skipTurnButton.setFillColor(sf::Color(100, 100, 100));
    
    skipTurnButtonText.setFont(font);
    skipTurnButtonText.setString("Skip Turn");
    skipTurnButtonText.setCharacterSize(24);
    skipTurnButtonText.setFillColor(sf::Color::White);
    
    // מרכוז מדויק של הטקסט בתוך כפתור Skip Turn
    sf::FloatRect skipTextRect = skipTurnButtonText.getLocalBounds();
    skipTurnButtonText.setOrigin(
        skipTextRect.left + skipTextRect.width/2.0f,
        skipTextRect.top + skipTextRect.height/2.0f
    );
    skipTurnButtonText.setPosition(
        skipTurnButton.getPosition().x + skipTurnButton.getSize().x/2.0f,
        skipTurnButton.getPosition().y + skipTurnButton.getSize().y/2.0f
    );

    // אתחול כפתורי הפעולה
    initializeActionButtons();
}

void GameScreen::initializeActionButtons() {
    float buttonWidth = 100;     // הקטנת רוחב הכפתור
    float buttonHeight = 40;     // גובה נשאר אותו דבר
    float totalWidth = 800;      // רוחב החלון
    float startY = 400;          // מיקום אנכי
    float spacing = 30;          // הגדלת הרווח בין הכפתורים
    
    // חישוב הרוחב הכולל שהכפתורים יתפסו
    float totalButtonsWidth = (buttonWidth * actions.size()) + (spacing * (actions.size() - 1));
    // חישוב נקודת ההתחלה
    float startX = (totalWidth - totalButtonsWidth) / 2;
    
    actionButtons.clear();
    actionTexts.clear();
    
    for (size_t i = 0; i < actions.size(); ++i) {
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        button.setPosition(startX + (i * (buttonWidth + spacing)), startY);
        button.setFillColor(sf::Color(100, 100, 100));
        actionButtons.push_back(button);

        sf::Text text;
        text.setFont(font);
        text.setString(actions[i]);
        text.setCharacterSize(18);  // הקטנת גודל הטקסט מעט
        text.setFillColor(sf::Color::White);
        
        // מרכוז הטקסט בתוך הכפתור
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            button.getPosition().x + (buttonWidth - textBounds.width) / 2,
            button.getPosition().y + (buttonHeight - textBounds.height) / 2
        );
        
        actionTexts.push_back(text);
    }
}

void GameScreen::createPlayerBoxes() {
    playerBoxes.clear();
    playerTexts.clear();
    playerCoinsTexts.clear();

    float boxWidth = 180;
    float boxHeight = 100;
    float spacing = 30;
    
    // חישוב מספר השורות והעמודות הנדרשות
    int numPlayers = players.size();
    int numRows, numCols;
    
    if (numPlayers <= 3) {
        numRows = 1;
        numCols = numPlayers;
    } else if (numPlayers <= 6) {
        numRows = 2;
        numCols = (numPlayers + 1) / 2;  // עיגול כלפי מעלה
    } else {
        numRows = 2;
        numCols = 3;
    }

    // חישוב נקודת ההתחלה כדי למרכז את כל הקבוצה
    float totalWidth = numCols * boxWidth + (numCols - 1) * spacing;
    float startX = (800 - totalWidth) / 2;  // 800 הוא רוחב החלון
    float startY = 150;  // התחלה מ-y=150
    
    for (size_t i = 0; i < players.size(); ++i) {
        int row = i / numCols;
        int col = i % numCols;
        
        // אם זו השורה האחרונה ויש מספר אי-זוגי של שחקנים, מרכז את התיבה האחרונה
        if (row == numRows - 1 && col == 0 && (i + numCols > players.size())) {
            col = (numCols - (players.size() % numCols)) / 2;
        }
        
        sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
        box.setPosition(
            startX + col * (boxWidth + spacing),
            startY + row * (boxHeight + spacing)
        );
        box.setFillColor(sf::Color(70, 70, 70));
        playerBoxes.push_back(box);

        // הגדרת טקסט השחקן
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setCharacterSize(22);
        playerText.setFillColor(sf::Color::White);
        playerText.setPosition(
            box.getPosition().x + 10,
            box.getPosition().y + 10
        );
        playerTexts.push_back(playerText);

        // הגדרת טקסט המטבעות
        sf::Text coinsText;
        coinsText.setFont(font);
        coinsText.setCharacterSize(20);
        coinsText.setFillColor(sf::Color::Yellow);
        coinsText.setPosition(
            box.getPosition().x + 10,
            box.getPosition().y + boxHeight - 30
        );
        playerCoinsTexts.push_back(coinsText);
    }
}

void GameScreen::initializeGame(const std::vector<std::string>& playerNames, 
                              const std::vector<std::string>& roles) {
    try {
        std::cout << "Starting game initialization..." << std::endl;
        
        // איפוס המצב הקודם
        std::cout << "Resetting previous game state..." << std::endl;
        resetGame();
        
        // בדיקות תקינות
        std::cout << "Validating player count: " << playerNames.size() << std::endl;
        if (playerNames.size() < 2 || playerNames.size() > 6) {
            throw std::runtime_error("Invalid number of players (must be 2-6)");
        }
        
        if (playerNames.size() != roles.size()) {
            throw std::runtime_error("Number of players doesn't match number of roles");
        }
        
        // יצירת משחק חדש
        std::cout << "Creating new game instance..." << std::endl;
        game = std::make_unique<coup::Game>();
        
        // יצירת השחקנים
        std::cout << "Creating players..." << std::endl;
        for (size_t i = 0; i < playerNames.size(); ++i) {
            std::cout << "Creating player " << i + 1 << ": " << playerNames[i] << " as " << roles[i] << std::endl;
            
            coup::Player* player = nullptr;
            
            try {
                if (roles[i] == "Governor") {
                    player = new coup::Governor(*game, playerNames[i]);
                } else if (roles[i] == "Judge") {
                    player = new coup::Judge(*game, playerNames[i]);
                } else if (roles[i] == "General") {
                    player = new coup::General(*game, playerNames[i]);
                } else if (roles[i] == "Baron") {
                    player = new coup::Baron(*game, playerNames[i]);
                } else if (roles[i] == "Merchant") {
                    player = new coup::Merchant(*game, playerNames[i]);
                } else if (roles[i] == "Spy") {
                    player = new coup::Spy(*game, playerNames[i]);
                } else {
                    throw std::runtime_error("Invalid role: " + roles[i]);
                }
                
                if (player == nullptr) {
                    throw std::runtime_error("Failed to create player");
                }
                
                players.push_back(player);
                std::cout << "Player " << playerNames[i] << " created successfully" << std::endl;
                
            } catch (const std::exception& e) {
                std::cerr << "Error creating player: " << e.what() << std::endl;
                // ניקוי השחקנים שכבר נוצרו
                for (auto* p : players) {
                    delete p;
                }
                players.clear();
                game = nullptr;
                throw;
            }
        }

        if (players.empty()) {
            throw std::runtime_error("No players were created");
        }

        // התחלת המשחק
        std::cout << "Initializing game state..." << std::endl;
        isInitialized = true;
        game->next_turn();
        
        // אתחול הממשק הגרפי
        std::cout << "Setting up GUI components..." << std::endl;
        createPlayerBoxes();
        initializeActionButtons();
        createSpecialActionButtons();
        updatePlayerInfo();
        
        std::cout << "Game initialization completed successfully" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error in initializeGame: " << e.what() << std::endl;
        resetGame();
        throw;
    }
}

void GameScreen::updatePlayerInfo() {
    try {
        if (!game) {
            std::cout << "Game is null in updatePlayerInfo" << std::endl;
            return;
        }
        
        updateStatusText();
        std::string currentPlayerName = game->turn();
        std::cout << "Updating display for current player: " << currentPlayerName << std::endl;
        
        // שמירה על הודעת השגיאה הנוכחית אם קיימת
        std::string currentStatus = statusText.getString();
        bool isError = currentStatus.substr(0, 6) == "Error:";
        
        // עדכון הודעת הסטטוס רק אם אין הודעת שגיאה
        if (!isError) {
            statusText.setFillColor(sf::Color::White);
            statusText.setString("Current Turn: " + currentPlayerName);
            centerText(statusText, 50, false);
        }

        int alive_count = 0;
        for (size_t i = 0; i < players.size(); ++i) {
            if (!players[i]) {
                std::cout << "Warning: Null player at index " << i << std::endl;
                continue;
            }
            
            if (players[i]->alive()) {
                alive_count++;
                std::string playerInfo = players[i]->get_name() + "\n" + players[i]->get_role();
                playerTexts[i].setString(playerInfo);
                std::string coinsInfo = "Coins: " + std::to_string(players[i]->coins());
                playerCoinsTexts[i].setString(coinsInfo);
                playerCoinsTexts[i].setPosition(
                    playerBoxes[i].getPosition().x + 10,
                    playerBoxes[i].getPosition().y + playerBoxes[i].getSize().y - 30
                );

                if (players[i]->get_name() == currentPlayerName) {
                    playerBoxes[i].setFillColor(sf::Color(100, 100, 70));
                } else {
                    playerBoxes[i].setFillColor(sf::Color(70, 70, 70));
                }
            } else {
                playerBoxes[i].setFillColor(sf::Color(50, 50, 50));
                std::string playerInfo = players[i]->get_name() + "\n" + players[i]->get_role() + "\n(Eliminated)";
                playerTexts[i].setString(playerInfo);
                playerCoinsTexts[i].setString("");
            }
        }

        if (alive_count <= 1) {
            std::cout << "Only one player remaining, checking game end" << std::endl;
            checkGameEnd();
        }
        
        // אם הייתה הודעת שגיאה, נשמור אותה באדום
        if (isError) {
            statusText.setString(currentStatus);
            centerText(statusText, 50, true);
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error in updatePlayerInfo: " << e.what() << std::endl;
        statusText.setString(e.what());
        centerText(statusText, 50, true);
    }
}

bool GameScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    try {
        if (game_over || !validateGameState()) {
            std::cout << "Game over or invalid state" << std::endl;
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        resetGameState();
                        shouldQuit = true;
                        return true;
                    }
                }
            }
            return false;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            // טיפול בחלון הדיאלוג אם הוא פעיל
            if (coupDialog.isActive) {
                handlePopupClick(mousePos);
                return true;
            }

            // טיפול בכפתור QUIT
            if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Quit button clicked" << std::endl;
                resetGame();
                shouldQuit = true;
                return true;
            }

            // טיפול בכפתור Skip Turn
            if (skipTurnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Skip Turn button clicked" << std::endl;
                try {
                    coup::Player* currentPlayer = game->getCurrentPlayer();
                    if (currentPlayer && currentPlayer->coins() >= 10) {
                        statusText.setString(MUST_COUP_ERROR);
                        centerText(statusText, 50, true);
                        return true;
                    }
                    
                    nextTurn();
                    updateSpecialButtons();
                } catch (const std::exception& e) {
                    std::cerr << "Error in Skip Turn: " << e.what() << std::endl;
                    statusText.setString(e.what());
                    centerText(statusText, 50);
                }
                return true;
            }

            // טיפול בכפתורים מיוחדים
            for (size_t i = 0; i < specialActionButtons.size(); ++i) {
                if (specialActionButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Special action button " << i << " clicked" << std::endl;
                    handleSpecialAction(i);
                    return true;
                }
            }

            // טיפול בכפתורי פעולות רגילות
            for (size_t i = 0; i < actionButtons.size(); ++i) {
                if (actionButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Action button " << i << " clicked" << std::endl;
                    
                    if (!game || players.empty()) {
                        std::cout << "Game or players are null" << std::endl;
                        return false;
                    }

                    std::string currentPlayerName = game->turn();
                    std::cout << "Current player: " << currentPlayerName << std::endl;
                    
                    coup::Player* currentPlayer = nullptr;
                    for (auto player : players) {
                        if (player && player->get_name() == currentPlayerName) {
                            currentPlayer = player;
                            break;
                        }
                    }

                    if (!currentPlayer) {
                        std::cout << "Current player not found" << std::endl;
                        return false;
                    }

                    std::cout << "Executing action: " << actions[i] << std::endl;
                    
                    if (currentPlayer->coins() >= 10 && actions[i] != "Coup") {
                        statusText.setString(MUST_COUP_ERROR);
                        centerText(statusText, 50, true);
                        return true;
                    }

                    try {
                        switch (i) {
                            case 0: // Gather
                                std::cout << "Attempting gather" << std::endl;
                                currentPlayer->gather();
                                break;
                                
                            case 1: // Tax
                                std::cout << "Attempting tax" << std::endl;
                                currentPlayer->tax();
                                break;
                                
                            case 2: // Bribe
                                std::cout << "Attempting bribe" << std::endl;
                                if (currentPlayer->coins() >= 4) {
                                    try {
                                        currentPlayer->bribe();
                                        statusText.setString("Bribe successful - you may perform another action");
                                        centerText(statusText, 50, false);
                                        
                                        bool hasJudge = false;
                                        for (const auto* p : players) {
                                            if (p && p->get_role() == "Judge" && p != currentPlayer && p->alive()) {
                                                hasJudge = true;
                                                coupDialog.message.setString("Would you like to cancel " + 
                                                currentPlayer->get_name() + "'s bribe for 4 coins?");
                                                centerTextInButton(coupDialog.message, coupDialog.background);
                                                
                                                pendingCoupAttacker = currentPlayer;
                                                pendingCoupTarget = const_cast<Player*>(p); 
                                                coupDialog.isActive = true;
                                                break;
                                            }
                                        }
                                        
                                        if (!hasJudge) {
                                            currentAction = ActionType::None;  
                                        }
                                        
                                        updatePlayerInfo();
                                        return true;
                                        
                                    } catch (const std::exception& e) {
                                        statusText.setString(e.what());
                                        centerText(statusText, 50, true);
                                        return false;
                                    }
                                } else {
                                    throw std::runtime_error("Not enough coins for Bribe (need 4)");
                                }
                                break;
                                
                            case 3: // Arrest
                                if (players.size() > 1) {
                                    try {
                                        // נסה לבדוק אם השחקן יכול לבצע arrest
                                        currentPlayer->can_perform_arrest();
                                        
                                        // אם הגענו לכאן, אפשר להמשיך עם פעולת ה-arrest
                                        std::cout << "Setting up arrest action..." << std::endl;
                                        statusText.setString("Select a player to arrest");
                                        centerText(statusText, 50);
                                        currentAction = coup::ActionType::Arrest;
                                        
                                    } catch (const std::exception& e) {
                                        // תפיסת השגיאה במקום אחד
                                        std::cout << "Arrest setup failed: " << e.what() << std::endl;
                                        statusText.setString(e.what());
                                        centerText(statusText, 50, true);
                                        currentAction = coup::ActionType::None;
                                    }
                                    return true;
                                }
                                break;
                                
                            case 4: // Sanction
                                if (currentPlayer->coins() >= 3) {
                                    if (players.size() > 1) {
                                        statusText.setString("Select a player to sanction");
                                        centerText(statusText, 50);
                                        currentAction = coup::ActionType::Sanction;
                                        return true;  // הוספת return true כאן
                                    }
                                } else {
                                    throw std::runtime_error("Not enough coins for Sanction (need 3)");
                                }
                                break;
                                
                            case 5: // Coup
                                if (currentPlayer->coins() >= 7) {
                                    if (players.size() > 1) {
                                        statusText.setString("Select a player to coup");
                                        centerText(statusText, 50, false);
                                        currentAction = coup::ActionType::Coup;
                                    }
                                } else {
                                    throw std::runtime_error("Not enough coins for Coup (need 7)");
                                }
                                break;
                        }
                        
                        std::cout << "Action completed successfully" << std::endl;
                        updatePlayerInfo();
                        updateSpecialButtons();
                        
                    } catch (const std::exception& e) {
                        std::cerr << "Action failed: " << e.what() << std::endl;
                        statusText.setString(e.what());
                        centerText(statusText, 50);
                    }
                    return true;
                }
            }

            // טיפול בבחירת שחקן מטרה
            if (currentAction != coup::ActionType::None || currentSpecialAction != SpecialAction::None) {
                handlePlayerSelection(mousePos);
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error in handleEvent: " << e.what() << std::endl;
        statusText.setString(e.what());
        centerText(statusText, 50);
    }
    return false;
}

void GameScreen::handleCoupAction(Player* attacker, Player* target) {
    if (!attacker || !target) return;

    try {
        std::cout << "Executing coup: " << attacker->get_name() 
                  << " -> " << target->get_name() << std::endl;

        // מעדכנים את התצוגה של השחקן המודח
        for (size_t j = 0; j < players.size(); ++j) {
            if (players[j] == target) {
                playerBoxes[j].setFillColor(sf::Color(50, 50, 50));
                std::string playerInfo = target->get_name() + "\n" + 
                                       target->get_role() + "\n(Eliminated)";
                playerTexts[j].setString(playerInfo);
                playerCoinsTexts[j].setString("");
                break;
            }
        }

        // מעדכנים את הסטטוס ומעבירים תור
        statusText.setString(attacker->get_name() + " eliminated " + target->get_name());
        centerText(statusText, 50);

        currentAction = coup::ActionType::None;
        game->next_turn();

        updateStatusText();
        updatePlayerInfo();
        updateSpecialButtons();
        checkGameEnd();

    } catch (const std::exception& e) {
        std::cout << "Coup failed: " << e.what() << std::endl;
        statusText.setString(e.what());
        centerText(statusText, 50, true);
        currentAction = coup::ActionType::None;
    }
}

void GameScreen::checkGameEnd() {
    if (!game) return;
    
    try {
        std::string winner_name;
        std::string winner_role;

        int alive_count = 0;
        for (const auto& player : players) {
            if (player->alive()) {
                alive_count++;
                winner_name = player->get_name();
                winner_role = player->get_role();
            }
        }

        if (alive_count == 1 && !winner_displayed) {
            game_over = true;
            winner_displayed = true;
            setupGameOverScreen(winner_name, winner_role);
        }
    } catch (const std::exception& e) {
        statusText.setString(e.what());
        centerText(statusText, 50);
    }
}

void GameScreen::nextTurn() {
    try {
        if (!game || players.empty()) {
            return;
        }

        game->next_turn();
        
        // איפוס הסטטוס והצבע
        statusText.setFillColor(sf::Color::White);
        updateStatusText();  // קריאה לפונקציה המעודכנת
        
        createSpecialActionButtons();
        updatePlayerInfo();
        
    } catch (const std::exception& e) {
        std::cerr << "Error in nextTurn: " << e.what() << std::endl;
        statusText.setString(e.what());
        centerText(statusText, 50, true);
    }
}

void GameScreen::handlePlayerSelection(const sf::Vector2i& mousePos) {
    std::cout << "Handling player selection at position: " << mousePos.x << "," << mousePos.y << std::endl;
    
    for (size_t i = 0; i < playerBoxes.size(); ++i) {
        sf::FloatRect bounds = playerBoxes[i].getGlobalBounds();
        std::cout << "Checking player box " << i << " bounds: " 
                  << bounds.left << "," << bounds.top << "," 
                  << bounds.width << "," << bounds.height << std::endl;
                  
        if (bounds.contains(mousePos.x, mousePos.y)) {
            std::cout << "Player " << i << " box clicked" << std::endl;
            std::cout << "Current action: " << static_cast<int>(currentAction) << std::endl;
            std::cout << "Current special action: " << static_cast<int>(currentSpecialAction) << std::endl;
            
            try {
                if (!game || players.empty()) {
                    std::cout << "Game or players is null" << std::endl;
                    return;
                }

                std::string currentPlayerName = game->turn();
                coup::Player* currentPlayer = nullptr;
                coup::Player* targetPlayer = players[i];

                for (auto player : players) {
                    if (player && player->get_name() == currentPlayerName) {
                        currentPlayer = player;
                        break;
                    }
                }

                if (!currentPlayer) {
                    std::cout << "Current player not found" << std::endl;
                    return;
                }

                if (!targetPlayer) {
                    std::cout << "Target player not found" << std::endl;
                    return;
                }

                if (currentPlayer == targetPlayer && currentAction != coup::ActionType::None) {
                    std::cout << "Cannot target self" << std::endl;
                    statusText.setString("Cannot target yourself");
                    centerText(statusText, 50);
                    return;
                }

                std::cout << "Current player: " << currentPlayer->get_name() 
                          << ", Target player: " << targetPlayer->get_name() << std::endl;

                if (currentPlayer->coins() >= 10) {
                    if (currentAction != coup::ActionType::Coup) {
                        statusText.setString("You must perform coup when you have 10 or more coins");
                        centerText(statusText, 50);
                        return;
                    }
                }

                if (currentAction == coup::ActionType::Arrest) {
                    std::cout << "Executing arrest action..." << std::endl;
                    try {
                        currentPlayer->arrest(*targetPlayer);
                        std::cout << "Arrest successful" << std::endl;
                        statusText.setString("Arrested " + targetPlayer->get_name());
                        centerText(statusText, 50, false);
                        
                        currentAction = coup::ActionType::None;
                        updatePlayerInfo();
                        
                    } catch (const std::exception& e) {
                        std::cout << "Arrest failed: " << e.what() << std::endl;
                        statusText.setString(e.what());
                        centerText(statusText, 50, true);
                        currentAction = coup::ActionType::None;
                    }
                    return;
                }
                else if (currentAction == coup::ActionType::Sanction) {
                    std::cout << "Executing sanction action..." << std::endl;
                    try {
                        currentPlayer->sanction(*targetPlayer);
                        std::cout << "Sanction successful" << std::endl;
                        statusText.setString("Sanctioned " + targetPlayer->get_name());
                        centerText(statusText, 50, false);
                        currentAction = coup::ActionType::None;
                        updatePlayerInfo();
                    } catch (const std::exception& e) {
                        std::cout << "Sanction failed: " << e.what() << std::endl;
                        statusText.setString(e.what());
                        centerText(statusText, 50, true);
                        currentAction = coup::ActionType::None;
                    }
                }
                else if (currentAction == coup::ActionType::Bribe) {
                    if (targetPlayer->get_role() == "Judge" || targetPlayer == currentPlayer) {
                        statusText.setString("Cannot bribe a Judge or yourself");
                        centerText(statusText, 50, true);
                        currentAction = ActionType::None;
                        return;
                    }

                    Judge* judge = nullptr;
                    for (auto* p : players) {
                        if (p && p->get_role() == "Judge" && p != currentPlayer && p->alive()) {
                            judge = dynamic_cast<Judge*>(p);
                            break;
                        }
                    }

                    currentPlayer->bribe();

                    if (judge) {
                        coupDialog.message.setString("Would you like to cancel " + 
                            currentPlayer->get_name() + "'s bribe?");
                        centerTextInButton(coupDialog.message, coupDialog.background);
                        
                        pendingCoupAttacker = currentPlayer;
                        pendingCoupTarget = judge;
                        coupDialog.isActive = true;
                    } else {
                        game->next_turn();
                    }
                    
                    currentAction = ActionType::None;
                    updatePlayerInfo();
                    return;
                }
                else if (currentAction == coup::ActionType::Coup) {
                    try {
                        // בדיקות מקדימות
                        if (!currentPlayer->alive() || !targetPlayer->alive()) {
                            statusText.setString("Cannot coup with dead players");
                            centerText(statusText, 50);
                            currentAction = coup::ActionType::None;
                            return;
                        }

                        if (currentPlayer->coins() < 7) {
                            statusText.setString("Not enough coins for coup (need 7)");
                            centerText(statusText, 50);
                            currentAction = coup::ActionType::None;
                            return;
                        }

                        // מבצעים את ה-coup
                        currentPlayer->coup(*targetPlayer);  

                        // בודקים אפשרות להגנה של General
                        if (currentPlayer->get_role() != "General") {
                            if (targetPlayer->get_role() == "General" && targetPlayer->coins() >= 5) {
                                coupDialog.message.setString("Block the coup?\nPay 5 coins to protect yourself");
                                centerTextInButton(coupDialog.message, coupDialog.background);
                                pendingCoupAttacker = currentPlayer;
                                pendingCoupTarget = targetPlayer;
                                potentialProtector = targetPlayer;
                                coupDialog.isActive = true;
                                awaitingGeneralResponse = true;
                                return;
                            }
                            
                            // חיפוש General אחר שיכול להגן
                            for (auto player : players) {
                                if (player && player->get_role() == "General" && 
                                    player->alive() && player->coins() >= 5 && 
                                    player != targetPlayer && player != currentPlayer) {
                                    
                                    coupDialog.message.setString("Do you want to protect " + 
                                                            targetPlayer->get_name() + "?\n" +
                                                            "Pay 5 coins to block the coup");
                                    centerTextInButton(coupDialog.message, coupDialog.background);
                                    pendingCoupAttacker = currentPlayer;
                                    pendingCoupTarget = targetPlayer;
                                    potentialProtector = player;
                                    coupDialog.isActive = true;
                                    awaitingGeneralResponse = true;
                                    return;
                                }
                            }
                        }

                        // אם אין General או שהתוקף הוא General
                        targetPlayer->eliminate();
                        handleCoupAction(currentPlayer, targetPlayer);
                        currentPlayer->clear_last_action();
                        
                    } catch (const std::exception& e) {
                        std::cout << "Coup failed: " << e.what() << std::endl;
                        statusText.setString(e.what());
                        centerText(statusText, 50);
                        currentAction = coup::ActionType::None;
                        currentPlayer->clear_last_action();
                    }
                    return;
                }
                else if (awaitingGeneralResponse && pendingCoupTarget == targetPlayer) {
                    if ((targetPlayer->get_role() == "General" && targetPlayer->coins() >= 5) ||
                        (potentialProtector && potentialProtector->get_role() == "General" && 
                         potentialProtector->coins() >= 5)) {
                        
                        General* protectingGeneral = dynamic_cast<General*>(
                            targetPlayer->get_role() == "General" ? targetPlayer : potentialProtector);
                        
                        try {
                            protectingGeneral->block_coup(*pendingCoupAttacker, *pendingCoupTarget);
                            std::cout << "Coup blocked by General" << std::endl;
                            statusText.setString("Coup blocked by " + protectingGeneral->get_name());
                            game->next_turn();
                            updatePlayerInfo();
                        } catch (const std::exception& e) {
                            std::cout << "Block coup failed: " << e.what() << std::endl;
                            statusText.setString(e.what());
                            targetPlayer->eliminate();
                            handleCoupAction(pendingCoupAttacker, pendingCoupTarget);
                        }
                    } else {
                        targetPlayer->eliminate();
                        handleCoupAction(pendingCoupAttacker, pendingCoupTarget);
                        pendingCoupAttacker->clear_last_action();
                    }
                    
                    awaitingGeneralResponse = false;
                    pendingCoupAttacker = nullptr;
                    pendingCoupTarget = nullptr;
                    potentialProtector = nullptr;
                    centerText(statusText, 50);
                }
                else if (currentSpecialAction == SpecialAction::CancelTax) {
                    std::cout << "Attempting to cancel tax... Current player: " << currentPlayer->get_name() << std::endl;
                    if (Governor* governor = dynamic_cast<Governor*>(currentPlayer)) {
                        std::cout << "Governor cast successful" << std::endl;
                        try {
                            // הדפסת מידע לבדיקה
                            std::cout << "Target player: " << targetPlayer->get_name() << std::endl;
                            ActionType lastAction = targetPlayer->get_last_action();
                            std::cout << "Target player's last action: " << static_cast<int>(lastAction) << std::endl;
                            std::cout << "Target player's coins: " << targetPlayer->coins() << std::endl;

                            if (lastAction != ActionType::Tax && lastAction != ActionType::Gather) {
                                std::cout << "Invalid last action" << std::endl;
                                statusText.setString("Player's last action was not tax or gather");
                                centerText(statusText, 50);
                                currentSpecialAction = SpecialAction::None;
                                return;
                            }

                            if (targetPlayer == currentPlayer) {
                                statusText.setString("Cannot cancel your own tax");
                                centerText(statusText, 50);
                                currentSpecialAction = SpecialAction::None;
                                return;
                            }

                            governor->cancel_tax(*targetPlayer);
                            std::cout << "Cancel tax successful" << std::endl;
                            statusText.setString("Tax cancelled for " + targetPlayer->get_name());
                            centerText(statusText, 50);
                            
                            // עדכון המצב והמשך המשחק
                            updatePlayerInfo();
                        } catch (const std::exception& e) {
                            std::cout << "Cancel tax failed: " << e.what() << std::endl;
                            statusText.setString(e.what());
                            centerText(statusText, 50);
                        }
                    } else {
                        statusText.setString("Only Governor can cancel tax");
                        centerText(statusText, 50);
                    }
                    currentSpecialAction = SpecialAction::None;
                    return;
                }
                else if (currentSpecialAction == SpecialAction::BlockArrest) {
                    std::cout << "Attempting to block arrest..." << std::endl;
                    if (Spy* spy = dynamic_cast<Spy*>(currentPlayer)) {
                        std::cout << "Spy cast successful" << std::endl;
                        try {
                            spy->block_arrest(*targetPlayer);
                            std::cout << "Block arrest successful" << std::endl;
                            statusText.setString("Blocked " + targetPlayer->get_name() + " from performing arrest");
                            centerText(statusText, 50, false);
                            currentAction = coup::ActionType::None;
                            currentSpecialAction = SpecialAction::None;
                        } catch (const std::exception& e) {
                            std::cout << "Block arrest failed: " << e.what() << std::endl;
                            statusText.setString(e.what());
                            centerText(statusText, 50, true);
                        }
                    } else {
                        std::cout << "Failed to cast to Spy" << std::endl;
                    }
                }
                else if (currentSpecialAction == SpecialAction::ViewCoins) {
                    showCoinsPopup(targetPlayer->get_name(), targetPlayer->coins());
                }
                
                updatePlayerInfo();
                updateSpecialButtons();

            } catch (const std::exception& e) {
                std::cerr << "Error in player selection: " << e.what() << std::endl;
                statusText.setString(e.what());
                centerText(statusText, 50);
            }
            
            currentAction = coup::ActionType::None;
            currentSpecialAction = SpecialAction::None;
            break;
        }
    }
}

void GameScreen::centerText(sf::Text& text, float yPosition, bool isError) {
    float maxWidth = 600.0f;
    std::string str = text.getString();
    
    bool hasErrorPrefix = (str.substr(0, 6) == "Error:");
    
    if (isError || hasErrorPrefix) {
        if (!hasErrorPrefix) {
            str = "Error: " + str;
            text.setString(str);
        }
        text.setFillColor(sf::Color::Red);
    } else {
        text.setFillColor(sf::Color::White);
    }
    
    sf::FloatRect bounds = text.getLocalBounds();
    if (!game_over && bounds.width > maxWidth) {
        size_t mid = str.find_last_of(" ", str.length()/2);
        if (mid != std::string::npos) {
            str.insert(mid + 1, "\n");
            text.setString(str);
        }
    }
    
    bounds = text.getLocalBounds();
    
    if (game_over) {
        size_t newlines = std::count(str.begin(), str.end(), '\n');
        float totalHeight = bounds.height + (newlines * text.getCharacterSize() * 1.5f);
        text.setOrigin(bounds.left + bounds.width/2.0f, 
                      bounds.top + totalHeight/2.0f);
    } else {
        text.setOrigin(bounds.left + bounds.width/2.0f,
                      bounds.top + bounds.height/2.0f);
    }
    
    text.setPosition(400, yPosition);
}

void GameScreen::draw(sf::RenderWindow& window) {
    try {
        window.clear(sf::Color(30, 30, 30));

        if (game_over && winner_displayed) {
            sf::RectangleShape background(sf::Vector2f(800, 600));
            background.setFillColor(sf::Color(40, 40, 40));
            window.draw(background);

            window.draw(gameOverText);
            window.draw(quitButton);
            window.draw(quitButtonText);
        }
        else if (!validateGameState()) {
            window.draw(quitButton);
            window.draw(quitButtonText);
            if (!statusText.getString().isEmpty()) {
                window.draw(statusText);
            }
        }
        else {
            window.draw(statusText);

            // ציור תיבות השחקנים והטקסט
            for (size_t i = 0; i < playerBoxes.size(); ++i) {
                window.draw(playerBoxes[i]);
                window.draw(playerTexts[i]);
                if (players[i] && players[i]->alive()) {
                    window.draw(playerCoinsTexts[i]);
                }
            }

            // ציור כפתורי פעולה
            for (size_t i = 0; i < actionButtons.size(); ++i) {
                window.draw(actionButtons[i]);
                window.draw(actionTexts[i]);
            }

            // ציור כפתורי פעולה מיוחדים
            for (size_t i = 0; i < specialActionButtons.size(); ++i) {
                window.draw(specialActionButtons[i]);
                if (i < specialActionTexts.size()) {
                    window.draw(specialActionTexts[i]);
                }
            }

            window.draw(skipTurnButton);
            window.draw(skipTurnButtonText);
            window.draw(quitButton);
            window.draw(quitButtonText);

            // ציור חלון הדיאלוג אם הוא פעיל
            if (coupDialog.isActive) {
                // אפקט עמעום לרקע
                sf::RectangleShape dimOverlay(sf::Vector2f(800, 600));
                dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));
                window.draw(dimOverlay);

                // ציור חלון הדיאלוג
                window.draw(coupDialog.background);
                window.draw(coupDialog.message);
                window.draw(coupDialog.yesButton);
                window.draw(coupDialog.yesText);
                window.draw(coupDialog.noButton);
                window.draw(coupDialog.noText);
            }
        }

        window.display();

    } catch (const std::exception& e) {
        std::cerr << "Error in draw: " << e.what() << std::endl;
    }
}

bool GameScreen::shouldGoBack() const {
    return shouldQuit;
}

void GameScreen::clearGame() {
    // ניקוי השחקנים
    for (auto* player : players) {
        delete player;
    }
    players.clear();
    
    // איפוס המשחק
    game = nullptr;
    
    // ניקוי הממשק הגרפי
    playerBoxes.clear();
    playerTexts.clear();
    playerCoinsTexts.clear();
    actionButtons.clear();
    actionTexts.clear();
    
    // איפוס משתני מצב
    currentAction = coup::ActionType::None;
    statusText.setString("");
    centerText(statusText, 50);
    isInitialized = false;
}

void GameScreen::reset() {
    resetGame();
}

void GameScreen::resetGame() {
    std::cout << "Starting game reset..." << std::endl;
    
    // ניקוי השחקנים
    std::cout << "Cleaning up players..." << std::endl;
    for (auto* player : players) {
        if (player != nullptr) {
            delete player;
        }
    }
    players.clear();
    
    // איפוס המשחק
    std::cout << "Resetting game instance..." << std::endl;
    game = nullptr;
    
    // ניקוי הממשק הגרפי
    std::cout << "Clearing GUI components..." << std::endl;
    playerBoxes.clear();
    playerTexts.clear();
    playerCoinsTexts.clear();
    actionButtons.clear();
    actionTexts.clear();
    specialActionButtons.clear();
    specialActionTexts.clear();
    
    // איפוס משתני מצב
    std::cout << "Resetting game state variables..." << std::endl;
    game_over = false;
    winner_displayed = false;
    shouldQuit = false;
    isInitialized = false;
    currentAction = coup::ActionType::None;
    currentSpecialAction = SpecialAction::None;
    
    std::cout << "Game reset completed" << std::endl;
}

void GameScreen::resetGameState() {
    game_over = false;
    winner_displayed = false;
    shouldQuit = false;
    isInitialized = false;
    currentAction = coup::ActionType::None;
}

void GameScreen::setupGameOverScreen(const std::string& winner_name, const std::string& winner_role) {
    gameOverText = sf::Text();
    if (!font.loadFromFile("assets/DejaVuSans.ttf")) {
        return;
    }
    
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER!\n\nWINNER: " + winner_name + "\nROLE: " + winner_role);

    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    gameOverText.setPosition(400, 200);

    quitButton.setPosition((800 - quitButton.getSize().x) / 2, 400);
    quitButtonText.setPosition(
        quitButton.getPosition().x + quitButton.getSize().x / 2.0f,
        quitButton.getPosition().y + quitButton.getSize().y / 2.0f
    );
}

void GameScreen::createSpecialActionButtons() {
    std::cout << "Starting createSpecialActionButtons..." << std::endl;
    
    specialActionButtons.clear();
    specialActionTexts.clear();

    if (!game || players.empty()) {
        std::cout << "Game or players is empty, returning" << std::endl;
        return;
    }

    try {
        std::string currentPlayerName = game->turn();
        std::cout << "Current player: " << currentPlayerName << std::endl;
        
        coup::Player* currentPlayer = nullptr;
        
        for (auto player : players) {
            if (player && player->get_name() == currentPlayerName) {
                currentPlayer = player;
                break;
            }
        }

        if (!currentPlayer) {
            std::cout << "Current player not found, returning" << std::endl;
            return;
        }

        if (currentPlayer->coins() >= 10) {
            skipTurnButton.setFillColor(sf::Color(70, 70, 70));  // צבע כהה יותר כשלא זמין
        } else {
            skipTurnButton.setFillColor(sf::Color(100, 100, 100));  // צבע רגיל
        }

        std::string role = currentPlayer->get_role();
        std::cout << "Current player role: " << role << std::endl;
        
        float buttonY = 500.f;
        float buttonWidth = 120.f;
        float buttonHeight = 30.f;
        float buttonX = 340.f;

        if (role == "Spy" && currentPlayer->alive()) {
            // View Coins button
            sf::RectangleShape viewCoinsButton(sf::Vector2f(buttonWidth, buttonHeight));
            viewCoinsButton.setPosition(buttonX, buttonY);
            viewCoinsButton.setFillColor(sf::Color(100, 100, 100));
            specialActionButtons.push_back(viewCoinsButton);

            // Block Arrest button
            sf::RectangleShape blockArrestButton(sf::Vector2f(buttonWidth, buttonHeight));
            blockArrestButton.setPosition(buttonX, buttonY + buttonHeight + 10.f);
            blockArrestButton.setFillColor(sf::Color(100, 100, 100));
            specialActionButtons.push_back(blockArrestButton);

            // Add texts
            sf::Text viewCoinsText;
            viewCoinsText.setFont(font);
            viewCoinsText.setString("View Coins");
            viewCoinsText.setCharacterSize(14);
            viewCoinsText.setFillColor(sf::Color::White);

            sf::Text blockArrestText;
            blockArrestText.setFont(font);
            blockArrestText.setString("Block Arrest");
            blockArrestText.setCharacterSize(14);
            blockArrestText.setFillColor(sf::Color::White);
            
            centerTextInButton(viewCoinsText, specialActionButtons[0]);
            centerTextInButton(blockArrestText, specialActionButtons[1]);
            
            specialActionTexts.push_back(viewCoinsText);
            specialActionTexts.push_back(blockArrestText);
        }
        else if (role == "Baron" && currentPlayer->alive()) {
            // Invest button
            sf::RectangleShape investButton(sf::Vector2f(buttonWidth, buttonHeight));
            investButton.setPosition(buttonX, buttonY);
            investButton.setFillColor(sf::Color(100, 100, 100));
            specialActionButtons.push_back(investButton);

            // Add text
            sf::Text investText;
            investText.setFont(font);
            investText.setString("Invest");
            investText.setCharacterSize(14);
            investText.setFillColor(sf::Color::White);
            
            centerTextInButton(investText, specialActionButtons[0]);
            specialActionTexts.push_back(investText);
        }
        else if (role == "Governor" && currentPlayer->alive()) {
            // Cancel Tax button
            sf::RectangleShape cancelTaxButton(sf::Vector2f(buttonWidth, buttonHeight));
            cancelTaxButton.setPosition(buttonX, buttonY);
            cancelTaxButton.setFillColor(sf::Color(100, 100, 100));
            specialActionButtons.push_back(cancelTaxButton);

            sf::Text cancelTaxText;
            cancelTaxText.setFont(font);
            cancelTaxText.setString("Cancel Tax");
            cancelTaxText.setCharacterSize(14);
            cancelTaxText.setFillColor(sf::Color::White);
            
            centerTextInButton(cancelTaxText, specialActionButtons[0]);
            specialActionTexts.push_back(cancelTaxText);
        }
        
        std::cout << "Special buttons created successfully" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error in createSpecialActionButtons: " << e.what() << std::endl;
    }
}

void GameScreen::handleSpecialAction(size_t index) {
    if (!game || players.empty()) return;

    std::string currentPlayerName = game->turn();
    coup::Player* currentPlayer = nullptr;
    
    for (auto player : players) {
        if (player && player->get_name() == currentPlayerName) {
            currentPlayer = player;
            break;
        }
    }

    if (!currentPlayer) return;

    std::string role = currentPlayer->get_role();

    try {
        if (role == "Spy") {
            switch (index) {
                case 0:  // View Coins
                    currentSpecialAction = SpecialAction::ViewCoins;
                    statusText.setString("Select a player to view coins");
                    centerText(statusText, 50);
                    break;
                case 1:  // Block Arrest
                    currentSpecialAction = SpecialAction::BlockArrest;
                    statusText.setString("Select a player to block arrest");
                    centerText(statusText, 50);
                    break;
            }
        }
        else if (role == "Baron" && index == 0) {  // Invest action
            if (Baron* baron = dynamic_cast<Baron*>(currentPlayer)) {
                baron->invest();
                updatePlayerInfo();
                updateSpecialButtons();
            }
        }
        else if (role == "Governor" && index == 0) {  // Cancel Tax
            if (Governor* governor = dynamic_cast<Governor*>(currentPlayer)) {
                currentSpecialAction = SpecialAction::CancelTax;
                statusText.setString("Select a player to cancel tax");
                centerText(statusText, 50);
            }
        }
    } catch (const std::exception& e) {
        statusText.setString(e.what());
        centerText(statusText, 50);
    }
}

void GameScreen::centerTextInButton(sf::Text& text, const sf::RectangleShape& button) {
    sf::FloatRect textBounds = text.getLocalBounds();
    float x = button.getPosition().x + (button.getSize().x - textBounds.width) / 2.f;
    float y = button.getPosition().y + (button.getSize().y - textBounds.height) / 2.f;
    text.setPosition(x, y);
}

void GameScreen::showCoinsPopup(const std::string& playerName, int coins) {
    statusText.setString(playerName + " has " + std::to_string(coins) + " coins");
    centerText(statusText, 50);
}

void GameScreen::updateSpecialButtons() {
    createSpecialActionButtons();
}

void GameScreen::initializePopupDialog() {
    // רקע - שינוי הצבע לאפור כהה
    coupDialog.background.setSize(sf::Vector2f(500, 200));
    coupDialog.background.setFillColor(sf::Color(50, 50, 50));  // צבע אפור כהה
    coupDialog.background.setPosition(150, 200);
    
    // טקסט - התאמת גודל ומיקום
    coupDialog.message.setFont(font);
    coupDialog.message.setCharacterSize(20);
    coupDialog.message.setFillColor(sf::Color::White);
    
    // חישוב מיקום הכפתורים
    float dialogCenterX = coupDialog.background.getPosition().x + coupDialog.background.getSize().x / 2;
    float dialogCenterY = coupDialog.background.getPosition().y + coupDialog.background.getSize().y / 2;
    float buttonWidth = 100;
    float buttonHeight = 40;
    float buttonSpacing = 100;
    float buttonsY = coupDialog.background.getPosition().y + coupDialog.background.getSize().y - buttonHeight - 20;
    
    // מיקום הטקסט במרכז החלונית
    coupDialog.message.setPosition(
        dialogCenterX,
        dialogCenterY - 30  // קצת מעל המרכז
    );
    
    // מרכוז הטקסט
    sf::FloatRect textBounds = coupDialog.message.getLocalBounds();
    coupDialog.message.setOrigin(
        textBounds.left + textBounds.width/2.0f,
        textBounds.top + textBounds.height/2.0f
    );
    
    // כפתור Yes
    coupDialog.yesButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    coupDialog.yesButton.setFillColor(sf::Color(0, 100, 0));
    coupDialog.yesButton.setPosition(dialogCenterX - buttonWidth - buttonSpacing/2, buttonsY);
    
    // כפתור No
    coupDialog.noButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    coupDialog.noButton.setFillColor(sf::Color(100, 0, 0));
    coupDialog.noButton.setPosition(dialogCenterX + buttonSpacing/2, buttonsY);
    
    // טקסט הכפתורים
    coupDialog.yesText.setFont(font);
    coupDialog.yesText.setString("Yes");
    coupDialog.yesText.setCharacterSize(20);
    coupDialog.yesText.setFillColor(sf::Color::White);
    
    coupDialog.noText.setFont(font);
    coupDialog.noText.setString("No");
    coupDialog.noText.setCharacterSize(20);
    coupDialog.noText.setFillColor(sf::Color::White);
    
    // מירכוז הטקסטים בכפתורים
    centerTextInButton(coupDialog.yesText, coupDialog.yesButton);
    centerTextInButton(coupDialog.noText, coupDialog.noButton);
}

void GameScreen::handlePopupClick(const sf::Vector2i& mousePos) {
    if (!coupDialog.isActive) return;
    
    try {
        if (coupDialog.yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if (pendingCoupTarget && pendingCoupTarget->get_role() == "Judge") {
                // טיפול בביטול שוחד...
            } 
            else if (pendingCoupTarget->get_role() == "General" || 
                     (potentialProtector && potentialProtector->get_role() == "General")) {
                
                // מקרה של חסימת coup על ידי GENERAL
                General* protectingGeneral = dynamic_cast<General*>(
                    pendingCoupTarget->get_role() == "General" ? 
                    pendingCoupTarget : potentialProtector);
                
                try {
                    protectingGeneral->block_coup(*pendingCoupAttacker, *pendingCoupTarget);
                    
                    std::string blockMessage = protectingGeneral == pendingCoupTarget ?
                        "Coup blocked by " + protectingGeneral->get_name() + " (self-defense)" :
                        "Coup blocked by " + protectingGeneral->get_name() + " (protecting " + pendingCoupTarget->get_name() + ")";
                    
                    statusText.setString(blockMessage);
                    centerText(statusText, 50, false);
                    
                    game->next_turn();
                    updateStatusText();
                    updatePlayerInfo();
                    updateSpecialButtons();
                    
                } catch (const std::exception& e) {
                    statusText.setString(e.what());
                    centerText(statusText, 50, true);
                }
            }
        } 
        else if (coupDialog.noButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            pendingCoupTarget->eliminate();  
            
            for (size_t j = 0; j < players.size(); ++j) {
                if (players[j] == pendingCoupTarget) {
                    playerBoxes[j].setFillColor(sf::Color(50, 50, 50));
                    std::string playerInfo = players[j]->get_name() + "\n" + 
                                          players[j]->get_role() + "\n(Eliminated)";
                    playerTexts[j].setString(playerInfo);
                    playerCoinsTexts[j].setString("");
                    break;
                }
            }

            statusText.setString(pendingCoupTarget->get_name() + " was eliminated by coup");
            centerText(statusText, 50, false);
            
            currentAction = coup::ActionType::None;
            game->next_turn();
            updateStatusText();
            updatePlayerInfo();
            updateSpecialButtons();
            checkGameEnd();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in handlePopupClick: " << e.what() << std::endl;
        statusText.setString(e.what());
        centerText(statusText, 50, true);
    }
    
    // ניקוי המצב בכל מקרה
    coupDialog.isActive = false;
    pendingCoupAttacker = nullptr;
    pendingCoupTarget = nullptr;
    potentialProtector = nullptr;
    updatePlayerInfo();
    updateSpecialButtons();
}

void GameScreen::updateStatusText() {
    if (!game) return;
    
    coup::Player* currentPlayer = nullptr;
    std::string currentPlayerName = game->turn();
    
    for (auto player : players) {
        if (player && player->get_name() == currentPlayerName) {
            currentPlayer = player;
            break;
        }
    }
    
    if (!currentPlayer) return;

    std::string currentStatus = statusText.getString();
    bool isError = currentStatus.substr(0, 6) == "Error:";

    if (currentPlayer->coins() >= 10) {
        if (!isError) {  
            statusText.setString(MUST_COUP_ERROR);
            centerText(statusText, 50, true);
        }
    } else {
        if (!isError) {
            statusText.setString("Current Turn: " + currentPlayerName);
            centerText(statusText, 50, false);
        }
    }
}

bool GameScreen::validateGameState() {
    if (game_over) {
        std::cout << "Game is over - showing end screen" << std::endl;
        return true;
    }
    return game != nullptr && !players.empty() && !playerBoxes.empty() && isInitialized;
}