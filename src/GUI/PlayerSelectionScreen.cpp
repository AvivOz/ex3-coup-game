#include "../include/GUI/PlayerSelectionScreen.hpp"
#include <iostream>

PlayerSelectionScreen::PlayerSelectionScreen() 
    : selectedPlayerCount(0), activeInputBox(-1), namingPhase(false), goBack(false), startGame(false) {
    
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    initializeComponents();
}

void PlayerSelectionScreen::initializeComponents() {
    // כותרת
    titleText.setFont(font);
    titleText.setString("Select Number of Players");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);
    
    // מרכוז הכותרת
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(400, 50);

    // כפתורי בחירת מספר שחקנים
    float startX = 400 - ((5 * 60 + 4 * 20) / 2); // מרכוז הכפתורים
    for (int i = 0; i < 5; ++i) {
        sf::RectangleShape button(sf::Vector2f(60, 60));
        button.setFillColor(sf::Color::Blue);
        button.setPosition(startX + i * 80, 150);
        playerCountButtons.push_back(button);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(i + 2));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        
        // מרכוז המספר בתוך הכפתור
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(startX + 30 + i * 80, 180);
        
        playerCountTexts.push_back(text);
    }

    // כפתור חזרה
    backButton.setSize(sf::Vector2f(100, 40));
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(50, 500);

    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(20);
    backButtonText.setFillColor(sf::Color::White);
    
    // מרכוז טקסט כפתור חזרה
    sf::FloatRect backBounds = backButtonText.getLocalBounds();
    backButtonText.setOrigin(backBounds.width / 2, backBounds.height / 2);
    backButtonText.setPosition(100, 520);

    // כפתור התחל
    startButton.setSize(sf::Vector2f(100, 40));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(650, 500);

    startButtonText.setFont(font);
    startButtonText.setString("Start");
    startButtonText.setCharacterSize(20);
    startButtonText.setFillColor(sf::Color::White);
    
    // מרכוז טקסט כפתור התחל
    sf::FloatRect startBounds = startButtonText.getLocalBounds();
    startButtonText.setOrigin(startBounds.width / 2, startBounds.height / 2);
    startButtonText.setPosition(700, 520);
}

void PlayerSelectionScreen::createPlayerInputs() {
    nameInputBoxes.clear();
    nameTexts.clear();
    playerNames.clear();
    playerNames.resize(selectedPlayerCount);

    float centerX = 400;  // מרכז המסך
    float startY = 150;
    float boxWidth = 300;
    float boxHeight = 40;
    float spacing = 60;  // מרווח בין התיבות

    for (int i = 0; i < selectedPlayerCount; ++i) {
        // תיבת קלט
        sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
        box.setFillColor(sf::Color::White);
        box.setPosition(centerX - (boxWidth / 2), startY + i * spacing);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Blue);
        nameInputBoxes.push_back(box);

        // טקסט
        sf::Text text;
        text.setFont(font);
        text.setString("");  // התחלה עם טקסט ריק
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(centerX - (boxWidth / 2) + 10, startY + i * spacing + 5);
        nameTexts.push_back(text);
    }

    // הפעלת התיבה הראשונה
    if (!nameInputBoxes.empty()) {
        activeInputBox = 0;
        nameInputBoxes[0].setFillColor(sf::Color::Yellow);
    }
}

void PlayerSelectionScreen::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(backButton);
    window.draw(backButtonText);
    
    if (!namingPhase) {
        // ציור כפתורי בחירת מספר שחקנים
        for (size_t i = 0; i < playerCountButtons.size(); ++i) {
            window.draw(playerCountButtons[i]);
            window.draw(playerCountTexts[i]);
        }
    } else {
        // ציור תיבות הקלט והטקסט
        for (size_t i = 0; i < nameInputBoxes.size(); ++i) {
            window.draw(nameInputBoxes[i]);
            window.draw(nameTexts[i]);
        }
        
        // ציור כפתור התחל רק אם כל השמות מולאו
        if (isSelectionComplete()) {
            window.draw(startButton);
            window.draw(startButtonText);
        }
    }
}

bool PlayerSelectionScreen::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            
            // בדיקת לחיצה על כפתור חזרה
            if (backButton.getGlobalBounds().contains(worldPos)) {
                reset();
                goBack = true;
                return true;
            }

            // בדיקת לחיצה על כפתור התחל
            if (namingPhase && isSelectionComplete() && startButton.getGlobalBounds().contains(worldPos)) {
                startGame = true;
                return true;
            }

            if (!namingPhase) {
                // בחירת מספר שחקנים
                for (size_t i = 0; i < playerCountButtons.size(); ++i) {
                    if (playerCountButtons[i].getGlobalBounds().contains(worldPos)) {
                        selectedPlayerCount = i + 2;
                        namingPhase = true;
                        createPlayerInputs();
                        return true;
                    }
                }
            } else {
                // בחירת תיבת טקסט
                for (size_t i = 0; i < nameInputBoxes.size(); ++i) {
                    if (nameInputBoxes[i].getGlobalBounds().contains(worldPos)) {
                        activeInputBox = i;
                        for (size_t j = 0; j < nameInputBoxes.size(); j++) {
                            nameInputBoxes[j].setFillColor(j == i ? sf::Color::Yellow : sf::Color::White);
                        }
                        return true;
                    }
                }
            }
        }
    }
    
    // טיפול בהקלדת טקסט
    if (namingPhase && activeInputBox != -1 && event.type == sf::Event::TextEntered) {
        // Backspace
        if (event.text.unicode == 8) {
            if (!playerNames[activeInputBox].empty()) {
                playerNames[activeInputBox].pop_back();
                nameTexts[activeInputBox].setString(playerNames[activeInputBox]);
            }
            return true;
        }
        // Enter - מעבר לתיבה הבאה רק אם השם הנוכחי לא ריק
        else if (event.text.unicode == 13) {
            if (!playerNames[activeInputBox].empty()) {
                activeInputBox = (activeInputBox + 1) % selectedPlayerCount;
                for (size_t i = 0; i < nameInputBoxes.size(); i++) {
                    nameInputBoxes[i].setFillColor(static_cast<size_t>(activeInputBox) == i ? 
                        sf::Color::Yellow : sf::Color::White);
                }
            }
            return true;
        }
        // תווים רגילים
        else if (event.text.unicode < 128 && event.text.unicode != 8) {
            if (playerNames[activeInputBox].length() < 20) {  // הגבלת אורך השם
                playerNames[activeInputBox] += static_cast<char>(event.text.unicode);
                nameTexts[activeInputBox].setString(playerNames[activeInputBox]);
            }
            return true;
        }
    }

    return false;
}

bool PlayerSelectionScreen::isSelectionComplete() const {
    if (!namingPhase || playerNames.empty()) {
        return false;
    }
    
    // בדיקה שכל השמות הוזנו והם לא ריקים
    for (const auto& name : playerNames) {
        if (name.empty()) {
            return false;
        }
    }
    
    return true;
}

const std::vector<std::string>& PlayerSelectionScreen::getPlayerNames() const {
    return playerNames;
}

void PlayerSelectionScreen::reset() {
    selectedPlayerCount = 0;
    activeInputBox = -1;
    namingPhase = false;
    goBack = false;
    startGame = false;
    playerNames.clear();
    nameInputBoxes.clear();
    nameTexts.clear();
    initializeComponents();
}