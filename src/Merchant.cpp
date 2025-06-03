// aurhor: avivoz4@gmail.com

#include "Merchant.hpp"
#include <stdexcept>
using namespace coup;
using namespace std;

Merchant::Merchant(Game& game, const string& name)
    : Player(game, name) {
    game.add_player(this); 
}

void Merchant::receive_arrest() {
    if (coins() >= 2) {
        removeCoins(2);  
    } else if (coins() == 1) {
        removeCoins(1);  
    } else {
        throw std::runtime_error("Target player has no coins");
    }
}

string Merchant::get_role() const {
    return "Merchant";
}