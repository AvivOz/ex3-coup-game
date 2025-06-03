#include "GUI/PlayerSelectionScreen.hpp"
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>

PlayerSelectionScreen::PlayerSelectionScreen() 
    : activeInputBox(-1)
    , selectedPlayerCount(0)
    , namingPhase(false)
    , goBack(false)
    , startGame(false)
    , focusedInputBox(-1)
{
    initializeComponents();
    availableRoles = {"Governor", "Judge", "General", "Baron", "Merchant", "Spy"};
}

void PlayerSelectionScreen::centerText(sf::Text& text, float yPosition) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(400, yPosition);
}

void PlayerSelectionScreen::centerButtonText(sf::Text& text, const sf::RectangleShape& button, const std::string& str) {
    text.setString(str);
    sf::FloatRect textRect = text.getLocalBounds();
    float xPos = button.getPosition().x + (button.getSize().x - textRect.width) / 2.0f;
    float yPos = button.getPosition().y + (button.getSize().y - textRect.height) / 2.0f;
    text.setPosition(xPos, yPos);
}

void PlayerSelectionScreen::focusNextInput() {
    if (namingPhase) {
        focusedInputBox = (focusedInputBox + 1) % selectedPlayerCount;
        activeInputBox = focusedInputBox;
        updateInputBoxColors();
    }
}

void PlayerSelectionScreen::updateInputBoxColors() {
    for (size_t i = 0; i < nameInputBoxes.size(); ++i) {
        if (static_cast<int>(i) == focusedInputBox) {
            nameInputBoxes[i].setFillColor(sf::Color(100, 100, 100));
        } else {
            nameInputBoxes[i].setFillColor(sf::Color(70, 70, 70));
        }
    }
}

void PlayerSelectionScreen::initializeComponents() {
    if (!font.loadFromFile("assets/DejaVuSans.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Title setup
    titleText.setFont(font);
    titleText.setString("Select number of players");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);
    centerText(titleText, 80);

    // Player count buttons
    float startX = 200;
    float spacing = 100;
    for (int i = 2; i <= 6; ++i) {
        sf::RectangleShape button(sf::Vector2f(60, 60));
        button.setPosition(startX + (i-2) * spacing, 200);
        button.setFillColor(sf::Color(100, 100, 100));
        playerCountButtons.push_back(button);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(i));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        text.setPosition(
            button.getPosition().x + button.getSize().x/2.0f,
            button.getPosition().y + button.getSize().y/2.0f
        );
        playerCountTexts.push_back(text);
    }

    // Back button
    backButton.setSize(sf::Vector2f(120, 50));
    backButton.setPosition(50, 500);
    backButton.setFillColor(sf::Color(100, 100, 100));
    
    backButtonText.setFont(font);
    backButtonText.setCharacterSize(24);
    backButtonText.setFillColor(sf::Color::White);
    centerButtonText(backButtonText, backButton, "Back");

    // Ready button
    readyButton.setSize(sf::Vector2f(120, 50));
    readyButton.setPosition(630, 500);
    readyButton.setFillColor(sf::Color(100, 100, 100));
    
    readyButtonText.setFont(font);
    readyButtonText.setCharacterSize(24);
    readyButtonText.setFillColor(sf::Color::White);
    centerButtonText(readyButtonText, readyButton, "Ready");
}

void PlayerSelectionScreen::createPlayerInputs() {
    nameInputBoxes.clear();
    nameTexts.clear();
    playerNames.clear();
    playerNames.resize(selectedPlayerCount);

    float startY = 200;
    float spacing = 60;
    
    for (int i = 0; i < selectedPlayerCount; ++i) {
        sf::RectangleShape inputBox(sf::Vector2f(300, 40));
        inputBox.setPosition(250, startY + i * spacing);
        inputBox.setFillColor(sf::Color(70, 70, 70));
        nameInputBoxes.push_back(inputBox);

        sf::Text nameText;
        nameText.setFont(font);
        nameText.setCharacterSize(20);
        nameText.setFillColor(sf::Color::White);
        nameText.setString("Player " + std::to_string(i + 1));  // ברירת מחדל
        playerNames[i] = "";  // השם עצמו נשאר ריק
        nameText.setPosition(260, startY + i * spacing + 10);
        nameTexts.push_back(nameText);
    }

    focusedInputBox = 0;
    activeInputBox = 0;
    updateInputBoxColors();
}

bool PlayerSelectionScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // טיפול בכפתור Back
        if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if (namingPhase) {
                namingPhase = false;
                focusedInputBox = -1;
                activeInputBox = -1;
            } else {
                goBack = true;
            }
            return true;
        }

        if (!namingPhase) {
            // בחירת מספר שחקנים
            for (size_t i = 0; i < playerCountButtons.size(); ++i) {
                if (playerCountButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    selectedPlayerCount = i + 2;
                    namingPhase = true;
                    createPlayerInputs();
                    return true;
                }
            }
        } else {
            // בחירת תיבת טקסט להזנת שם
            for (size_t i = 0; i < nameInputBoxes.size(); ++i) {
                if (nameInputBoxes[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    focusedInputBox = i;
                    activeInputBox = i;
                    updateInputBoxColors();
                    return true;
                }
            }

            // לחיצה על כפתור Ready
            if (isSelectionComplete() && readyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                assignRandomRoles();
                startGame = true;
                return true;
            }
        }

        // לחיצה מחוץ לתיבות הטקסט
        focusedInputBox = -1;
        activeInputBox = -1;
        updateInputBoxColors();
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (namingPhase) {
            if (event.key.code == sf::Keyboard::Tab) {
                focusNextInput();
                return true;
            }
            else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Enter) {
                if (isSelectionComplete()) {
                    assignRandomRoles();
                    startGame = true;
                    return true;
                }
                focusNextInput();
                return true;
            }
        }
    }
    else if (event.type == sf::Event::TextEntered && activeInputBox != -1) {
    if (event.text.unicode == '\b') {  // Backspace
        if (!playerNames[activeInputBox].empty()) {
            playerNames[activeInputBox].pop_back();
            nameTexts[activeInputBox].setString(playerNames[activeInputBox].empty() ? 
                "Player " + std::to_string(activeInputBox + 1) :  // אם ריק, חזור לברירת מחדל
                playerNames[activeInputBox]);                      // אחרת, הצג את השם
        }
    }
    else if (event.text.unicode < 128) {  // תווים רגילים באנגלית
        char inputChar = static_cast<char>(event.text.unicode);
        if (playerNames[activeInputBox].length() < 20 &&  // הגבלת אורך השם
            (isalnum(inputChar) || inputChar == ' ')) {   // רק אותיות, מספרים ורווחים
            
            playerNames[activeInputBox] += inputChar;
            if (!isDuplicateName(playerNames[activeInputBox], activeInputBox)) {
                nameTexts[activeInputBox].setString(playerNames[activeInputBox]);
            } else {
                playerNames[activeInputBox].pop_back();  // ביטול הוספת התו
            }
        }
    }
    }

    return false;
}

void PlayerSelectionScreen::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(backButton);
    window.draw(backButtonText);

    if (!namingPhase) {
        for (size_t i = 0; i < playerCountButtons.size(); ++i) {
            window.draw(playerCountButtons[i]);
            window.draw(playerCountTexts[i]);
        }
    } else {
        for (size_t i = 0; i < nameInputBoxes.size(); ++i) {
            window.draw(nameInputBoxes[i]);
            window.draw(nameTexts[i]);
        }
        
        if (isSelectionComplete()) {
            window.draw(readyButton);
            window.draw(readyButtonText);
        }
    }
}

bool PlayerSelectionScreen::isSelectionComplete() const {
    if (playerNames.size() != static_cast<size_t>(selectedPlayerCount)) {
        return false;
    }
    
    for (const auto& name : playerNames) {
        if (name.empty()) {
            return false;
        }
    }
    return true;
}

bool PlayerSelectionScreen::isDuplicateName(const std::string& name, int currentIndex) const {
    if (name.empty()) {
        return false;
    }
    
    for (size_t i = 0; i < playerNames.size(); ++i) {
        if (static_cast<int>(i) != currentIndex && playerNames[i] == name) {
            return true;
        }
    }
    return false;
}

void PlayerSelectionScreen::reset() {
    activeInputBox = -1;
    focusedInputBox = -1;
    selectedPlayerCount = 0;
    namingPhase = false;
    goBack = false;
    startGame = false;
    playerNames.clear();
    selectedRoles.clear();
    nameInputBoxes.clear();
    nameTexts.clear();
}

bool PlayerSelectionScreen::shouldGoBack() const {
    return goBack;
}

bool PlayerSelectionScreen::shouldStartGame() const {
    return startGame;
}

const std::vector<std::string>& PlayerSelectionScreen::getPlayerNames() const {
    return playerNames;
}

const std::vector<std::string>& PlayerSelectionScreen::getSelectedRoles() const {
    return selectedRoles;
}

void PlayerSelectionScreen::assignRandomRoles() {
    selectedRoles.clear();
    selectedRoles.resize(selectedPlayerCount);
    
    std::vector<size_t> indices(availableRoles.size());
    std::iota(indices.begin(), indices.end(), 0);
    
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));
    
    for (int i = 0; i < selectedPlayerCount; ++i) {
        selectedRoles[i] = availableRoles[indices[i]];
    }
}