#pragma once
#include "Player.hpp"
#include "Game.hpp"
#include "Governor.hpp"
#include "Judge.hpp"
#include "General.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"
#include "Spy.hpp"
#include <string>

namespace coup {
    class PlayerFactory {
    public:
        static Player* createPlayer(const std::string& role, Game& game, const std::string& name);
    };
}