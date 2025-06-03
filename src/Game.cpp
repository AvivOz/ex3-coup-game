#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace coup {

Game::Game() : current_player_index(0), game_started(false) {}

std::vector<std::string> Game::players_list() const {
    std::vector<std::string> names;
    for (const auto& player : players) {
        if (player->alive()) {
            names.push_back(player->get_name());
        }
    }
    return names;
}

std::string Game::turn() const {
    if (players.empty()) {
        throw std::runtime_error("No players in game");
    }
    return players[current_player_index]->get_name();
}

std::string Game::winner() const {
    if (!game_started) {
        throw std::runtime_error("Game hasn't started yet");
    }

    std::vector<Player*> alive_players;
    for (const auto& player : players) {
        if (player->alive()) {
            alive_players.push_back(player);
        }
    }

    if (alive_players.size() != 1) {
        throw std::runtime_error("Game is still in progress");
    }

    return alive_players[0]->get_name();
}

void Game::next_turn() {
    if (players.size() < 2) {
        throw std::runtime_error("Not enough players to start the game");
    }

    if (!game_started) {
        game_started = true;
        current_player_index = 0;
        players[current_player_index]->start_turn_bonus();
        return;
    }

    ActionType last_action = players[current_player_index]->get_last_action();

    size_t start_index = current_player_index;
    current_player_index = (current_player_index + 1) % players.size();

    while (!players[current_player_index]->alive()) {
        current_player_index = (current_player_index + 1) % players.size();
        
        if (current_player_index == start_index) {
            if (players[start_index]->alive()) {
                current_player_index = start_index;
                players[current_player_index]->start_turn_bonus();
                return;
            }
            throw std::runtime_error("No alive players to move to");
        }
    }
    
    players[current_player_index]->save_last_action(last_action);
    players[current_player_index]->start_turn_bonus();
}

void Game::add_player(Player* player) {
    if (player == nullptr) {
        throw std::runtime_error("Cannot add null player");
    }
    if (players.size() >= 6) {
        throw std::runtime_error("Maximum number of players reached");
    }
    std::cout << "Adding player: " << player->get_name() << " (" << player->get_role() << ")" << std::endl;
    players.push_back(player);
}

void Game::apply_coup(Player& target) {
    if (!target.alive()) {
        throw std::runtime_error("Cannot coup an eliminated player");
    }

    size_t attacker_index = current_player_index;

    target.eliminate();
    
    int alive_count = 0;
    Player* last_alive = nullptr;
    
    for (const auto& player : players) {
        if (player->alive()) {
            alive_count++;
            last_alive = player;
        }
    }
    
    if (alive_count <= 1 && last_alive != nullptr) {
        game_started = false;
        current_player_index = find_player_index(last_alive);
    }

    // אם המשחק ממשיך, מעבירים את התור לשחקן הבא החי
    current_player_index = attacker_index;
    next_turn();
}

bool Game::has_started() const {
    return game_started;
}

size_t Game::num_of_players() const {
    return players.size();
}

size_t Game::find_player_index(Player* player) const {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i] == player) {
            return i;
        }
    }
    return 0;
}

Player* Game::getCurrentPlayer() const {
    if (players.empty()) {
        throw std::runtime_error("No players in game");
    }
    return players[current_player_index];
}

bool Game::is_alive(size_t index) const {
    if (index >= players.size()) {
        return false;
    }
    return players[index]->alive();
}

} 