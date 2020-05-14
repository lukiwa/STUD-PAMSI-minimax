//
// Created by Lukasz-Lap on 12.05.2020.
//

#include <map>
#include "Connect4AI.h"

void Connect4AI::TakeTurn() {
    if (_current_player == BoardPositionState::AI) {
        auto move = FindBestMove();
        DropCoin(move, BoardPositionState::AI);
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

/**
 * @brief Minimax algorithm for finding best move in the game
 * @param depth depth of the search
 * @param is_maximizing is the maximizer turn
 * @return max score
 */
int Connect4AI::MiniMax(int depth, bool is_maximizing) {
    if (depth <= 0) {
        return 0;
    }

    HaveWinner();
    if (_winner == BoardPositionState::AI) {
        return depth;
    }
    if (_winner == BoardPositionState::PLAYER) {
        return -depth;
    }


    int bestValue = is_maximizing ? -1 : 1;
    for (int i = 0; i < _number_of_columns; ++i) {
        if (!DropCoin(i, is_maximizing ? BoardPositionState::AI : BoardPositionState::PLAYER)) {
            continue;
        }
        int v = MiniMax(depth - 1, !is_maximizing);
        bestValue = is_maximizing ? std::max(bestValue, v) : std::min(bestValue, v);
        RemoveTopCoin(i);
    }
    return bestValue;
}

/** TODO - random move if more than one
 * @brief Find best move for AI
 * @return column to play
 */
int Connect4AI::FindBestMove() {
    std::map<int, int> moves;
    for (int i = 0; i < _number_of_columns; ++i) {
        if (!DropCoin(i, BoardPositionState::AI)) {
            continue;
        }
        moves.emplace(MiniMax(_max_depth, false), i);
        RemoveTopCoin(i);
    }

    return moves.rbegin()->second;
}

/** TODO improve this
 * @brief Remove top coin of given column
 * @param column given column
 * @return true if removed, false if not
 */
bool Connect4AI::RemoveTopCoin(int column) {
    int row = 0;
    while (row < _number_of_rows && _board[column][row] == BoardPositionState::FREE) {
        row++;
    }
    if (row == _number_of_rows) {
        return false;
    }

    _board[column][row] = BoardPositionState::FREE;
    //_changed = true;??
    return true;
}

Connect4AI::Connect4AI() : _max_depth(6) {}


