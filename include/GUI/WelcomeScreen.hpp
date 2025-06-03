// WelcomeScreen.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class WelcomeScreen {
private:
    sf::Font font;
    sf::Text titleText;
    sf::RectangleShape startButton;
    sf::Text startButtonText;
    sf::RectangleShape exitButton;
    sf::Text exitButtonText;
    bool startGame;  
    
    // הוספת המשתנים החדשים לתמונת הרקע
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    void initializeComponents();
    void centerText(sf::Text& text, float yPosition);
    void centerButtonText(sf::Text& text, const sf::RectangleShape& button, const std::string& str);

public:
    WelcomeScreen();
    bool handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool shouldStartGame() const;  
};