//
// Created by Lukasz-Lap on 07.05.2020.
//

#pragma once


#include <cstdint>

class Game {
protected:
    int _number_of_players;


    virtual void Start() = 0;

    virtual bool HaveWinner() const = 0;

    virtual bool IsTie() const = 0;

    virtual void TakeTurn() = 0;

    //virtual bool GetWinner() = 0;

public:
    virtual void DisplayGame() = 0;

    void Run();

    explicit Game(int number_of_players);

    virtual ~Game() = default;

public:
};




