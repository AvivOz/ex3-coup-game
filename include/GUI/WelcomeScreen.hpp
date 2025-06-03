// aurhor: avivoz4@gmail.com

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class WelcomeScreen
 * @brief Displays the opening screen with game title, background, and buttons to start or exit.
 */
class WelcomeScreen {
private:
    sf::Font font;                     ///< Main font used for all text elements
    sf::Text titleText;                ///< Game title displayed at the top
    sf::RectangleShape startButton;   ///< Button to start the game
    sf::Text startButtonText;         ///< Text displayed inside the start button
    sf::RectangleShape exitButton;    ///< Button to exit the application
    sf::Text exitButtonText;          ///< Text displayed inside the exit button
    bool startGame = false;           ///< Flag to indicate whether the game should start

    sf::Texture backgroundTexture;    ///< Background image texture
    sf::Sprite backgroundSprite;      ///< Sprite used to draw the background image

    /** @brief Initializes fonts, background, title, and buttons. */
    void initializeComponents();

    /**
     * @brief Centers a text horizontally at a given vertical position.
     * @param text Text to be centered
     * @param yPosition Y-axis position for the text
     */
    void centerText(sf::Text& text, float yPosition);

    /**
     * @brief Centers a given string inside a button.
     * @param text Text to update and center
     * @param button The button shape
     * @param str String to assign to the text
     */
    void centerButtonText(sf::Text& text, const sf::RectangleShape& button, const std::string& str);

public:
    /**
     * @brief Constructs the WelcomeScreen and initializes all components.
     */
    WelcomeScreen();

    /**
     * @brief Handles user interactions with the welcome screen.
     * @param event SFML event to process
     * @param window SFML render window
     * @return true if event was handled
     */
    bool handleEvent(const sf::Event& event, sf::RenderWindow& window);

    /**
     * @brief Draws all elements of the welcome screen.
     * @param window SFML render window
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Checks if the user requested to start the game.
     * @return true if Start Game was triggered
     */
    bool shouldStartGame() const;
};
