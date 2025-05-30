// author: avivoz4@gmail.com

#include "Spy.hpp"

using namespace coup;
using namespace std;

Spy::Spy(Game& game, const string& name)
    : Player(game, name) {}

void Spy::block_arrest(Player& target) {

    if (!target.alive()) {
        throw std::runtime_error("Cannot block an eliminated player");
    }

    target.block_arrest();
    last_action = ActionType::Block_Arrest;
}

string Spy::get_role() const {
    return "Spy";
}