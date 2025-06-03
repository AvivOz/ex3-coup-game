#pragma once
#include <vector>
#include <string>

namespace coup {
    class Player;  

    class Game {
    private:
        std::vector<Player*> players;
        size_t current_player_index;
        bool game_started;
        bool is_alive(size_t index) const; 

    public:
        Game();
        std::vector<std::string> players_list() const;
        std::string turn() const;
        std::string winner() const;
        void next_turn();
        void add_player(Player* player);
        void apply_coup(Player& target);
        bool has_started() const;
        size_t num_of_players() const;
        size_t find_player_index(Player* player) const;
        
        Player* getCurrentPlayer() const;
    };
}