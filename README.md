🃏 Coup Game – CPP_EX3
Author: Aviv Oz
Repository: https://github.com/AvivOz/ex3-coup-game

📑 Table of Contents
Project Overview

Game Description

Project Structure

Features Implemented

Requirements

Installation & Setup

How to Run

Game Rules

Character Roles

Technical Implementation

Testing

Memory Management

🧩 Project Overview
This project implements the Coup card game in C++ as part of Assignment 3 in System Programming 2.
It includes both a command-line version (main.cpp) and a full graphical version using SFML.

🎲 Game Description
Players:

Are randomly assigned a unique role at the beginning.

Take turns performing actions to gain coins, eliminate others, or block opponents.

Use role-specific abilities and strategic plays.

The objective is to be the last surviving player.

📁 Project Structure
css
Copy
Edit
ex3-coup-game/
├── Makefile
├── README.md
│
├── main.cpp
│
├── include/
│   ├── Game.hpp
│   ├── PlayerFactory.hpp
│   └── Roles/
│       ├── Player.hpp
│       ├── Governor.hpp
│       ├── Judge.hpp
│       ├── General.hpp
│       ├── Baron.hpp
│       ├── Merchant.hpp
│       └── Spy.hpp
│
│   └── GUI/
│       ├── Button.hpp
│       ├── GUIManager.hpp
│       ├── WelcomeScreen.hpp
│       ├── PlayerInputScreen.hpp
│       ├── RoleRevealScreen.hpp
│       └── GameTurnScreen.hpp
│
├── src/
│   ├── Game.cpp
│   ├── PlayerFactory.cpp
│   └── Roles/
│       ├── Player.cpp
│       ├── Governor.cpp
│       ├── Judge.cpp
│       ├── General.cpp
│       ├── Baron.cpp
│       ├── Merchant.cpp
│       └── Spy.cpp
│
│   └── GUI/
│       ├── Button.cpp
│       ├── GUIManager.cpp
│       ├── WelcomeScreen.cpp
│       ├── PlayerInputScreen.cpp
│       ├── RoleRevealScreen.cpp
│       └── GameTurnScreen.cpp
│
├── GUI/
│   └── main_gui.cpp
│
├── Tests/
│   └── demo_test.cpp
✅ Features Implemented
Turn-based game engine

Command-line game via main.cpp

Full graphical game with SFML

Role system using inheritance and polymorphism

Random role assignment via factory pattern

Coin-based actions: gather, tax, bribe, arrest, sanction, coup

Special role abilities and block mechanics

Game win detection, elimination, and validation

Clean modular structure with GUI/logic separation

🛠 Requirements
g++ with C++17 support

Linux (tested on Ubuntu)

Make

SFML (libsfml-dev)

Valgrind (optional)

🔧 Installation & Setup
Clone the repository:

bash
Copy
Edit
git clone https://github.com/AvivOz/ex3-coup-game.git
cd ex3-coup-game
Check compilers:

css
Copy
Edit
g++ --version
make --version
Install SFML (for GUI):

sql
Copy
Edit
sudo apt update
sudo apt install libsfml-dev
For Windows/macOS – refer to:
https://www.sfml-dev.org/download.php

▶️ How to Run
Run command-line version

css
Copy
Edit
make Main
./main
Run GUI version

go
Copy
Edit
make gui_run
Run tests

bash
Copy
Edit
make test
Check for memory leaks

go
Copy
Edit
make valgrind
📜 Game Rules
Action	Description
Gather	+1 coin
Tax	+2 coins (Governor: +3)
Bribe	Pay 4 coins to get an extra turn
Arrest	Take 1 coin from another player
Sanction	Block economic actions of a player until next turn
Coup	Pay 7 coins to eliminate a player (mandatory at 10+)
Win	Be the last surviving player

🧑‍💼 Character Roles
Role	Special Ability	Block Capability
Governor	Tax for +3 coins	Can block others' tax
Judge	Immune to bribes	Can block bribes
General	Can block coups	Bonus on arrest
Baron	Gains bonus from sanctions	Can invest coins
Merchant	Bonus if holding ≥3 coins	Bonus when arrested
Spy	Peek opponent's coins	Can block arrests

🧠 Technical Implementation
Object-Oriented Design
Each role inherits from Player and overrides its actions.

Factory Pattern
PlayerFactory creates role instances dynamically.

SFML GUI
Modular screen structure: Welcome → Input → Reveal → Game Turn.

Turn Management
Eliminated players are skipped, coup is enforced if 10+ coins, and rule validation is strict.

🧪 Testing
Test file: Tests/demo_test.cpp
Includes 30+ test cases for:

Core mechanics

Role behavior

Turn rotation

Input validation

Win condition logic

Run tests:

go
Copy
Edit
make test
make valgrind
🧼 Memory Management
Verified with Valgrind – no leaks

RAII and destructors used correctly

No raw pointer misuse

Exception-safe handling throughout the game