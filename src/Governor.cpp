// author: avivoz4@gmail.com

#include "Governor.hpp"
#include <stdexcept>
#include <iostream>

using namespace coup;
using namespace std;

Governor::Governor(Game& game, const string& name)
    : Player(game, name) {
    game.add_player(this); 
}

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
    std::cout << "Governor attempting to cancel tax for " << target.get_name() << std::endl;

    if (!target.alive()) {
        throw std::runtime_error("Cannot cancel tax of eliminated player");
    }

    if (target.get_name() == name) {
        throw std::runtime_error("Cannot cancel your own tax");
    }

    if (target.isTaxCancelledForCurrentTurn()) {
        throw std::runtime_error("This player's tax was already cancelled this turn");
    }

    // בדיקת הפעולה האחרונה
    if (target.get_last_action() != ActionType::Tax && target.get_last_action() != ActionType::Gather) {
        throw std::runtime_error("Player's last action was not tax or gather");
    }

    // במקום לנסות להוריד מטבעות ישירות, נשתמש בפונקציה tax_cancelled
    target.tax_cancelled();
    
    last_action = ActionType::Cancel_Tax;
    std::cout << "Tax/Gather cancelled successfully for " << target.get_name() << std::endl;
    game.next_turn();
}

string Governor::get_role() const {
    return "Governor";
}