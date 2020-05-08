//
// Created by Lukasz-Lap on 07.05.2020.
//

#include "Game.h"

Game::Game(int number_of_players) : _number_of_players(number_of_players) {}

/**
 * @brief Skeleton method of any 2 player game
 */
void Game::Run() {
    Start();
    while (!HaveWinner()) {
        TakeTurn();
        DisplayGame();
        if (IsTie()) { break; }
    }
    // GetWinner();
}
