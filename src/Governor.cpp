// author: avivoz4@gmail.com

#include "Governor.hpp"

using namespace coup;
using namespace std;

Governor::Governor(Game& game, const string& name)
    : Player(game, name) {}

void Governor::tax() {

    if (sanctioned_until_next_turn) {
        throw runtime_error("You are sanctioned and cannot perform tax this turn");
    }

    num_of_coins += 3; 
    sanctioned_until_next_turn = false;
    can_arrest = true;
    last_action = ActionType::Tax;
    game.next_turn();
}

void Governor::cancel_tax(Player& target) {
    if (!target.alive()) {
        throw runtime_error("Cannot cancel tax of eliminated player");
    }

    if (target.coins() < 2) {
        throw runtime_error("Target does not have enough coins to cancel the tax action he did");
    }

    if (!target.is_awaiting_block() || target.get_last_action() != ActionType::Tax) {
        throw runtime_error("Target's last action was not tax or it is no longer blockable");
    }

    target.removeCoins(2);
    last_action = ActionType::Undo;
}

string Governor::get_role() const {
    return "Governor";
}