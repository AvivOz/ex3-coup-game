// author: avivoz4@gmail.com
#pragma once

#include "Player.hpp"

namespace coup {

    class Spy : public Player {

        public:

            Spy(Game& game, const std::string& name);

            void block_arrest(Player& target);
            std::string get_role() const override;
    };
}