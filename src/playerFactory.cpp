#include "playerFactory.hpp"
#include <stdexcept>

namespace coup {
    Player* PlayerFactory::createPlayer(const std::string& role, Game& game, const std::string& name) {
        if (role == "Governor") {
            return new Governor(game, name);
        }
        else if (role == "Judge") {
            return new Judge(game, name);
        }
        else if (role == "General") {
            return new General(game, name);
        }
        else if (role == "Baron") {
            return new Baron(game, name);
        }
        else if (role == "Merchant") {
            return new Merchant(game, name);
        }
        else if (role == "Spy") {
            return new Spy(game, name);
        }
        throw std::runtime_error("Invalid player role: " + role);
    }
}