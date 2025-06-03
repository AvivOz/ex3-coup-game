// author: avivoz4@gmail.com

#pragma once
#include <vector>
#include <string>

namespace coup {

    class Player;

    /**
     * @class Game
     * @brief Manages the overall game state, player turns, and game rules.
     */
    class Game {
    private:
        std::vector<Player*> players;        ///< List of all players in the game
        size_t current_player_index = 0;     ///< Index of the player whose turn it is
        bool game_started = false;           ///< Whether the game has officially started

        /**
         * @brief Checks if a player at a given index is alive.
         * @param index Index of the player in the players vector
         * @return true if the player is still in the game
         */
        bool is_alive(size_t index) const;

    public:
        /** @brief Constructor for the Game class. */
        Game();

        /**
         * @brief Returns a list of all current player names.
         * @return Vector of player names
         */
        std::vector<std::string> players_list() const;

        /**
         * @brief Returns the name of the player whose turn it is.
         * @return String containing the name of the current player
         */
        std::string turn() const;

        /**
         * @brief Returns the name of the winner (if one remains).
         * @return String containing the winner's name
         * @throws runtime_error if the game is not yet over
         */
        std::string winner() const;

        /**
         * @brief Moves the game to the next alive player's turn.
         */
        void next_turn();

        /**
         * @brief Adds a new player to the game.
         * @param player Pointer to the player to add
         * @throws runtime_error if game has already started or max players reached
         */
        void add_player(Player* player);

        /**
         * @brief Applies a coup against the given player.
         * @param target Reference to the player to eliminate
         */
        void apply_coup(Player& target);

        /**
         * @brief Checks whether the game has started.
         * @return true if the game has started
         */
        bool has_started() const;

        /**
         * @brief Returns the number of players currently in the game.
         * @return Size_t value of player count
         */
        size_t num_of_players() const;

        /**
         * @brief Finds the index of a given player.
         * @param player Pointer to the player to search for
         * @return Index of the player in the players vector
         * @throws runtime_error if player not found
         */
        size_t find_player_index(Player* player) const;

        /**
         * @brief Returns a pointer to the current player.
         * @return Pointer to the player whose turn it is
         */
        Player* getCurrentPlayer() const;
    };

} 