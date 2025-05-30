// aurhor: avivoz4@gmail.com

#pragma once

#include "Player.hpp"

namespace coup {

    class Judge : public Player {

    public:

        Judge(Game& game, const std::string& name);

        void cancel_bribe(Player& target);
        std::string get_role() const override;
    };

}