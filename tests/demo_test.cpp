/**
 * @file test_coup.cpp
 * Basic tests for Coup game
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.hpp"
#include "Player.hpp"
#include "Judge.hpp"
#include "Governor.hpp"
#include "General.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"
#include "Spy.hpp"

using namespace coup;
using namespace std;

TEST_CASE("1. Basic Game Setup") {
    Game game;
    
    SUBCASE("1.1 Initial game state") {
        CHECK(game.players_list().empty());
        CHECK(game.num_of_players() == 0);
        CHECK_THROWS(game.turn()); // משחק ללא שחקנים
    }

    SUBCASE("1.2 Adding single player") {
        Governor p1(game, "P1");
        vector<string> players = game.players_list();
        CHECK(players.size() == 1);
        CHECK(players[0] == "P1");
        CHECK(game.turn() == "P1");
    }

    SUBCASE("1.3 Adding multiple players") {
        Governor p1(game, "P1");
        Judge p2(game, "P2");
        Spy p3(game, "P3");
        
        vector<string> players = game.players_list();
        CHECK(players.size() == 3);
        CHECK(players[0] == "P1");
        CHECK(players[1] == "P2");
        CHECK(players[2] == "P3");
    }
}

TEST_CASE("2. Player Basic Properties") {
    Game game;
    Governor p1(game, "P1");
    Judge p2(game, "P2"); 
    
    SUBCASE("2.1 Initial player state") {
        CHECK(p1.coins() == 0);
        CHECK(p1.alive());
        CHECK(p1.get_name() == "P1");
        CHECK(p1.get_role() == "Governor");
    }

    SUBCASE("2.2 Basic coin operations") {
        CHECK(game.turn() == "P1"); // וידוא שזה התור של p1
        p1.gather();
        CHECK(p1.coins() == 1);
    }
}

TEST_CASE("3. Turn Management") {
    Game game;
    Governor p1(game, "P1");
    Judge p2(game, "P2");
    
    SUBCASE("3.1 Basic turn sequence") {
        CHECK(game.turn() == "P1");
        p1.gather();
        game.next_turn();
        CHECK(game.turn() == "P2");
    }

    SUBCASE("3.2 Valid actions in turn") {
        CHECK(game.turn() == "P1");
        CHECK_NOTHROW(p1.gather());
        game.next_turn();
        CHECK(game.turn() == "P2");
        CHECK_NOTHROW(p2.gather());
    }
}

TEST_CASE("4. Basic Actions") {
    Game game;
    Governor p1(game, "P1");
    Judge p2(game, "P2");

    SUBCASE("4.1 Gather action") {
        CHECK(game.turn() == "P1");
        CHECK(p1.coins() == 0);
        p1.gather();
        CHECK(p1.coins() == 1);
    }

    SUBCASE("4.2 Tax action") {
        CHECK(game.turn() == "P1");
        p1.tax();
        CHECK(p1.coins() > 0);
    }

    SUBCASE("4.3 Basic arrest sequence") {
        // תור ראשון - p1 אוסף מטבע
        CHECK(game.turn() == "P1");
        p1.gather();
        game.next_turn();
        
        // תור p2 - אוסף מטבע
        CHECK(game.turn() == "P2");
        p2.gather();
        
        // חזרה ל-p1 לביצוע המעצר
        game.next_turn();
        p1.arrest(p2);
    }
}

TEST_CASE("5. Player Interactions") {
    Game game;
    Governor p1(game, "P1");
    Judge p2(game, "P2");
    
    SUBCASE("5.1 Block action sequence") {
        // Setup - giving coins to both players
        CHECK(game.turn() == "P1");
        p1.gather();
        game.next_turn();
        
        CHECK(game.turn() == "P2");
        p2.gather();
        
        // Arrest action by p1
        game.next_turn();
        p1.arrest(p2);
        
        // Block by p2
        game.next_turn();
        CHECK(game.turn() == "P2");
        CHECK_NOTHROW(p2.block_arrest());
    }

    SUBCASE("5.2 Turn based actions") {
        // p1's turn
        CHECK(game.turn() == "P1");
        CHECK_NOTHROW(p1.gather());
        game.next_turn();
        
        // p2's turn
        CHECK(game.turn() == "P2");
        CHECK_NOTHROW(p2.gather());
    }
}