// author: avivoz4@gmail.com

#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * @class Spy
     * @brief Represents the Spy role in the Coup game.
     *
     * The Spy can block arrest attempts against themselves or other players.
     */
    class Spy : public Player {
    public:
        /**
         * @brief Constructs a Spy player.
         * @param game Reference to the game instance
         * @param name Name of the player
         */
        Spy(Game& game, const std::string& name);

        /**
         * @brief Blocks an arrest attempt targeting a player.
         * @param target The player whose arrest is being blocked
         */
        void block_arrest(Player& target);

        /**
         * @brief Returns the role name.
         * @return The string "Spy"
         */
        std::string get_role() const override;
    };

}