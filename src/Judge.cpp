// aurhor: avivoz4@gmail.com

#include "Judge.hpp"
#include <stdexcept>
#include <iostream>

using namespace coup;
using namespace std;

Judge::Judge(Game& game, const string& name)
    : Player(game, name) {
    game.add_player(this); 
}

void Judge::cancel_bribe(Player& target) {
    std::cout << "Judge attempting to cancel bribe for " << target.get_name() << std::endl;

    if (!target.alive()) {
        throw runtime_error("Cannot cancel bribe of eliminated player");
    }

    if (target.get_name() == name) {
        throw runtime_error("Cannot cancel your own bribe");
    }

    if (target.get_last_action() != ActionType::Bribe) {
        throw runtime_error("Target's last action was not bribe");
    }

    if (target.isBribeCancelledForCurrentTurn()) {
        throw runtime_error("This player's bribe was already cancelled this turn");
    }

    target.bribe_cancelled();
    target.clear_last_action();  
    last_action = ActionType::Cancel_Bribe;
    std::cout << "Bribe cancelled successfully for " << target.get_name() << std::endl;
    game.next_turn();
}

void Judge::receive_sanction() {
    Player::receive_sanction();
}

string Judge::get_role() const {
    return "Judge";
}