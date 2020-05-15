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
        auto x = MiniMax(i, _max_depth, true);
        moves.emplace(x, i);
        std::cout << x << " " << i << std::endl;
        RemoveTopCoin(i);
    }

    return moves.rbegin()->second;
}

/**
 * @brief Minimax algorithm for finding best move in the game
 * @param depth depth of the search
 * @param is_maximizing is the maximizer turn
 * @return max score
 */
int Connect4AI::MiniMax(int node, int depth, bool is_maximizing) {
    int bestValue = is_maximizing ? -Evaluate(BoardPositionState::AI) : Evaluate(BoardPositionState::PLAYER);


    if (depth <= 0) {
        return bestValue;
    }
/*
    HaveWinner();
    if (_winner == BoardPositionState::AI) {
        return depth;
    }
    if (_winner == BoardPositionState::PLAYER) {
        return -depth;
    }
*/


    if (!DropCoin(node, is_maximizing ? BoardPositionState::AI : BoardPositionState::PLAYER)) {
        return bestValue;
    }
    int v = MiniMax(node, depth - 1, !is_maximizing);
    bestValue = is_maximizing ? std::max(bestValue, v) : std::min(bestValue, v);
    RemoveTopCoin(node);


    return bestValue;
}

int Connect4AI::Evaluate(BoardPositionState player) {
    int score = 0;
    if (CoinsConnected(4, player)) {
        score += 1000;
    }
    if (CoinsConnected(2, player)) {
        score += 4;
    }
    if (_last_move.column == 2) {
        score += 2;
    }
    return score;

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




