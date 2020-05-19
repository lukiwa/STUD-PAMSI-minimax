//
// Created by Lukasz-Lap on 19.05.2020.
//

#include "DisplayableGame.h"

DisplayableGame::DisplayableGame(int number_of_players, sf::RenderWindow &window) :
        _number_of_players(number_of_players),
        _window(window) {}

/**
 * @brief Skeleton method of any 2 player game
 */
void DisplayableGame::Run() {
    setenv("DISPLAY", "127.0.0.1:0", true); //allow display on WSL
    sf::Event event;

    Start();
    while (_window.isOpen()) {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) { _window.close(); }
            if (HaveWinner()) {/*TODO*/ return;}
            if (IsTie()) { /*TODO */ return; }
            TakeTurn();

            DisplayGame();

        }

    }

}