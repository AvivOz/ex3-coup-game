// aurhor: avivoz4@gmail.com

#include "Judge.hpp"
#include <stdexcept>

using namespace coup;
using namespace std;

Judge::Judge(Game& game, const string& name)
    : Player(game, name) {}

void Judge::cancel_bribe(Player& target) {

    if (!target.alive()) {
        throw runtime_error("Cannot undo bribe of eliminated player");
    }

    if (target.get_last_action() != ActionType::Bribe || !target.is_awaiting_block()) {
        throw runtime_error("Target's last action was not bribe or it is no longer blockable");
    }

    target.clear_last_action();
    last_action = ActionType::Undo;
}

string Judge::get_role() const {
    return "Judge";
}