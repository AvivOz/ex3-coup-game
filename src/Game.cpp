// author: avivoz4@gmail.com

#include "Game.hpp"
#include "Player.hpp"

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

namespace coup {

    std::vector<std::string> Game::players() const {
        std::vector<std::string> active_players;
        for (const Player* player : players_list) {
            if (player->alive()) {
                active_players.push_back(player->get_name());
            }
        }
        return active_players;
    }

    std::string Game::turn() const {

        if (players_list.empty()) {
            std::cerr << "[Game::turn] Error: players_list is empty!" << std::endl;
            return "UNKNOWN";
        }
        if (current_player_index >= players_list.size()) {
            std::cerr << "[Game::turn] Error: current_player_index is out of bounds!" << std::endl;
            return "UNKNOWN";
        }
        if (players_list[current_player_index] == nullptr) {
            std::cerr << "[Game::turn] Error: current player is nullptr!" << std::endl;
            return "UNKNOWN";
        }

        std::string name = players_list[current_player_index]->get_name();
        std::cout << "[Game::turn] current player name: " << name << std::endl;
        return name;
    }

    std::string Game::winner() const {
        std::vector<Player*> alive_players;
        for (Player* player : players_list) {
            if (player->alive()) {
                alive_players.push_back(player);
            }
        }

        if (alive_players.size() == 1) {
            return alive_players[0]->get_name();
        }

        throw std::runtime_error("The game is still ongoing - no winner yet");
    }

    void Game::add_player(Player* player) {
        if (players_list.size() >= 6) {
            throw std::runtime_error("Maximum 6 players allowed");
        }
        players_list.push_back(player);
    }

    void Game::next_turn() {
        if (players_list.empty()) return;

        size_t original_index = current_player_index;

        do {
            current_player_index = (current_player_index + 1) % players_list.size();
        } while (!players_list[current_player_index]->alive() && current_player_index != original_index);
    }

    void Game::eliminate_player(Player* player) {
        player->eliminate();
    }

    void Game::apply_coup(Player& target) {
        target.eliminate();
        eliminate_player(&target);
    }

    void Game::reset() {
        for (Player* player : players_list) {
            delete player;
        }
        players_list.clear();
        current_player_index = 0;
    }

    std::vector<Player*>& Game::get_players_list() {
        return players_list;
    }

    const std::vector<Player*>& Game::get_players_list() const {
        return players_list;
    }

} 