// aurhor: avivoz4@gmail.com

#pragma once
#include <SFML/Graphics.hpp>

// Forward declarations
class WelcomeScreen;
class PlayerSelectionScreen;
class GameScreen;

enum class Screen {
    Welcome,
    PlayerSelection,
    Game
};

/**
 * GUI class manages the entire graphical flow of the game:
 * window creation, screen switching, event handling, updating and rendering.
 */
class GUI {
private:
    sf::RenderWindow window;                  ///< Main SFML window used for rendering
    Screen currentScreen;                     ///< Enum indicating the currently active screen
    WelcomeScreen* welcomeScreen;             ///< Pointer to the welcome screen
    PlayerSelectionScreen* playerSelectionScreen; ///< Pointer to the player selection screen
    GameScreen* gameScreen;                   ///< Pointer to the main game screen

public:
    /**
     * @brief Constructor. Initializes the SFML window and sets the default screen.
     */
    GUI();

    /**
     * @brief Destructor. Cleans up dynamically allocated screen objects.
     */
    ~GUI();

    /**
     * @brief Handles user input and delegates events to the currently active screen.
     */
    void handleEvents();

    /**
     * @brief Updates logic for the currently active screen (e.g., animations, state changes).
     */
    void update();

    /**
     * @brief Renders the currently active screen and draws it on the SFML window.
     */
    void render();

    /**
     * @brief Switches the current screen to GameScreen.
     * Typically called after the player selection phase is complete.
     */
    void switchToGame();

    /**
     * @brief Runs the main GUI loop.
     * Handles the event loop, screen updates, and rendering until the window is closed.
     */
    void run();
};