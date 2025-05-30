#pragma once

#include <string>
#include <vector>
#include <stdexcept>

namespace coup {

    class Player;

    class Game {

    private:
        std::vector<Player*> players_list;
        size_t current_player_index = 0;

    public:
        Game() : current_player_index(0) {}

        std::vector<std::string> players() const;
        std::vector<Player*>& get_players_list();
        const std::vector<Player*>& get_players_list() const;
        std::string turn() const;
        std::string winner() const;

        void add_player(Player* player);
        void next_turn();
        void eliminate_player(Player* player);
        void apply_coup(Player& target);

        void reset();
    };

}
