// author: avivoz4@gmail.com

#pragma once

#include "Player.hpp"

namespace coup {

    class Governor : public Player {

    public:
    
        Governor(Game& game, const std::string& name);

        void tax() override;
        void cancel_tax(Player& target);
        std::string get_role() const override;
    };

}
