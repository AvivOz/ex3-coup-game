// author: avivoz4@gmail.com

#pragma once
#include "Player.hpp"
#include "Game.hpp"
#include "Governor.hpp"
#include "Judge.hpp"
#include "General.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"
#include "Spy.hpp"
#include <string>

namespace coup {

    /**
     * @class PlayerFactory
     * @brief Factory class for creating Player instances based on role.
     * 
     * Provides a single static method to generate concrete Player-derived objects
     * such as Governor, Judge, General, etc., based on role name strings.
     */
    class PlayerFactory {
    public:
        /**
         * @brief Creates a Player object based on the given role string.
         *
         * @param role The name of the role (e.g., "Governor", "Spy", etc.)
         * @param game Reference to the game instance
         * @param name The player's name
         * @return Pointer to a dynamically allocated Player object of the appropriate subclass
         * @throws std::invalid_argument if the role name is invalid
         */
        static Player* createPlayer(const std::string& role, Game& game, const std::string& name);
    };

}