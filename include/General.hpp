// aurhor: avivoz4@gmail.com

#pragma once

#include "Player.hpp"

namespace coup {

    class General : public Player {

    public:
        General(Game& game, const std::string& name);

        void block_coup(Player& attacker, Player& target);
        void receive_arrest() override;
        std::string get_role() const override;
    };

}