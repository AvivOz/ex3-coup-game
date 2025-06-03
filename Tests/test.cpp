/**
 * @file CoupTests.cpp
 * @brief Comprehensive tests for the Coup game implementation
 * @author AvivOz
 * @date 2025-05-30
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/Baron.hpp"
#include "../include/General.hpp"
#include "../include/Governor.hpp"
#include "../include/Judge.hpp"
#include "../include/Merchant.hpp"
#include "../include/Spy.hpp"

// Basic Game Setup Tests
TEST_CASE("Game Initialization Tests") {
    Game game{};

    SUBCASE("Initial Game State") {
        CHECK(game.turn() == "");  // No players yet
        CHECK_THROWS(game.winner());  // Can't get winner before game ends
        CHECK(game.players().empty());
    }

    SUBCASE("Player Creation") {
        Governor p1{game, "Player1"};
        CHECK(game.players().size() == 1);
        CHECK(game.turn() == "Player1");

        Judge p2{game, "Player2"};
        CHECK(game.players().size() == 2);

        General p3{game, "Player3"};
        Baron p4{game, "Player4"};
        Merchant p5{game, "Player5"};
        Spy p6{game, "Player6"};
        
        CHECK(game.players().size() == 6);
        CHECK_THROWS_AS(Governor p7(game, "Player7"), std::invalid_argument);
    }

    SUBCASE("Duplicate Names") {
        Governor p1{game, "Alice"};
        CHECK_THROWS_AS(Judge p2(game, "Alice"), std::invalid_argument);
    }
}

// Turn Management Tests
TEST_CASE("Turn Management") {
    Game game{};
    Governor p1{game, "P1"};
    Judge p2{game, "P2"};
    General p3{game, "P3"};

    SUBCASE("Turn Order") {
        CHECK(game.turn() == "P1");
        p1.income();
        CHECK(game.turn() == "P2");
        p2.income();
        CHECK(game.turn() == "P3");
        p3.income();
        CHECK(game.turn() == "P1");
    }

    SUBCASE("Player Elimination") {
        p1.coins() = 7;  // Set coins for coup
        p1.coup(p2);
        CHECK_FALSE(std::count(game.players().begin(), game.players().end(), "P2"));
        CHECK(game.turn() == "P3");
    }

    SUBCASE("Out of Turn Actions") {
        CHECK(game.turn() == "P1");
        CHECK_NOTHROW(p1.income());
        CHECK_THROWS_AS(p2.income(), std::runtime_error);
        CHECK_THROWS_AS(p3.income(), std::runtime_error);
    }
}