//
// Created by Lukasz-Lap on 07.05.2020.
//

#pragma once

#include <array>
#include <tuple>
#include "Game.h"
#include "BoardPositionState.h"


struct LastMove {
    int column;
    int row;
    BoardPositionState state;

    void Set(int column, int row, BoardPositionState state) {
        this->column = column;
        this->row = row;
        this->state = state;
    }
};

class Connect4 : public Game {
private:
    const int _available_places;
    int _taken_places;
    BoardPositionState _current_player;
    //std::pair<int, int> _last_move;
    LastMove _last_move;
    std::array<std::array<BoardPositionState, 6>, 7> _board{};


    void Start() override;

    bool HaveWinner() const override;

    bool IsTie() const override;

    void TakeTurn() override;


public:
    Connect4();

    void DisplayGame() override;

    bool DropCoin(int column, BoardPositionState state);


};




