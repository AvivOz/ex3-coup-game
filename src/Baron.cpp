// author: avivoz4@gmail.com

#include "Baron.hpp"
#include <stdexcept>

namespace coup {

Baron::Baron(Game& game, const std::string& name)
      : Player(game, name) {
    game.add_player(this); 
}

void Baron::invest() {
    prepare_for_turn();

    if (sanctioned_until_next_turn) {
        throw std::runtime_error("You are sanctioned and cannot invest this turn");
    }

    enforce_coup_requirement();  // בדיקת 10 מטבעות

    if (num_of_coins < 3) {
        throw std::runtime_error("Not enough coins to invest");
    }

    num_of_coins -= 3;  // הורדת המטבעות להשקעה
    num_of_coins += 6;  // קבלת הרווח מההשקעה

    last_action = ActionType::Invest;
    awaiting_block = true;
    game.next_turn();
}

std::string Baron::get_role() const {
    return "Baron";
}

}  