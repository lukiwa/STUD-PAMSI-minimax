//
// Created by Lukasz-Lap on 07.05.2020.
//

#pragma once

#include <array>
#include <tuple>
#include "Game.h"


enum class BoardPositionState {
    PLAYER, AI, FREE
};


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
protected:
    const int _number_of_rows;
    const int _number_of_columns;
    const int _available_places;
    int _taken_places;
    BoardPositionState _current_player;
    mutable BoardPositionState _winner;
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




