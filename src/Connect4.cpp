//
// Created by Lukasz-Lap on 07.05.2020.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include "Connect4.h"

Connect4::Connect4() : Game(2), _available_places(6 * 7) {
    _taken_places = 0;
    _current_player = BoardPositionState::PLAYER;
    _last_move.Set(0, 0, BoardPositionState::PLAYER);
    //init board with free spaces
    for (auto &i: _board) {
        std::fill(i.begin(), i.end(), BoardPositionState::FREE);
    }
}

void Connect4::Start() {
    DisplayGame();
}

bool Connect4::HaveWinner() const {
    //if row or column contains that set - there is a winner
    std::array<BoardPositionState, 4> col_and_row_winner{};
    std::fill(col_and_row_winner.begin(), col_and_row_winner.end(), _last_move.state);


    //check column of last move for set of 4 elements
    auto col_it = std::search(_board[_last_move.column].begin(),
                              _board[_last_move.column].end(),
                              col_and_row_winner.begin(),
                              col_and_row_winner.end());
    if (col_it != _board[_last_move.column].end()) {
        return true;
    }


    //check rows
    std::array<BoardPositionState, 7> row_arr{};
    for (int i = 0; i < 7; ++i) {
        row_arr[i] = _board[i][_last_move.row];
    }
    auto row_it = std::search(row_arr.begin(),
                              row_arr.end(),
                              col_and_row_winner.begin(),
                              col_and_row_winner.end());
    if (row_it != row_arr.end()) {
        return true;
    }


    //check diagonals
    //from left top to right bottom - first diagonal
    std::vector<BoardPositionState> diagonal_1;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (i - j == _last_move.row - _last_move.column) {
                diagonal_1.emplace_back(_board[j][i]);
            }
        }
    }
    auto diag_1_it = std::search(diagonal_1.begin(),
                                 diagonal_1.end(),
                                 col_and_row_winner.begin(),
                                 col_and_row_winner.end());
    if (diag_1_it != diagonal_1.end()) {
        return true;
    }

    //from left bottom to right top - second diagonal
    std::vector<BoardPositionState> diagonal_2;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (j + i == _last_move.column + _last_move.row) {
                diagonal_2.emplace_back(_board[j][i]);
            }
        }
    }
    auto diag_2_it = std::search(diagonal_2.begin(),
                                 diagonal_2.end(),
                                 col_and_row_winner.begin(),
                                 col_and_row_winner.end());
    if (diag_2_it != diagonal_2.end()) {
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

void Connect4::TakeTurn() {
    if (_current_player == BoardPositionState::AI) {
        //auto move = FindBestMove(board);
        //DropCoin(move, BoardPositionState::AI)
        //-----------DEBUG--------------------------
        int col = 0;
        std::cin >> col;
        DropCoin(col, BoardPositionState::AI);;
        //-------------------------------------------
        _current_player = BoardPositionState::PLAYER;
        return;
    }

    if (_current_player == BoardPositionState::PLAYER) {
        int col = 0;
        std::cin >> col;
        DropCoin(col, BoardPositionState::PLAYER);
        _current_player = BoardPositionState::AI;
        return;
    }


}

void Connect4::DisplayGame() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (_board[j][i] == BoardPositionState::PLAYER) {
                std::cout << "P";
            }
            if (_board[j][i] == BoardPositionState::AI) {
                std::cout << "A";
            }
            if (_board[j][i] == BoardPositionState::FREE) {
                std::cout << "F";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/**
 * @brief Insert coin in given column
 * @param column picked column
 * @param state which state
 * @return true if dropped, false if column is full
 */
bool Connect4::DropCoin(int column, BoardPositionState state) {

    for (int i = 5; i >= 0; --i) {
        if (_board[column][i] == BoardPositionState::FREE) {
            _board[column][i] = state;
            _last_move.Set(column, i, state);
            ++_taken_places;
            return true;
        }
    }

/*
    for (auto i = _board[column].end() - 1; i != _board[column].begin(); --i) {
        if (*i == BoardPositionState::FREE) {
            *i = state;
            ++_taken_places;

            return true;
        }
    }
*/
    return false;
}

