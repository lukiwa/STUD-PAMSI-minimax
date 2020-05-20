//
// Created by Lukasz-Lap on 07.05.2020.
//

#pragma once

#include <array>
#include <tuple>
#include "BoardPosition.h"


/**
 * @brief Info about performed move.
 */
struct Move {
    int column;
    int row;
    BoardPositionState state;

    void Set(int column, int row, BoardPositionState state) {
        this->column = column;
        this->row = row;
        this->state = state;
    }
};

class Connect4 {

protected:


    const int _number_of_rows;
    const int _number_of_columns;
    const int _available_places;
    int _taken_places;
    BoardPositionState _current_player;
    mutable BoardPositionState _winner;
    Move _last_move;
    std::array<std::array<BoardPositionState, 6>, 7> _board{};


    bool CoinsConnected(int connected, BoardPositionState player) const;


public:
    Connect4();

    virtual ~Connect4() = default;

    bool DropCoin(int column, BoardPositionState state);

    BoardPositionState GetCurrentPlayer();

    void ChangeCurrentPlayer();

    Move GetLastMove();

    int GetColumnNumber();

    int GetRowNumber();

    BoardPositionState GetWinner();

    bool HaveWinner() const;

    bool IsTie() const;


};




