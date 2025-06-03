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
    Cancel_Tax,
    Cancel_Bribe,
    Block_Arrest,
    Block_Coup
};

class Player {
protected:
    std::string name;
    Game& game;
    int num_of_coins;
    bool is_alive;
    bool sanctioned_until_next_turn;
    bool can_arrest;
    bool awaiting_block;

protected:
    Player* last_arrested_target;
    static Player* global_last_arrested_player;
    ActionType last_action;

    bool bonus_applied;
    bool taxCancelledThisTurn;
    bool bribeCancelledThisTurn;

public:
    Player(Game& game, const std::string& name);
    virtual ~Player() = default;  // Pure virtual destructor

    // Pure virtual functions
    virtual std::string get_role() const = 0;
    
    // Virtual functions with default implementations
    virtual void gather();
    virtual void tax();
    virtual void bribe();
    virtual void arrest(Player& target);
    virtual void sanction(Player& target);
    virtual void coup(Player& target);
    virtual void invest();
    virtual void tax_cancelled();
    virtual void receive_arrest();
    virtual void receive_sanction();
    virtual void bribe_cancelled();


    // Non-virtual public functions
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
    void reset_arrest_target();
    bool must_coup() const;

    ActionType get_last_action() const;
    bool is_awaiting_block() const;
    void can_perform_arrest() const; 
    void clear_last_action();
    void save_last_action(ActionType action);


    void start_turn_bonus();
    void reset_turn_flags();
    void enforce_coup_requirement() const;
    void prepare_for_turn();

    bool isTaxCancelledForCurrentTurn() const;
    void setTaxCancelledThisTurn(bool value);

    bool isBribeCancelledForCurrentTurn() const;
    void setBribeCancelledThisTurn(bool value);
};

}  