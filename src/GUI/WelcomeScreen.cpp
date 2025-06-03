#include "GUI/WelcomeScreen.hpp"

WelcomeScreen::WelcomeScreen() : startGame(false) {
    initializeComponents();
}

void WelcomeScreen::centerText(sf::Text& text, float yPosition) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(400, yPosition);
}

void WelcomeScreen::centerButtonText(sf::Text& text, const sf::RectangleShape& button, const std::string& str) {
    text.setString(str);
    sf::FloatRect textRect = text.getLocalBounds();
    float xPos = button.getPosition().x + (button.getSize().x - textRect.width) / 2.0f;
    float yPos = button.getPosition().y + (button.getSize().y - textRect.height) / 2.0f;
    text.setPosition(xPos, yPos);
}

void WelcomeScreen::initializeComponents() {
    // טעינת התמונה
    if (!backgroundTexture.loadFromFile("assets/photos/WelcomeScreenBackground.png")) {
        throw std::runtime_error("Failed to load background image");
    }
    
    // הגדרת הספרייט של הרקע
    backgroundSprite.setTexture(backgroundTexture);
    
    // התאמת גודל התמונה לחלון
    float scaleX = 800.0f / backgroundTexture.getSize().x;
    float scaleY = 600.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    if (!font.loadFromFile("assets/DejaVuSans.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Title setup
    titleText.setFont(font);
    titleText.setString("Welcome to Coup Game");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    centerText(titleText, 150);

    // Start button setup
    startButton.setSize(sf::Vector2f(200, 50));
    startButton.setPosition(300, 300);
    startButton.setFillColor(sf::Color(100, 100, 100));

    startButtonText.setFont(font);
    startButtonText.setCharacterSize(24);
    startButtonText.setFillColor(sf::Color::White);
    centerButtonText(startButtonText, startButton, "Start Game");

    // Exit button setup
    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setPosition(300, 380);
    exitButton.setFillColor(sf::Color(100, 100, 100));

    exitButtonText.setFont(font);
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::White);
    centerButtonText(exitButtonText, exitButton, "Exit");
}

bool WelcomeScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            startGame = true;
            return true;
        }
        
        if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            window.close();
        }
    }
    return false;
}

void WelcomeScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);  
    window.draw(titleText);
    window.draw(startButton);
    window.draw(startButtonText);
    window.draw(exitButton);
    window.draw(exitButtonText);
}

bool WelcomeScreen::shouldStartGame() const {
    return startGame;
}