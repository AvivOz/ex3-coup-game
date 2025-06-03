// author: avivoz4@gmail.com

#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * @class Merchant
     * @brief Represents the Merchant role in the Coup game.
     * 
     * The Merchant gains bonus coins when holding 3 or more coins and also receives a bonus when arrested.
     */
    class Merchant : public Player {
    public:
        /**
         * @brief Constructs a Merchant player.
         * @param game Reference to the game instance
         * @param name Name of the player
         */
        Merchant(Game& game, const std::string& name);

        /**
         * @brief Called when the Merchant is arrested.
         * Applies a bonus or special behavior for being arrested.
         */
        void receive_arrest() override;

        /**
         * @brief Returns the role name.
         * @return The string "Merchant"
         */
        std::string get_role() const override;
    };

}