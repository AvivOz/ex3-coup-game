// aurhor: avivoz4@gmail.com

#include "Baron.hpp"

using namespace coup;
using namespace std;

Baron::Baron(Game& game, const string& name)
    : Player(game,  name) {}

void Baron::invest() {

    if (num_of_coins < 3) {
        throw runtime_error("Not enough coins to invest");
    }

    if (sanctioned_until_next_turn) {
        throw runtime_error("You are sanctioned and cannot invest this turn");
    }

    num_of_coins -= 3;
    num_of_coins += 6;

    last_action = ActionType::Invest;
    awaiting_block = true;
    sanctioned_until_next_turn = false;
    can_arrest = true;

    game.next_turn();
}

string Baron::get_role() const {
    return "Baron";
}
 