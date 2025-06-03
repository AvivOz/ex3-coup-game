// aurhor: avivoz4@gmail.com

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Judge.hpp"
#include "General.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"
#include "Spy.hpp"

namespace coup {
    class Game;
    class Player;
    class Governor;
    class Judge;
    class General;
    class Baron;
    class Merchant;
    class Spy;
}

/**
 * @class GameScreen
 * @brief Handles the graphical user interface and game logic during gameplay.
 */
class GameScreen {
private:
    enum class DialogResult {
        None,  ///< No dialog result
        Yes,   ///< Player confirmed
        No     ///< Player declined
    };

    struct PopupDialog {
        sf::RectangleShape background; ///< Background of the dialog
        sf::Text message;              ///< Message text
        sf::RectangleShape yesButton; ///< 'Yes' button
        sf::Text yesText;             ///< Text for 'Yes'
        sf::RectangleShape noButton;  ///< 'No' button
        sf::Text noText;              ///< Text for 'No'
        bool isActive = false;        ///< Whether dialog is active
        DialogResult result = DialogResult::None; ///< Current dialog result
    };

    PopupDialog coupDialog; ///< Dialog shown when coup is mandatory

    /** @brief Initializes the popup dialog components. */
    void initializePopupDialog();

    /** @brief Handles user clicks inside the popup dialog. */
    void handlePopupClick(const sf::Vector2i& mousePos);

    const float MAX_TEXT_WIDTH = 600.0f; ///< Max width for wrapped error/status text
    const std::string MUST_COUP_ERROR = "Error: You have 10 coins or more\nYou must perform coup!"; ///< Error message for coup enforcement

    sf::Font font;
    sf::Text statusText;
    sf::RectangleShape quitButton;
    sf::Text quitButtonText;
    sf::RectangleShape skipTurnButton;
    sf::Text skipTurnButtonText;
    sf::Text gameOverText;
    sf::RenderWindow* window = nullptr;

    std::vector<sf::Text> buttonTexts;
    std::vector<sf::RectangleShape> playerBoxes;
    std::vector<sf::Text> playerTexts;
    std::vector<sf::Text> playerCoinsTexts;

    bool game_over = false;
    bool shouldQuit = false;
    bool isInitialized = false;
    bool winner_displayed = false;

    coup::ActionType currentAction = coup::ActionType::None;

    std::vector<sf::RectangleShape> actionButtons;
    std::vector<sf::Text> actionTexts;
    std::vector<sf::RectangleShape> specialActionButtons;
    std::vector<sf::Text> specialActionTexts;

    enum class SpecialAction {
        None,
        ViewCoins,
        BlockArrest,
        CancelTax,
        Invest
    };

    SpecialAction currentSpecialAction = SpecialAction::None;

    const std::vector<std::string> actions = {
        "Gather", "Tax", "Bribe", "Arrest", "Sanction", "Coup"
    };

    std::unique_ptr<coup::Game> game;
    std::vector<coup::Player*> players;

    coup::Player* pendingCoupAttacker = nullptr;
    coup::Player* pendingCoupTarget = nullptr;
    coup::Player* potentialProtector = nullptr;
    bool awaitingGeneralResponse = false;

    /** @brief Initializes all UI components. */
    void initializeComponents();

    /** @brief Creates boxes for each player on screen. */
    void createPlayerBoxes();

    /** @brief Updates displayed player names and coins. */
    void updatePlayerInfo();

    /** @brief Centers text horizontally at a given Y position. */
    void centerText(sf::Text& text, float yPosition, bool isError = false);

    /** @brief Advances to the next player's turn. */
    void nextTurn();

    /** @brief Initializes action buttons. */
    void initializeActionButtons();

    /** @brief Resets the entire game state and visuals. */
    void resetGame();

    /** @brief Validates if the game is in a playable state. */
    bool validateGameState();

    /**
     * @brief Handles coup logic between two players.
     * @param currentPlayer Attacking player
     * @param targetPlayer Target of the coup
     */
    void handleCoupAction(coup::Player* currentPlayer, coup::Player* targetPlayer);

    /** @brief Checks if the game has ended. */
    void checkGameEnd();

    /** @brief Resets internal gameplay state without visuals. */
    void resetGameState();

    /** @brief Displays winner text and highlights the winner. */
    void setupGameOverScreen(const std::string& winner_name, const std::string& winner_role);

    /** @brief Handles selection of players for actions. */
    void handlePlayerSelection(const sf::Vector2i& mousePos);

    /** @brief Updates the top status text based on game state. */
    void updateStatusText();

    /** @brief Creates buttons for special role-specific actions. */
    void createSpecialActionButtons();

    /**
     * @brief Executes the selected special action.
     * @param index Index of the selected special action
     */
    void handleSpecialAction(size_t index);

    /**
     * @brief Displays a popup showing a player's coin count.
     * @param playerName Name of the target player
     * @param coins Number of coins to show
     */
    void showCoinsPopup(const std::string& playerName, int coins);

    /** @brief Updates visibility and state of special action buttons. */
    void updateSpecialButtons();

    /**
     * @brief Centers text within a given button.
     * @param text Text to center
     * @param button Button used as reference
     */
    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);

    /** @brief Clears all game-related resources and resets GUI state. */
    void clearGame();

public:
    /** @brief Constructor for the GameScreen. */
    GameScreen();

    /** @brief Destructor for GameScreen. */
    ~GameScreen();

    /**
     * @brief Initializes the game with given player names and assigned roles.
     * @param playerNames Vector of player names
     * @param roles Vector of roles assigned to each player
     */
    void initializeGame(const std::vector<std::string>& playerNames, const std::vector<std::string>& roles);

    /**
     * @brief Handles input events such as mouse clicks.
     * @param event The SFML event to process
     * @param window Reference to the SFML window
     * @return true if event was handled
     */
    bool handleEvent(const sf::Event& event, sf::RenderWindow& window);

    /**
     * @brief Renders all game elements to the window.
     * @param window The SFML window to draw on
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Checks if the user has requested to exit the game.
     * @return true if quit was requested
     */
    bool shouldGoBack() const;

    /** @brief Resets the screen and game state to allow new game start. */
    void reset();
};