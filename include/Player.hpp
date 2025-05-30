#pragma once

#include <string>
#include "Game.hpp"

namespace coup {

enum class ActionType {
    None,
    Gather,
    Tax,
    Bribe,
    Arrest,
    Sanction,
    Coup,
    Invest,
    Undo,
    Block_Arrest,
    Block_Coup
};

class Player {
protected:
    std::string name;
    Game& game;
    int num_of_coins = 0;
    bool is_alive = true;
    bool sanctioned_until_next_turn = false;
    bool can_arrest = true;
    bool awaiting_block = false;
    ActionType last_action = ActionType::None;

    bool bonus_applied = false;
    bool taxCancelledThisTurn = false;
    bool bribeCancelledThisTurn = false;

public:
    Player(Game& game, const std::string& name);

    virtual void gather();
    virtual void tax();
    virtual void bribe();
    virtual void arrest(Player& target);
    virtual void sanction(Player& target);
    virtual void coup(Player& target);

    virtual void invest();

    int coins() const;
    const std::string& get_name() const;
    void rename(const std::string& newName);
    bool alive() const;

    void eliminate();
    void undo_elimination();
    void reset_sanctions();
    void block_arrest();
    void addCoins(int amount);
    void removeCoins(int amount);
    void receive_sanction();

    ActionType get_last_action() const;
    bool is_awaiting_block() const;
    void clear_last_action();

    void start_turn_bonus();
    void reset_turn_flags();
    void enforce_coup_requirement() const;
    void prepare_for_turn();

    bool isTaxCancelledForCurrentTurn() const;
    void setTaxCancelledThisTurn(bool value);

    bool isBribeCancelledForCurrentTurn() const;
    void setBribeCancelledThisTurn(bool value);

    virtual std::string get_role() const = 0;

    virtual ~Player() = default;
};

}  