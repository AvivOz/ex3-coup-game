#include "playerFactory.hpp"
#include <vector>
#include <string>
#include <random>

namespace coup {

    Player* playerFactory(Game& game, const std::string& name) {
        static std::vector<std::string> roles = {"Governor", "Spy", "Baron", "General", "Judge", "Merchant"};
        static std::mt19937 rng(std::random_device{}());
        static std::uniform_int_distribution<> dist(0, roles.size() - 1);

        std::string role = roles[dist(rng)];
        if (role == "Governor") return new Governor(game, name);
        if (role == "Spy") return new Spy(game, name);
        if (role == "Baron") return new Baron(game, name);
        if (role == "General") return new General(game, name);
        if (role == "Judge") return new Judge(game, name);
        return new Merchant(game, name);
    }
}