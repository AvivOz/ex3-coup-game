#include "Player.hpp"
#include <stdexcept>

using namespace coup;
using namespace std;

Player::Player(Game& game, const string& name)
    : name(name), game(game), num_of_coins(0), is_alive(true),
      sanctioned_until_next_turn(false), can_arrest(true),
      awaiting_block(false), last_action(ActionType::None),
      bonus_applied(false), taxCancelledThisTurn(false), bribeCancelledThisTurn(false) {
    game.add_player(this);
}

bool Player::isTaxCancelledForCurrentTurn() const {
    return taxCancelledThisTurn;
}

void Player::setTaxCancelledThisTurn(bool value) {
    taxCancelledThisTurn = value;
}

bool Player::isBribeCancelledForCurrentTurn() const {
    return bribeCancelledThisTurn;
}

void Player::setBribeCancelledThisTurn(bool value) {
    bribeCancelledThisTurn = value;
}

void Player::reset_turn_flags() {
    bonus_applied = false;
    taxCancelledThisTurn = false;
    bribeCancelledThisTurn = false;
}

void Player::start_turn_bonus() {
    if (!bonus_applied && get_role() == "Merchant" && coins() >= 3) {
        ++num_of_coins;
        bonus_applied = true;
    }
}

void Player::enforce_coup_requirement() const {
    if (coins() >= 10) {
        throw runtime_error("You must perform coup when you have 10 or more coins");
    }
}

void Player::prepare_for_turn() {
    start_turn_bonus();
    enforce_coup_requirement();
}

void Player::gather() {
    prepare_for_turn();

    if (sanctioned_until_next_turn) {
        throw runtime_error("You are sanctioned and cannot perform gather this turn");
    }

    ++num_of_coins; 
    reset_sanctions();
    clear_last_action();
    last_action = ActionType::Gather;
    game.next_turn();
}

void Player::tax() {
    prepare_for_turn();

    if (sanctioned_until_next_turn) {
        throw runtime_error("You are sanctioned and cannot perform tax this turn");
    }

    num_of_coins += 2;
    reset_sanctions();
    awaiting_block = true;
    last_action = ActionType::Tax;
    game.next_turn();
}

void Player::bribe() {
    prepare_for_turn();

    if (num_of_coins < 4) {
        throw runtime_error("Not enough coins to bribe");
    }

    num_of_coins -= 4;
    awaiting_block = true;
    last_action = ActionType::Bribe;
}

void Player::arrest(Player& target) {
    prepare_for_turn();

    if (!can_arrest) {
        throw std::runtime_error("You are blocked from arresting this turn");
    }

    if (!target.alive()) {
        throw runtime_error("You cannot arrest an eliminated player");
    }

    if (target.num_of_coins == 0) {
        throw runtime_error("Target has no coins to steal");
    }

    if (target.get_role() == "Merchant") {
        if (target.coins() < 2) {
            throw runtime_error("Merchant does not have enough coins to be arrested");
        }
        target.removeCoins(2);
    } else {
        target.removeCoins(1);
        ++num_of_coins;

        if (target.get_role() == "General") {
            target.addCoins(1);
        }
    }

    if (target.get_role() == "General") {
        target.addCoins(1);
    }

    reset_sanctions();
    clear_last_action();
    last_action = ActionType::Arrest;
    game.next_turn();
}

void Player::sanction(Player& target) {
    prepare_for_turn();

    if (num_of_coins < 3) {
        throw runtime_error("You don't have enough money to perform sanction");
    }

    if (!target.alive()) {
        throw runtime_error("You cannot sanction an eliminated player");
    }

    num_of_coins -= 3;
    target.receive_sanction();

    if (target.get_role() == "Judge") {
        removeCoins(1); 
    }
    
    reset_sanctions();
    clear_last_action();
    last_action = ActionType::Sanction;
    game.next_turn();
}

void Player::coup(Player& target) {
    prepare_for_turn();

    if (num_of_coins < 7) {
        throw runtime_error("You don't have enough money to perform coup");
    }

    if (!target.alive()) {
        throw runtime_error("You cannot sanction an eliminated player");
    }

    num_of_coins -= 7;
    game.apply_coup(target);
    reset_sanctions();
    awaiting_block = false;
    last_action = ActionType::Coup;
    game.next_turn();
}

void Player::invest() {
    throw runtime_error("This role cannot perform invest");
}

int Player::coins() const {
    return num_of_coins;
}

const string& Player::get_name() const {
    return name;
}

void Player::rename(const std::string& newName) {
    name = newName;
}

bool Player::alive() const {
    return is_alive;
}

void Player::eliminate() {
    is_alive = false;
}

void Player::undo_elimination() {
    is_alive = true;
}

void Player::reset_sanctions() {
    sanctioned_until_next_turn = false;
    can_arrest = true;
}

void Player::block_arrest() {
    can_arrest = false;
}

void Player::addCoins(int amount) {
    num_of_coins += amount;
}

void Player::removeCoins(int amount) {
    if (num_of_coins < amount) {
        throw runtime_error("Not enough coins to remove");
    }
    num_of_coins -= amount;
}

ActionType Player::get_last_action() const {
    return last_action;
}

bool Player::is_awaiting_block() const {
    return awaiting_block;
}

void Player::clear_last_action() {
    awaiting_block = false;
    last_action = ActionType::None;
}

void Player::receive_sanction() {
    sanctioned_until_next_turn = true;
    if (get_role() == "Baron") {
        addCoins(1);
    }
}