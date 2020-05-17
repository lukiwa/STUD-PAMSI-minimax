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
    int alpha = -1000000;
    int beta = 1000000;

    int bestMoveScore = -1000000;
    for (int i = 0; i < _number_of_columns; ++i) {
        if (!DropCoin(i, BoardPositionState::AI)) {
            continue;
        }
        auto score = Minimize(alpha, beta, _max_depth);
        moves.emplace(score, i);

        if (score > bestMoveScore) {
            bestMoveScore = score;
            alpha = score;
        }
        std::cout << score << " " << i << " " << alpha << std::endl;
        RemoveTopCoin(i);
    }

    return moves.rbegin()->second;
}

int Connect4AI::Minimize(int alpha, int beta, int depth) {


    if (CoinsConnected(4, BoardPositionState::AI)) {
        return 1000 + depth;
    }
    if (IsTie()) { return depth; }
    if (depth <= 0) return Evaluate(BoardPositionState::AI);


    int bestMoveScore = 1000000;

    for (int i = 0; i < _number_of_columns; i++) {
        if (!DropCoin(i, BoardPositionState::PLAYER)) {
            continue;
        }
        int moveScore = Maximize(alpha, beta, depth - 1);
        if (moveScore < beta) {
            beta = moveScore;
        }
        if (moveScore < bestMoveScore) {
            bestMoveScore = moveScore;
        }
        RemoveTopCoin(i);


        if (beta <= alpha) break;
    }

    return bestMoveScore;
}

int Connect4AI::Maximize(int alpha, int beta, int depth) {

    if (CoinsConnected(4, BoardPositionState::PLAYER)) {
        return -1000 - depth;
    }
    if (IsTie()) { return -depth; }
    if (depth <= 0) return -Evaluate(BoardPositionState::PLAYER);


    int bestMoveScore = -1000000;
    for (int i = 0; i < _number_of_columns; i++) {
        if (!DropCoin(i, BoardPositionState::AI)) {
            continue;
        }
        int moveScore = Minimize(alpha, beta, depth - 1);
        if (moveScore > alpha) {
            alpha = moveScore;
        }
        if (moveScore > bestMoveScore) {
            bestMoveScore = moveScore;
        }
        RemoveTopCoin(i);

        if (beta <= alpha) break;
    }


    return bestMoveScore;

}


int Connect4AI::Evaluate(BoardPositionState player) {

    int evaluationTable[6][7]{{3, 4, 5,  7,  5,  4, 3},
                              {4, 6, 8,  10, 8,  6, 4},
                              {5, 8, 11, 13, 11, 8, 5},
                              {5, 8, 11, 13, 11, 8, 5},
                              {4, 6, 8,  10, 8,  6, 4},
                              {3, 4, 5,  7,  5,  4, 3}};


    int score = 0;
    for (int i = 0; i < _number_of_rows; i++) {
        for (int j = 0; j < _number_of_columns; j++) {
            if (_board[j][i] == player) {
                score += evaluationTable[i][j];
            }
        }
    }
    if (CoinsConnected(2, player)) {
        score += 20;
    }
    if (CoinsConnected(3, player)) {
        score += 30;
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







