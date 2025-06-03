// author: avivoz4@gmail.com

#include "Player.hpp"
#include <stdexcept>
#include <iostream>

namespace coup {

Player* Player::global_last_arrested_player = nullptr;

Player::Player(Game& game, const std::string& name)
    : name(name)
    , game(game)
    , num_of_coins(0)
    , is_alive(true)
    , sanctioned_until_next_turn(false)
    , can_arrest(true)
    , awaiting_block(false)
    , last_arrested_target(nullptr)
    , last_action(ActionType::None)
    , bonus_applied(false)
    , taxCancelledThisTurn(false)
    , bribeCancelledThisTurn(false) {
}

void Player::gather() {
    prepare_for_turn();

    if (sanctioned_until_next_turn) {
        throw std::runtime_error("Error: You are sanctioned and cannot perform gather this turn");
    }

    ++num_of_coins; 
    reset_sanctions();
    clear_last_action();
    last_action = ActionType::Gather;
    game.next_turn();
}

void Player::tax() {

    if (sanctioned_until_next_turn) {
        throw std::runtime_error("Error: You are sanctioned and cannot perform tax this turn");
    }

    num_of_coins += 2;
    reset_sanctions();
    awaiting_block = true;
    last_action = ActionType::Tax;
    game.next_turn();
}

void Player::bribe() {
    prepare_for_turn();

    if (sanctioned_until_next_turn) {
        throw std::runtime_error("You are sanctioned and cannot bribe this turn");
    }

    if (num_of_coins < 4) {
        throw std::runtime_error("Not enough coins to bribe");
    }

    num_of_coins -= 4;
    awaiting_block = true;
    last_action = ActionType::Bribe;
}

void Player::arrest(Player& target) {
    enforce_coup_requirement();
    can_perform_arrest();

    if (&target == global_last_arrested_player) {
        throw std::runtime_error("Error: This player was already arrested in the last turn");
    }

    if (!target.alive()) {
        throw std::runtime_error("Error: Cannot arrest a dead player");
    }

    try {
        target.receive_arrest();
        if (target.get_role() != "Merchant") {
            this->addCoins(1);
        }
        this->last_action = ActionType::Arrest;
        global_last_arrested_player = &target;
        reset_sanctions();
        game.next_turn();
    } catch (const std::exception& e) {
        throw;
    }
}

void Player::sanction(Player& target) {
    prepare_for_turn();

    if (num_of_coins < 3) {
        throw std::runtime_error("You don't have enough money to perform sanction");
    }

    if (!target.alive()) {
        throw std::runtime_error("You cannot sanction an eliminated player");
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
    if (!alive()) {
        throw std::runtime_error("Dead player cannot perform actions");
    }

    if (num_of_coins < 7) {
        throw std::runtime_error("You don't have enough money to perform coup (need 7 coins)");
    }

    if (!target.alive()) {
        throw std::runtime_error("Cannot coup an eliminated player");
    }

    if (&target == this) {
        throw std::runtime_error("Cannot coup yourself");
    }

    num_of_coins -= 7;
    last_action = ActionType::Coup;
    awaiting_block = true;
}

void Player::receive_arrest() {
    if (coins() > 0) {
        removeCoins(1);
    } else {
        throw std::runtime_error("Target player has no coins");
    }
}

void Player::invest() {
    throw std::runtime_error("This role cannot perform invest");
}

int Player::coins() const {
    return num_of_coins;
}

const std::string& Player::get_name() const {
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
}

void Player::block_arrest() {
    can_arrest = false;
}

void Player::can_perform_arrest() const {
    if (!can_arrest) {
        throw std::runtime_error("Error: You are blocked from performing arrest this turn");
    }
}

void Player::reset_arrest_target() {
    last_arrested_target = nullptr;
}

bool Player::must_coup() const {
    return coins() >= 10;
}

void Player::addCoins(int amount) {
    num_of_coins += amount;
}

void Player::removeCoins(int amount) {
    if (amount > num_of_coins) {
        throw std::runtime_error("Cannot remove more coins than player has");
    }
    num_of_coins -= amount;
}

void Player::tax_cancelled() {
    if (last_action == ActionType::Tax) {
        if (get_role() == "Governor") {
            removeCoins(3);  
        } else {
            removeCoins(2);  
        }
    } else if (last_action == ActionType::Gather) {
        removeCoins(1);  
    }
    
    taxCancelledThisTurn = true;
    clear_last_action();
}

void Player::save_last_action(ActionType action) {
    last_action = action;
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

void Player::bribe_cancelled() {
    if (last_action == ActionType::Bribe) {
        bribeCancelledThisTurn = true;
    }
}

void Player::start_turn_bonus() {
    if (!bonus_applied && get_role() == "Merchant" && coins() >= 3) {
        std::cout << "Merchant bonus: Adding 1 coin at start of turn (current coins: " 
                  << coins() << ")" << std::endl;
        ++num_of_coins;
        bonus_applied = true;
    }
}

void Player::reset_turn_flags() {
    bonus_applied = false;
    taxCancelledThisTurn = false;
    bribeCancelledThisTurn = false;
}

void Player::enforce_coup_requirement() const {
    if (coins() >= 10 && last_action != ActionType::Coup) {
        throw std::runtime_error("You must perform coup when you have 10 or more coins");
    }
}

void Player::prepare_for_turn() {
    reset_turn_flags();
    
    if (this == global_last_arrested_player) {
        global_last_arrested_player = nullptr;
    }
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

}