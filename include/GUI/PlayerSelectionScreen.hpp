// aurhor: avivoz4@gmail.com

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/**
 * @class PlayerSelectionScreen
 * @brief Handles player count selection, name input, and role assignment before the game starts.
 */
class PlayerSelectionScreen {
private:
    int activeInputBox = -1;         ///< Index of currently active input box
    int selectedPlayerCount = 0;     ///< Number of players selected
    bool namingPhase = false;        ///< Whether the screen is in name-input mode
    bool goBack = false;             ///< Flag to indicate transition to welcome screen
    bool startGame = false;          ///< Flag to indicate start of game
    int focusedInputBox = -1;        ///< Index of focused input box for keyboard input

    sf::Font font;                   ///< Font used for all text
    sf::Text titleText;              ///< Title at the top of the screen

    std::vector<sf::RectangleShape> playerCountButtons; ///< Buttons for selecting number of players
    std::vector<sf::Text> playerCountTexts;             ///< Text labels on player count buttons

    std::vector<sf::RectangleShape> nameInputBoxes;     ///< Rectangles representing name input fields
    std::vector<sf::Text> nameTexts;                    ///< Texts showing typed player names
    std::vector<std::string> playerNames;               ///< Stores the actual inputted player names
    std::vector<std::string> availableRoles;            ///< All role options from which to assign randomly
    std::vector<std::string> selectedRoles;             ///< Randomly assigned roles for players

    sf::RectangleShape backButton;    ///< Button for going back to welcome screen
    sf::Text backButtonText;          ///< Text inside back button

    sf::RectangleShape readyButton;   ///< Button to proceed to game
    sf::Text readyButtonText;         ///< Text inside ready button

    /** @brief Initializes fonts, title, and all screen elements. */
    void initializeComponents();

    /** @brief Creates input boxes based on selected player count. */
    void createPlayerInputs();

    /**
     * @brief Centers a given text horizontally on screen at the given Y position.
     * @param text The text object to center
     * @param yPosition Y coordinate for vertical placement
     */
    void centerText(sf::Text& text, float yPosition);

    /**
     * @brief Centers a text inside a given button.
     * @param text Text object to modify
     * @param button Rectangle button
     * @param str String to set in the text
     */
    void centerButtonText(sf::Text& text, const sf::RectangleShape& button, const std::string& str);

    /** @brief Checks whether all required names have been entered. */
    bool isSelectionComplete() const;

    /** @brief Assigns roles randomly from the available list. */
    void assignRandomRoles();

    /**
     * @brief Checks if the entered name already exists.
     * @param name Name to check
     * @param currentIndex Index of the box being edited
     * @return true if the name already exists in another box
     */
    bool isDuplicateName(const std::string& name, int currentIndex) const;

    /** @brief Moves focus to the next available input box. */
    void focusNextInput();

    /** @brief Updates visual color indicators of input boxes. */
    void updateInputBoxColors();

public:
    /** @brief Constructor for PlayerSelectionScreen. Initializes all GUI elements. */
    PlayerSelectionScreen();

    /**
     * @brief Handles user input (mouse, keyboard) for the player selection phase.
     * @param event SFML event to handle
     * @param window Reference to render window
     * @return true if handled
     */
    bool handleEvent(const sf::Event& event, sf::RenderWindow& window);

    /**
     * @brief Draws all screen elements to the given window.
     * @param window SFML render window
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Checks if the back button was triggered.
     * @return true if returning to welcome screen
     */
    bool shouldGoBack() const;

    /**
     * @brief Checks if player names were entered and game is ready to start.
     * @return true if game should start
     */
    bool shouldStartGame() const;

    /**
     * @brief Returns reference to the finalized list of player names.
     * @return const reference to player names vector
     */
    const std::vector<std::string>& getPlayerNames() const;

    /**
     * @brief Returns reference to the list of randomly assigned roles.
     * @return const reference to roles vector
     */
    const std::vector<std::string>& getSelectedRoles() const;

    /** @brief Resets the screen to its initial state. */
    void reset();
};