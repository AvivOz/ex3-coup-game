// aurhor: avivoz4@gmail.com

#include "General.hpp"
#include "Game.hpp"
#include <stdexcept>


using namespace coup;
using namespace std;

General::General(Game& game, const string& name)
    : Player(game, name) {
    game.add_player(this); 
}

void General::block_coup(Player& attacker, Player& target) {
    if (!alive()) {
        throw runtime_error("General is eliminated and cannot block coup");
    }

    if (!target.alive()) {
        throw runtime_error("Target is already eliminated");
    }

    if (num_of_coins < 5) {
        throw runtime_error("General does not have enough coins to block coup");
    }

    if (!attacker.is_awaiting_block() || attacker.get_last_action() != ActionType::Coup) {
        throw runtime_error("There is no coup to block");
    }

    num_of_coins -= 5;  

    last_action = ActionType::Block_Coup;
    target.undo_elimination();
    target.reset_sanctions();
    attacker.clear_last_action();
}

void General::receive_arrest() {
    if (coins() > 0) {
        removeCoins(1);  
        addCoins(1);     
    } else {
        throw std::runtime_error("Target player has no coins");
    }
}

string General::get_role() const {
    return "General";
}