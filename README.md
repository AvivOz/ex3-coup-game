# Coup Game – CPP_EX3  
**Author:** Aviv Oz  
**Repository:** https://github.com/AvivOz/ex3-coup-game  

---

## 📑 Table of Contents  
- [Project Overview](#project-overview)  
- [Game Description](#game-description)  
- [Project Structure](#project-structure)  
- [Features Implemented](#features-implemented)  
- [Requirements](#requirements)  
- [Installation & Setup](#installation--setup)  
- [How to Run](#how-to-run)  
- [Game Rules](#game-rules)  
- [Character Roles](#character-roles)  
- [Technical Implementation](#technical-implementation)  
- [Testing](#testing)  
- [Memory Management](#memory-management)  

---

## 🧩 Project Overview  
This project implements the Coup card game in C++ as part of Assignment 3 in System Programming 2. The game supports 2–6 players with unique roles and a full graphical interface built using SFML.

---

## 🎲 Game Description  
Players:
- Are randomly assigned a unique role at the beginning.
- Take turns performing actions to gain coins, eliminate others, or block opponents.
- Use role-specific abilities and strategic plays.
- The objective is to be the **last surviving player**.

---

## 📁 Project Structure  

ex3-coup-game/
├── Makefile
├── README.md
│
├── main.cpp
├── playerFactory.cpp
│
├── include/
│ ├── Game.hpp
│ └── Roles/
│ ├── Player.hpp
│ ├── Governor.hpp
│ ├── Judge.hpp
│ ├── General.hpp
│ ├── Baron.hpp
│ ├── Merchant.hpp
│ └── Spy.hpp
│
├── src/
│ ├── Game.cpp
│ └── Roles/
│ ├── Player.cpp
│ ├── Governor.cpp
│ ├── Judge.cpp
│ ├── General.cpp
│ ├── Baron.cpp
│ ├── Merchant.cpp
│ └── Spy.cpp
│
├── Tests/
│ └── demo_test.cpp
│
└── GUI/
├── Button.cpp/.hpp
├── GUIManager.cpp/.hpp
├── WelcomeScreen.cpp/.hpp
├── PlayerInputScreen.cpp/.hpp
├── RoleRevealScreen.cpp/.hpp
├── GameTurnScreen.cpp/.hpp
└── main_gui.cpp

yaml
Copy
Edit

---

## ✅ Features Implemented  
- Turn-based gameplay system  
- Dynamic player creation with random role assignment  
- Coin-based economy (gather, tax, bribe, etc.)  
- Six unique roles with custom actions and blocks  
- Player elimination & win detection  
- Complete GUI with SFML (no default players)  
- Supports 2–6 players  
- Input validation and game rule enforcement  
- Role reveal screen with random shuffle  

---

## 🛠 Requirements  
- g++ with C++17 support  
- Linux (tested on Ubuntu)  
- Make  
- SFML (`libsfml-dev`)  
- Valgrind (for memory checks – optional)

---

## 🔧 Installation & Setup  

Clone the repository:
```bash
git clone https://github.com/AvivOz/ex3-coup-game.git
cd ex3-coup-game
Check:

bash
Copy
Edit
g++ --version
make --version
Install SFML (for GUI mode):

bash
Copy
Edit
sudo apt update
sudo apt install libsfml-dev
For Windows/macOS – refer to https://www.sfml-dev.org/download.php

▶️ How to Run
Build the game:
bash
Copy
Edit
make Main
Run tests:
bash
Copy
Edit
make test
Run GUI:
bash
Copy
Edit
make gui_run
Memory check:
bash
Copy
Edit
make valgrind
📜 Game Rules
Gather: +1 coin

Tax: +2 coins (Governor: +3)

Bribe: Pay 4 coins, get an extra turn

Arrest: Take 1 coin from another player

Sanction: Block economic actions of a player until their next turn

Coup: Pay 7 coins to eliminate a player (mandatory at 10+)

Win Condition: Only one player remains alive

🧑‍💼 Character Roles
Role	Ability	Block Capability
Governor	Tax: +3 coins	Can block tax actions
Judge	Immune to bribe	Can block bribes
General	Can block coups	Gets bonus when arresting
Baron	Gains bonus from sanctions	Can invest coins
Merchant	Gets bonus if holding 3+ coins	Gains extra on arrest
Spy	Can view opponent coins	Can block arrests

🧠 Technical Implementation
Object-Oriented Design:

Each role inherits from Player

Actions and blocks are overridden per role

Factory Pattern: Used to create players with assigned roles

SFML GUI: Modular design using multiple screen classes

Turn Management: Eliminated players are skipped, game ends when one survives

Action Handling: Validity checks and blocking logic enforced

🧪 Testing
30+ test cases in demo_test.cpp

Covers:

Basic actions

Role-specific behavior

Turn management

Invalid action prevention

Game end condition

Run with:

bash
Copy
Edit
make test
make valgrind
🧼 Memory Management
Verified with Valgrind (no leaks)

Proper use of destructors

No use of raw pointers that require manual deletion

Exception-safe design