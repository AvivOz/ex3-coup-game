# Coup Game – CPP_EX3  
Author: Aviv Oz  
Repository: https://github.com/AvivOz/ex3-coup-game  

## Table of Contents  
- Project Overview  
- Game Description  
- Project Structure  
- Features Implemented  
- Requirements  
- Installation & Setup  
- How to Run  
- Game Rules  
- Character Roles  
- Technical Implementation  
- Testing  
- Memory Management  

## Project Overview  
This project implements the Coup card game in C++ as part of Assignment 3 in System Programming 2.  
It includes both a command-line version (`main.cpp`) and a full graphical version using SFML.

## Game Description  
Players:  
- Are randomly assigned a unique role at the beginning.  
- Take turns performing actions to gain coins, eliminate others, or block opponents.  
- Use role-specific abilities and strategic plays.  
- The objective is to be the last surviving player.

## Project Structure  
```
ex3-coup-game/
├── Makefile
├── README.md
├── main.cpp                        # Command-line version
│
├── include/
│   ├── Roles/
│   │   ├── Game.hpp
│   │   ├── PlayerFactory.hpp
│   │   ├── Player.hpp
│   │   ├── Governor.hpp
│   │   ├── Judge.hpp
│   │   ├── General.hpp
│   │   ├── Baron.hpp
│   │   ├── Merchant.hpp
│   │   └── Spy.hpp
│   └── GUI/
│       ├── WelcomeScreen.hpp
│       ├── PlayerSelectionScreen.hpp
│       ├── GameScreen.hpp
│       └── gui.hpp
│
├── src/
│   ├── Roles/
│   │   ├── Game.cpp
│   │   ├── PlayerFactory.cpp
│   │   ├── Player.cpp
│   │   ├── Governor.cpp
│   │   ├── Judge.cpp
│   │   ├── General.cpp
│   │   ├── Baron.cpp
│   │   ├── Merchant.cpp
│   │   └── Spy.cpp
│   └── GUI/
│       ├── WelcomeScreen.cpp
│       ├── PlayerSelectionScreen.cpp
│       ├── GameScreen.cpp
│       ├── gui.cpp
│       └── main.cpp
│
├── Tests/
│   └── demo_test.cpp
```

## Features Implemented  
- Turn-based game engine  
- Command-line game via `main.cpp`  
- Full graphical game with SFML  
- Role system using inheritance and polymorphism  
- Random role assignment via factory pattern  
- Coin-based actions: gather, tax, bribe, arrest, sanction, coup  
- Special role abilities and block mechanics  
- Game win detection and rule enforcement  
- Clean modular structure with GUI separation  

## Requirements  
- g++ with C++17 support  
- Linux (tested on Ubuntu)  
- Make  
- libsfml-dev  
- Valgrind (optional)

## Installation & Setup  

Clone the repository:  
```
git clone https://github.com/AvivOz/ex3-coup-game.git
cd ex3-coup-game
```

Check compilers:  
```
g++ --version
make --version
```

Install SFML:  
```
sudo apt update
sudo apt install libsfml-dev
```

For Windows/macOS – visit: https://www.sfml-dev.org/download.php

## How to Run  

Command-line version:  
```
make Main
./main
```

Graphical version:  
```
make gui_run
```

Run tests:  
```
make test
```

Check memory leaks:  
```
make valgrind
```

## Game Rules  

| Action   | Description |
|----------|-------------|
| Gather   | +1 coin |
| Tax      | +2 coins (Governor gets +3) |
| Bribe    | Pay 4 coins for an extra turn |
| Arrest   | Take 1 coin from another player |
| Sanction | Block economic actions of a player |
| Coup     | Pay 7 coins to eliminate a player (mandatory at 10+) |
| Win      | Last player remaining wins |

## Character Roles  

| Role     | Special Ability             | Block Capability         |
|----------|-----------------------------|---------------------------|
| Governor | Tax for +3 coins            | Block tax actions         |
| Judge    | Immune to bribes            | Block bribes              |
| General  | Can block coups             | Bonus on arrest           |
| Baron    | Bonus from sanctions        | Can invest coins          |
| Merchant | Bonus if holding ≥3 coins   | Bonus when arrested       |
| Spy      | View opponent's coins       | Block arrests             |

## Technical Implementation  
- Object-Oriented Design with base Player class and role inheritance  
- Factory pattern to generate role objects  
- GUI built modularly with SFML  
- Turn management and elimination logic  
- Enforced coup rule for 10+ coins  

## Testing  
Located in: `Tests/demo_test.cpp`  
Includes 30+ test cases for:  
- Game mechanics  
- Turn order  
- Role-specific behavior  
- Invalid actions  
- Win detection  

Run with:  
```
make test
make valgrind
```

## Memory Management  
- Verified with Valgrind – no leaks  
- Smart pointers and RAII  
- No raw pointer misuse  
- Exception-safe cleanup