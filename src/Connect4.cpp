//
// Created by Lukasz-Lap on 07.05.2020.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include "Connect4.h"

Connect4::Connect4() :
        _available_places(6 * 7),
        _number_of_columns(7),
        _number_of_rows(6),
        _taken_places(0),
        _current_player(BoardPositionState::PLAYER) {

    _last_move.Set(0, 0, BoardPositionState::PLAYER);
    //init board with free spaces
    for (auto &i: _board) {
        std::fill(i.begin(), i.end(), BoardPositionState::FREE);
    }
}


/**
 * @brief Check if the game has winner
 * @return true if has winner, false otherwise
 */
bool Connect4::HaveWinner() const {
    if (CoinsConnected(4, _last_move.state)) {
        _winner = _last_move.state;
        return true;
    }
    return false;
}

/**
 * @brief Checks for free spaces in the board
 * @return true if there are available places.
 */
bool Connect4::IsTie() const {
    return _taken_places == _available_places;
}


/**
 * @brief Insert coin in given column
 * @param column picked column
 * @param state which state
 * @return true if dropped, false if column is full
 */
bool Connect4::DropCoin(int column, BoardPositionState state) {

    for (int i = _number_of_rows - 1; i >= 0; --i) {
        if (_board[column][i] == BoardPositionState::FREE) {
            _board[column][i] = state;
            _last_move.Set(column, i, state);
            ++_taken_places;
            return true;
        }
    }

    return false;
}

/**
 * @brief Checks whether given player has connected given amount of fields
 * @note  CHECK MUST BE MADE STRAIGHT AFTER PLAYER's TURN
 * @param connected how many fields has player connected
 * @param player given player
 * @return true if given player has connected given amount of field
 */
bool Connect4::
CoinsConnected(int connected, BoardPositionState player) const {
    //if row or column contains that set - there is a winner

    std::vector<BoardPositionState> to_be_connected(connected);
    std::fill(to_be_connected.begin(), to_be_connected.end(), player);



    //check column of last move for set of 4 elements
    auto col_it = std::search(_board[_last_move.column].begin(),
                              _board[_last_move.column].end(),
                              to_be_connected.begin(),
                              to_be_connected.end());
    if (col_it != _board[_last_move.column].end()) {
        return true;
    }


    //check rows
    std::array<BoardPositionState, 7> row_arr{};
    for (int i = 0; i < _number_of_columns; ++i) {
        row_arr[i] = _board[i][_last_move.row];
    }
    auto row_it = std::search(row_arr.begin(),
                              row_arr.end(),
                              to_be_connected.begin(),
                              to_be_connected.end());
    if (row_it != row_arr.end()) {
        return true;
    }


    //check diagonals
    //from left top to right bottom - first diagonal
    std::vector<BoardPositionState> diagonal_1;
    //from left bottom to right top - second diagonal
    std::vector<BoardPositionState> diagonal_2;

    for (int i = 0; i < _number_of_rows; ++i) {
        for (int j = 0; j < _number_of_columns; ++j) {
            if (i - j == _last_move.row - _last_move.column) {
                diagonal_1.emplace_back(_board[j][i]);
            }
            if (j + i == _last_move.column + _last_move.row) {
                diagonal_2.emplace_back(_board[j][i]);
            }
        }
    }
    auto diag_1_it = std::search(diagonal_1.begin(),
                                 diagonal_1.end(),
                                 to_be_connected.begin(),
                                 to_be_connected.end());

    auto diag_2_it = std::search(diagonal_2.begin(),
                                 diagonal_2.end(),
                                 to_be_connected.begin(),
                                 to_be_connected.end());
    if (diag_1_it != diagonal_1.end()) {
        return true;
    }
    if (diag_2_it != diagonal_2.end()) {
        return true;
    }


    return false;
}

BoardPositionState Connect4::GetCurrentPlayer() {
    return _current_player;
}

/**
 * @brief Change current player (eg. after performed turn)
 */
void Connect4::ChangeCurrentPlayer() {
    if (_current_player == BoardPositionState::PLAYER) {
        _current_player = BoardPositionState::AI;
        return;
    }
    if (_current_player == BoardPositionState::AI) {
        _current_player = BoardPositionState::PLAYER;
        return;
    }


}

Move Connect4::GetLastMove() {
    return _last_move;
}

/**
 * @brief Get total number of columns
 * @return
 */
int Connect4::GetColumnNumber() {
    return _number_of_columns;
}

/**
 * @brief Get total number of rows
 * @return
 */
int Connect4::GetRowNumber() {
    return _number_of_rows;
}

