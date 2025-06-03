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

class GameScreen {
private:

enum class DialogResult {
        None,
        Yes,
        No
    };

struct PopupDialog {
    sf::RectangleShape background;
    sf::Text message;
    sf::RectangleShape yesButton;
    sf::Text yesText;
    sf::RectangleShape noButton;
    sf::Text noText;
    bool isActive = false;
    DialogResult result = DialogResult::None;  
};
    
    PopupDialog coupDialog;
    void initializePopupDialog();
    void handlePopupClick(const sf::Vector2i& mousePos);

    const float MAX_TEXT_WIDTH = 600.0f;
    const std::string MUST_COUP_ERROR = "Error: You have 10 coins or more\nYou must perform coup!";
    sf::Font font;
    sf::Text statusText;
    sf::RectangleShape quitButton;
    sf::Text quitButtonText;
    sf::RectangleShape skipTurnButton;
    sf::Text skipTurnButtonText;
    sf::Text gameOverText;
    sf::RenderWindow* window;
    std::vector<sf::Text> buttonTexts;
    std::vector<sf::RectangleShape> playerBoxes;
    std::vector<sf::Text> playerTexts;
    std::vector<sf::Text> playerCoinsTexts;
    bool game_over = false;
    bool shouldQuit = false;
    bool isInitialized = false;
    bool winner_displayed = false;
    coup::ActionType currentAction = coup::ActionType::None;

    // הוספת המשתנים החדשים לכפתורי פעולות
    std::vector<sf::RectangleShape> actionButtons;
    std::vector<sf::Text> actionTexts;
    std::vector<sf::RectangleShape> specialActionButtons;
    std::vector<sf::Text> specialActionTexts;

    // מצבים חדשים לפעולות מיוחדות
    enum class SpecialAction {
        None,
        ViewCoins,
        BlockArrest,
        CancelTax,
        Invest
    };
    SpecialAction currentSpecialAction = SpecialAction::None;

    // הפעולות הבסיסיות במשחק
    const std::vector<std::string> actions = {
        "Gather",       // gather coins
        "Tax",         // collect tax
        "Bribe",       // pay 2 coins
        "Arrest",      // arrest another player
        "Sanction",    // sanction another player
        "Coup"         // coup another player
    };

    std::unique_ptr<coup::Game> game;
    std::vector<coup::Player*> players;

    coup::Player* pendingCoupAttacker = nullptr;
    coup::Player* pendingCoupTarget = nullptr;
    coup::Player* potentialProtector = nullptr;
    bool awaitingGeneralResponse = false;

    void initializeComponents();
    void createPlayerBoxes();
    void updatePlayerInfo();
    void centerText(sf::Text& text, float yPosition, bool isError = false);
    void nextTurn();
    void initializeActionButtons();
    void resetGame();
    bool validateGameState();
    void handleCoupAction(coup::Player* currentPlayer, coup::Player* targetPlayer);
    void checkGameEnd();
    void resetGameState();
    void setupGameOverScreen(const std::string& winner_name, const std::string& winner_role);
    void handlePlayerSelection(const sf::Vector2i& mousePos);
    void updateStatusText();

    
    // פונקציות חדשות לטיפול בכפתורים מיוחדים
    void createSpecialActionButtons();
    void handleSpecialAction(size_t index);
    void showCoinsPopup(const std::string& playerName, int coins);
    void updateSpecialButtons();
    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
    void clearGame();

public:
    GameScreen();
    ~GameScreen();
    void initializeGame(const std::vector<std::string>& playerNames, 
                       const std::vector<std::string>& roles);
    bool handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool shouldGoBack() const;
    void reset();
};