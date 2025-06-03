// author: avivoz4@gmail.com

#pragma once
#include "Player.hpp"

namespace coup {
    class Baron : public Player {
        public: 
            Baron(Game& game, const std::string& name);
            void invest() override;
            std::string get_role() const override;
            virtual ~Baron() = default;
    };
}