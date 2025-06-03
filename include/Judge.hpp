// author: avivoz4@gmail.com

#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * @class Judge
     * @brief Represents the Judge role in the Coup game.
     * 
     * The Judge can cancel bribe actions and is more resistant to sanctions.
     */
    class Judge : public Player {
    public:
        /**
         * @brief Constructs a Judge player.
         * @param game Reference to the game instance
         * @param name Name of the player
         */
        Judge(Game& game, const std::string& name);

        /**
         * @brief Cancels a bribe action performed by another player.
         * @param target The player whose bribe is being canceled
         */
        void cancel_bribe(Player& target);

        /**
         * @brief Called when this Judge is sanctioned.
         * Applies special Judge behavior in response to sanction.
         */
        void receive_sanction() override;

        /**
         * @brief Returns the role name.
         * @return The string "Judge"
         */
        std::string get_role() const override;
    };

}