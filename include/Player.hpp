// author: avivoz4@gmail.com

#pragma once

#include <string>
#include "Game.hpp"

namespace coup {

/**
 * @enum ActionType
 * @brief Enum representing all possible player actions, including special and block actions.
 */
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

/**
 * @class Player
 * @brief Abstract base class for all player roles in the game.
 * 
 * Manages player state, action logic, coins, elimination, blocking, and turn flags.
 */
class Player {
protected:
    std::string name;                          ///< Player name
    Game& game;                                ///< Reference to the game instance
    int num_of_coins = 0;                      ///< Number of coins the player has
    bool is_alive = true;                      ///< Whether the player is alive
    bool sanctioned_until_next_turn = false;   ///< Whether the player is currently sanctioned
    bool can_arrest = true;                    ///< Whether the player can arrest this turn
    bool awaiting_block = false;               ///< Whether the player awaits block response

    Player* last_arrested_target = nullptr;    ///< Last player this player arrested
    static Player* global_last_arrested_player;///< Globally tracked last arrested player
    ActionType last_action = ActionType::None; ///< Last action this player performed

    bool bonus_applied = false;                ///< Whether bonus has been applied this turn
    bool taxCancelledThisTurn = false;         ///< Flag if tax was canceled this turn
    bool bribeCancelledThisTurn = false;       ///< Flag if bribe was canceled this turn

public:
    /**
     * @brief Constructs a new Player object.
     * @param game Reference to the game instance
     * @param name Name of the player
     */
    Player(Game& game, const std::string& name);

    /** @brief Virtual destructor. */
    virtual ~Player() = default;

    /** @brief Returns the role name of the player. */
    virtual std::string get_role() const = 0;

    // ==== Virtual Action Methods (Override Optional) ====

    /** @brief Perform gather: gain 1 coin. */
    virtual void gather();

    /** @brief Perform tax: role-specific implementation. */
    virtual void tax();

    /** @brief Perform bribe: pay 4 coins and gain extra turn. */
    virtual void bribe();

    /**
     * @brief Arrest another player.
     * @param target The player to arrest
     */
    virtual void arrest(Player& target);

    /**
     * @brief Sanction another player, blocking economic actions until their next turn.
     * @param target The player to sanction
     */
    virtual void sanction(Player& target);

    /**
     * @brief Perform coup: eliminate another player.
     * @param target The player to eliminate
     */
    virtual void coup(Player& target);

    /** @brief Optional role-specific invest action. */
    virtual void invest();

    /** @brief Hook called when player's tax is canceled. */
    virtual void tax_cancelled();

    /** @brief Hook called when player is arrested. */
    virtual void receive_arrest();

    /** @brief Hook called when player is sanctioned. */
    virtual void receive_sanction();

    /** @brief Hook called when bribe is canceled. */
    virtual void bribe_cancelled();

    // ==== Non-virtual Utility Methods ====

    /** @brief Gets current coin count. */
    int coins() const;

    /** @brief Gets player name. */
    const std::string& get_name() const;

    /** @brief Renames the player. */
    void rename(const std::string& newName);

    /** @brief Checks if the player is alive. */
    bool alive() const;

    /** @brief Eliminates the player. */
    void eliminate();

    /** @brief Undoes elimination of the player. */
    void undo_elimination();

    /** @brief Resets sanction state. */
    void reset_sanctions();

    /** @brief Blocks arrest effects if possible. */
    void block_arrest();

    /**
     * @brief Adds coins to the player's balance.
     * @param amount Amount of coins to add
     */
    void addCoins(int amount);

    /**
     * @brief Removes coins from the player's balance.
     * @param amount Amount of coins to remove
     */
    void removeCoins(int amount);

    /** @brief Clears last arrest target pointer. */
    void reset_arrest_target();

    /** @brief Checks if player must perform a coup (10+ coins). */
    bool must_coup() const;

    /** @brief Returns the player's last performed action. */
    ActionType get_last_action() const;

    /** @brief Checks if player is currently awaiting a block. */
    bool is_awaiting_block() const;

    /** @brief Marks that the player can arrest this turn. */
    void can_perform_arrest() const;

    /** @brief Clears the saved last action. */
    void clear_last_action();

    /**
     * @brief Saves the player's last action.
     * @param action The ActionType performed
     */
    void save_last_action(ActionType action);

    /** @brief Applies bonus logic for start of turn (e.g., Merchant role). */
    void start_turn_bonus();

    /** @brief Resets turn-specific flags (bonuses, blocks, etc). */
    void reset_turn_flags();

    /** @brief Throws if player has 10+ coins and does not coup. */
    void enforce_coup_requirement() const;

    /** @brief Prepares player state at the beginning of turn. */
    void prepare_for_turn();

    /** @brief Checks if tax was canceled this turn. */
    bool isTaxCancelledForCurrentTurn() const;

    /** @brief Sets whether tax was canceled this turn. */
    void setTaxCancelledThisTurn(bool value);

    /** @brief Checks if bribe was canceled this turn. */
    bool isBribeCancelledForCurrentTurn() const;

    /** @brief Sets whether bribe was canceled this turn. */
    void setBribeCancelledThisTurn(bool value);
};

}