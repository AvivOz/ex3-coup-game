#include "gui.hpp"
#include "../include/playerFactory.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <set>
#include <string>
#include "GameTurnScreen.hpp"

GUI::GUI()
    : window(sf::VideoMode(800, 600), "Coup Game"),
      state(ScreenState::Welcome),
      justSwitchedScreen(false),  // הסדר כאן חשוב
      selectedPlayerCount(0), 
      currentInputIndex(0),
      activeNameBoxIndex(-1),
      gameTurnScreen(nullptr),
      readyClicked(false)
    {
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    startGameButton.setSize(sf::Vector2f(150, 50));
    startGameButton.setFillColor(sf::Color::Green);
    startGameButton.setPosition(325, 500);

    startGameText.setFont(font);
    startGameText.setString("Start Game");
    startGameText.setCharacterSize(20);
    startGameText.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = startGameText.getLocalBounds();
    startGameText.setPosition(
        startGameButton.getPosition().x + (startGameButton.getSize().x - textRect.width) / 2,
        startGameButton.getPosition().y + (startGameButton.getSize().y - textRect.height) / 2 - 5
    );

    initWelcome();
    initSelectPlayerCount();
    initNameInput();
    initGame();
}

void GUI::initWelcome() {
    titleText.setFont(font);
    titleText.setString("Coup Game");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(300, 100);

    startButton.setSize(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color::Blue);
    startButton.setPosition(300, 300);

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(325, 310);

    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(300, 400);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(370, 410);
}

void GUI::initSelectPlayerCount() {
    playerCountButtons.clear();
    playerCountTexts.clear();

    playerCountTitle.setFont(font);
    playerCountTitle.setString("Select Number of Players");
    playerCountTitle.setCharacterSize(30);
    playerCountTitle.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = playerCountTitle.getLocalBounds();
    playerCountTitle.setPosition((window.getSize().x - titleBounds.width) / 2.f, 150);

    for (int i = 2; i <= 6; ++i) {
        sf::RectangleShape btn(sf::Vector2f(60, 60));
        btn.setFillColor(sf::Color::Blue);
        btn.setPosition(100 + (i - 2) * 100, 300);
        playerCountButtons.push_back(btn);

        sf::Text txt;
        txt.setFont(font);
        txt.setString(std::to_string(i));
        txt.setCharacterSize(24);
        txt.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = txt.getLocalBounds();
        txt.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
        txt.setPosition(
            btn.getPosition().x + btn.getSize().x / 2.f,
            btn.getPosition().y + btn.getSize().y / 2.f);

        playerCountTexts.push_back(txt);
    }

    backButton.setSize(sf::Vector2f(80, 35));
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(20, window.getSize().y - 50);

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    sf::FloatRect backBounds = backText.getLocalBounds();
    backText.setOrigin(backBounds.left + backBounds.width / 2.f, backBounds.top + backBounds.height / 2.f);
    backText.setPosition(
        backButton.getPosition().x + backButton.getSize().x / 2.f,
        backButton.getPosition().y + backButton.getSize().y / 2.f);
}

void GUI::initNameInput() {
    nameInputBoxes.clear();
    nameInputTexts.clear();
    nameBuffers.clear();
    nameLabels.clear();

    nameInputTitle.setFont(font);
    nameInputTitle.setString("Enter the Names of the Players");
    nameInputTitle.setCharacterSize(28);
    nameInputTitle.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = nameInputTitle.getLocalBounds();
    nameInputTitle.setPosition((window.getSize().x - titleBounds.width) / 2.f, 60);

    float startY = 150;
    float inputX = (window.getSize().x - 250) / 2.f;
    for (int i = 0; i < 6; ++i) {
        sf::RectangleShape box(sf::Vector2f(250, 40));
        box.setFillColor(sf::Color::White);
        box.setPosition(inputX, startY + i * 60);
        nameInputBoxes.push_back(box);

        sf::Text txt;
        txt.setFont(font);
        txt.setCharacterSize(22);
        txt.setFillColor(sf::Color::Black);
        txt.setPosition(inputX + 10, startY + i * 60 + 5);
        nameInputTexts.push_back(txt);

        nameBuffers.push_back("");

        sf::Text label;
        label.setFont(font);
        label.setCharacterSize(22);
        label.setFillColor(sf::Color::White);
        label.setString("Player " + std::to_string(i + 1) + ":");
        label.setPosition(inputX - 110, startY + i * 60 + 5);
        nameLabels.push_back(label);
    }

    backButton.setSize(sf::Vector2f(80, 35));
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(20, window.getSize().y - 50);

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    sf::FloatRect backBounds = backText.getLocalBounds();
    backText.setOrigin(backBounds.left + backBounds.width / 2.f, backBounds.top + backBounds.height / 2.f);
    backText.setPosition(
    backButton.getPosition().x + backButton.getSize().x / 2.f,
    backButton.getPosition().y + backButton.getSize().y / 2.f);

    activeNameBoxIndex = 0;
}

void GUI::initGame() {
    gameStarted = false;
    readyClicked = false;
    currentInputIndex = 0;
    playerNames.clear();
    nameBuffers.clear();
    nameInputTexts.clear();
    initNameInput();
}

void GUI::handleEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        // Order matters: handle game screen event before checking state change
        if (state == ScreenState::Game && gameTurnScreen) {
            gameTurnScreen->handleEvent(window);

            if (gameTurnScreen->didRequestQuit()) {
                state = ScreenState::Welcome;
                gameStarted = false;
                readyClicked = false;
                delete gameTurnScreen;
                gameTurnScreen = nullptr;
                game.reset();
                justSwitchedScreen = true;
            }
            return;
        }

        // Welcome screen
        if (state == ScreenState::Welcome) {
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (startButton.getGlobalBounds().contains(mousePos)) {
                    state = ScreenState::SelectPlayerCount;
                } else if (exitButton.getGlobalBounds().contains(mousePos)) {
                    window.close();
                }
            }
        }

        // Select player count screen
        else if (state == ScreenState::SelectPlayerCount) {
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int i = 0; i < static_cast<int>(playerCountButtons.size()); ++i) {
                    if (playerCountButtons[i].getGlobalBounds().contains(mousePos)) {
                        selectedPlayerCount = i + 2; // i מייצג 0 => 2 שחקנים, 1 => 3 וכו'
                        state = ScreenState::NameInput;
                        initNameInput(); // עדכון שדות שמות
                        break;
                    }
                }

                if (backButton.getGlobalBounds().contains(mousePos)) {
                    state = ScreenState::Welcome;
                }
            }
        }

        // Name input screen
        else if (state == ScreenState::NameInput) {
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int i = 0; i < selectedPlayerCount; ++i) {
                    if (nameInputBoxes[i].getGlobalBounds().contains(mousePos)) {
                        activeNameBoxIndex = i;
                        break;
                    }
                }

                if (startGameButton.getGlobalBounds().contains(mousePos)) {
                    // נוודא שיש לפחות 2 שמות לא ריקים שונים
                    std::set<std::string> uniqueNames;
                    int nonEmpty = 0;
                    for (int i = 0; i < selectedPlayerCount; ++i) {
                        std::string name = nameBuffers[i];
                        if (!name.empty()) {
                            uniqueNames.insert(name);
                            ++nonEmpty;
                        }
                    }
                    if (nonEmpty >= 2 && uniqueNames.size() >= 2) {
                        startGameIfReady();
                    }
                }

                if (backButton.getGlobalBounds().contains(mousePos)) {
                    state = ScreenState::SelectPlayerCount;
                }
            }

            else if (event.type == sf::Event::TextEntered && activeNameBoxIndex >= 0) {
                if (event.text.unicode == '\b') {  // Backspace
                    if (!nameBuffers[activeNameBoxIndex].empty()) {
                        nameBuffers[activeNameBoxIndex].pop_back();
                    }
                } else if (event.text.unicode < 128 && event.text.unicode >= 32) {
                    nameBuffers[activeNameBoxIndex] += static_cast<char>(event.text.unicode);
                }

                nameInputTexts[activeNameBoxIndex].setString(nameBuffers[activeNameBoxIndex]);
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab) {
                    activeNameBoxIndex = (activeNameBoxIndex + 1) % selectedPlayerCount;
                }
            }
        }
    }
}

void GUI::startGameIfReady() {

    if (gameStarted || readyClicked) {
        return;
    }

    readyClicked = true;  
    gameStarted = true;

    game.reset();

    playerNames.clear();
    for (int i = 0; i < selectedPlayerCount; ++i) {
        playerNames.push_back(nameBuffers[i]);
    }

    if (gameTurnScreen != nullptr) {
        delete gameTurnScreen;
        gameTurnScreen = nullptr;
    }

    for (const auto& name : playerNames) {
        playerFactory(game, name);
    }

    gameTurnScreen = new GameTurnScreen(game.get_players_list(), game);
    state = ScreenState::Game;
}

void GUI::update() {
    if (state == ScreenState::Game && gameTurnScreen && gameTurnScreen->didRequestQuit()) {
        state = ScreenState::Welcome;
        gameStarted = false;
        readyClicked = false;
        delete gameTurnScreen;
        gameTurnScreen = nullptr;
        game.reset();
        justSwitchedScreen = true;
        return;
    }

    if (state == ScreenState::NameInput && justSwitchedScreen) {
        activeNameBoxIndex = 0;
        justSwitchedScreen = false;
    }
}

void GUI::draw() {
    window.clear(sf::Color(30, 30, 30));

    if (state == ScreenState::Welcome) {
        window.draw(titleText);
        window.draw(startButton);
        window.draw(startText);
        window.draw(exitButton);
        window.draw(exitText);
    }
    else if (state == ScreenState::SelectPlayerCount) {
        window.draw(playerCountTitle);
        for (const auto& btn : playerCountButtons) window.draw(btn);
        for (const auto& txt : playerCountTexts) window.draw(txt);
        window.draw(backButton);
        window.draw(backText);
    }
    else if (state == ScreenState::NameInput) {
        window.draw(nameInputTitle);
        for (int i = 0; i < selectedPlayerCount; ++i) {
            if (i == activeNameBoxIndex) {
                sf::RectangleShape highlight(nameInputBoxes[i]);
                highlight.setOutlineColor(sf::Color::Green);
                highlight.setOutlineThickness(3);
                highlight.setFillColor(nameInputBoxes[i].getFillColor());
                window.draw(highlight);
            } else {
                window.draw(nameInputBoxes[i]);
            }
            window.draw(nameLabels[i]);
            window.draw(nameInputTexts[i]);
        }
        window.draw(backButton);
        window.draw(backText);
        window.draw(startGameButton);
        window.draw(startGameText);
    }
    else if (state == ScreenState::Game) {
        if (gameTurnScreen) {
            gameTurnScreen->draw(window);
        }
    }

    window.display();
}

void GUI::run() {
    while (window.isOpen()) {
        handleEvent();
        update();
        draw();
    }
}