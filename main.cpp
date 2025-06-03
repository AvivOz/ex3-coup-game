#include <iostream>
#include <string>
#include <vector>
#include "Game.hpp"
#include "Player.hpp"
#include "Baron.hpp"
#include "Governor.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Spy.hpp"
#include "General.hpp"

using namespace std;
using namespace coup;

int main() {
    try {
        cout << "\n=== Welcome to Coup Game Demo ===\n" << endl;

        // Initialize game
        Game game{};
        
        // Create players
        Governor p1{game, "Moshe"};
        General p2{game, "Yossi"};
        Judge p3{game, "Sarah"};
        Baron p4{game, "David"};
        Merchant p5{game, "Yael"};

        cout << "Initial game state:" << endl;
        cout << "Current turn: " << game.turn() << endl;
        cout << "Players in game: ";
        for (const string& player : game.players_list()) {
            cout << player << " ";
        }
        cout << "\n\n";

        cout << "=== Game Actions Demonstration ===\n" << endl;

        // Demonstrate gather (income)
        p1.gather();
        cout << "Moshe (Governor) gathers coins. Coins: " << p1.coins() << endl;

        p2.gather();
        cout << "Yossi (General) gathers coins. Coins: " << p2.coins() << endl;

        // Demonstrate tax (Governor special)
        p3.gather();
        cout << "Sarah (Judge) gathers coins. Coins: " << p3.coins() << endl;

        p4.gather();
        cout << "David (Baron) gathers coins. Coins: " << p4.coins() << endl;

        p5.gather();
        cout << "Yael (Merchant) gathers coins. Coins: " << p5.coins() << endl;

        // Show next turns
        p1.tax();
        cout << "Moshe (Governor) collects tax. Coins: " << p1.coins() << endl;

        p2.gather();
        cout << "Yossi (General) gathers coins. Coins: " << p2.coins() << endl;

        // Demonstrate coup
        for(int i = 0; i < 4; i++) {
            p3.gather();
            p4.gather();
            p5.gather();
            p1.gather();
            p2.gather();
        }

        cout << "\nMoshe attempts coup on Sarah..." << endl;
        p1.coup(p3);
        cout << "Coup successful! Sarah is out of the game." << endl;

        cout << "\nRemaining players: ";
        for (const string& player : game.players_list()) {
            cout << player << " ";
        }
        cout << "\n" << endl;

        cout << "=== Game Demo Completed ===\n" << endl;

    } catch (const exception& e) {
        cout << "Error occurred: " << e.what() << endl;
    }

    return 0;
}