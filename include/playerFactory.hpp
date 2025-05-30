#pragma once

#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Game.hpp"
#include <vector>
#include <string>

using namespace coup;
using std::string;
using std::vector;

namespace coup {

    /**
     * @brief this function creates a player according to the role and adds it to the playersList in use for the GUI.
     */
    Player* playerFactory(Game& game, const std::string& name);

}
