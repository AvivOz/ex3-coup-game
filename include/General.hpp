// author: avivoz4@gmail.com

#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * @class General
     * @brief Represents the General role in the Coup game.
     * 
     * The General has the unique ability to block coup attempts and gains a bonus when arrested.
     */
    class General : public Player {
    public:
        /**
         * @brief Constructs a General player.
         * @param game Reference to the game instance
         * @param name Name of the player
         */
        General(Game& game, const std::string& name);

        /**
         * @brief Blocks a coup attempt made by an attacker against a target.
         * @param attacker The player attempting the coup
         * @param target The intended target of the coup
         */
        void block_coup(Player& attacker, Player& target);

        /**
         * @brief Called when this General is arrested.
         * Applies any special bonus or rule for being arrested.
         */
        void receive_arrest() override;

        /**
         * @brief Returns the role name.
         * @return The string "General"
         */
        std::string get_role() const override;
    };

} 