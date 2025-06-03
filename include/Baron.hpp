// author: avivoz4@gmail.com

#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * @class Baron
     * @brief Represents the Baron role in the Coup game.
     * 
     * The Baron is a special role that can invest coins and gains a bonus when sanctions are applied.
     */
    class Baron : public Player {
    public:
        /**
         * @brief Constructs a Baron player.
         * @param game Reference to the game instance
         * @param name The name of the player
         */
        Baron(Game& game, const std::string& name);

        /**
         * @brief Executes the Baron's special invest ability.
         * Increases internal investment count and may influence sanction-related logic.
         */
        void invest() override;

        /**
         * @brief Returns the name of the role.
         * @return A string representing the role name: "Baron"
         */
        std::string get_role() const override;

        /**
         * @brief Virtual destructor.
         */
        virtual ~Baron() = default;
    };

} 