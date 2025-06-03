// aurhor: avivoz4@gmail.com

#pragma once

#include "Player.hpp"

namespace coup {

    class Merchant : public Player {

        public:

            Merchant(Game& game, const std::string& name);
            void receive_arrest() override;
            std::string get_role() const override;
    };
}