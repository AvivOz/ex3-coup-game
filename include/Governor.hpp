// author: avivoz4@gmail.com

#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * @class Governor
     * @brief Represents the Governor role in the Coup game.
     * 
     * The Governor can collect increased tax and has the ability to cancel tax actions performed by others.
     */
    class Governor : public Player {
    public:
        /**
         * @brief Constructs a Governor player.
         * @param game Reference to the game instance
         * @param name The name of the player
         */
        Governor(Game& game, const std::string& name);

        /**
         * @brief Executes the Governor's enhanced tax ability.
         * Adds 3 coins to the player's total.
         */
        void tax() override;

        /**
         * @brief Cancels a tax action performed by another player.
         * @param target The player whose tax is being cancelled
         */
        void cancel_tax(Player& target);

        /**
         * @brief Returns the role name.
         * @return The string "Governor"
         */
        std::string get_role() const override;
    };

}