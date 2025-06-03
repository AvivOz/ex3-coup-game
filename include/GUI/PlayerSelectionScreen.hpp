#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PlayerSelectionScreen {
private:
    int activeInputBox;
    int selectedPlayerCount;
    bool namingPhase;
    bool goBack;
    bool startGame;
    int focusedInputBox;  // הוספנו משתנה חדש לעקיבה אחר תיבת הקלט הממוקדת

    sf::Font font;
    sf::Text titleText;
    std::vector<sf::RectangleShape> playerCountButtons;
    std::vector<sf::Text> playerCountTexts;
    std::vector<sf::RectangleShape> nameInputBoxes;
    std::vector<sf::Text> nameTexts;
    std::vector<std::string> playerNames;
    std::vector<std::string> availableRoles;
    std::vector<std::string> selectedRoles;
    
    sf::RectangleShape backButton;
    sf::Text backButtonText;
    sf::RectangleShape readyButton;
    sf::Text readyButtonText;

    void initializeComponents();
    void createPlayerInputs();
    void centerText(sf::Text& text, float yPosition);
    void centerButtonText(sf::Text& text, const sf::RectangleShape& button, const std::string& str);
    bool isSelectionComplete() const;
    void assignRandomRoles();
    bool isDuplicateName(const std::string& name, int currentIndex) const;
    void focusNextInput();  // פונקציה חדשה למעבר בין תיבות
    void updateInputBoxColors();  // פונקציה חדשה לעדכון צבעי התיבות

public:
    PlayerSelectionScreen();
    bool handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool shouldGoBack() const;
    bool shouldStartGame() const;
    const std::vector<std::string>& getPlayerNames() const;
    const std::vector<std::string>& getSelectedRoles() const;
    void reset();
};