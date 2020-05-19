//
// Created by Lukasz-Lap on 19.05.2020.
//

#pragma once

#include "SFML/Graphics.hpp"

class DisplayableGame {
protected:
    int _number_of_players;
    sf::RenderWindow &_window;

    virtual void Start() = 0;

    virtual bool HaveWinner() const = 0;

    virtual bool IsTie() const = 0;

    virtual void TakeTurn() = 0;

    //virtual bool GetWinner() = 0;

public:

    DisplayableGame(int number_of_players, sf::RenderWindow &window);

    virtual ~DisplayableGame() = default;

    virtual void DisplayGame() = 0;

    void Run();


};




