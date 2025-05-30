// aurhor: avivoz4@gmail.com

#include "Merchant.hpp"

using namespace coup;
using namespace std;

Merchant::Merchant(Game& game, const string& name)
    : Player(game, name) {}

string Merchant::get_role() const {
    return "Merchant";
}