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
 * @brief Find best move for AI - aka. Minimax
 * @return column to play
 */
int Connect4AI::FindBestMove() {
    std::map<int, int> moves;
    int alpha = -1000000;
    int beta = 1000000;


    for (int i = 0; i < _number_of_columns; ++i) {
        if (!DropCoin(i, BoardPositionState::AI)) {
            continue;
        }
        //AI has made a move - it's now minimizer's (human's) turn
        auto score = Minimize(alpha, beta, _max_depth);
        moves.emplace(score, i);


        std::cout << score << " " << i << " " << alpha << std::endl;
        RemoveTopCoin(i);
    }

    //get move with highest score
    return moves.rbegin()->second;
}

/**
 * @brief Minimizer's turn
 * @param alpha alpha param
 * @param beta beta param
 * @param depth depth of search
 * @return score
 */
int Connect4AI::Minimize(int alpha, int beta, int depth) {

    //if ai in prev turn has won
    if (CoinsConnected(4, BoardPositionState::AI)) {
        return 1000 + depth;
    }
    if (IsTie()) { return depth; }
    //in non-terminal case - evaluate ai last move
    if (depth <= 0) return Evaluate(BoardPositionState::AI);


    int best_move_score = 1000000;

    for (int i = 0; i < _number_of_columns; i++) {
        //human's turn
        if (!DropCoin(i, BoardPositionState::PLAYER)) {
            continue;
        }
        //human has made a turn - it's ai's turn
        auto move_score = Maximize(alpha, beta, depth - 1);

        //minimizing step - beta changes
        if (move_score < beta) {
            beta = move_score;
        }
        if (move_score < best_move_score) {
            best_move_score = move_score;
        }
        RemoveTopCoin(i);

        //alpha cut-off
        if (beta <= alpha) break;
    }

    return best_move_score;
}

/**
 * @brief Maximizer's turn
 * @param alpha alpha parameter
 * @param beta beta parameter
 * @param depth depth of search
 * @return score
 */
int Connect4AI::Maximize(int alpha, int beta, int depth) {

    //if human in prev turn has won
    if (CoinsConnected(4, BoardPositionState::PLAYER)) {
        return -1000 - depth;
    }
    if (IsTie()) {
        return -depth;
    }
    //in non-terminal case - evaluate ai last move
    if (depth <= 0) return -Evaluate(BoardPositionState::PLAYER);


    int best_move_score = -1000000;
    for (int i = 0; i < _number_of_columns; i++) {
        //ai's turn
        if (!DropCoin(i, BoardPositionState::AI)) {
            continue;
        }
        //ai has made a turn - it is ai's turn
        auto move_score = Minimize(alpha, beta, depth - 1);
        if (move_score > alpha) {
            alpha = move_score;
        }
        if (move_score > best_move_score) {
            best_move_score = move_score;
        }
        RemoveTopCoin(i);

        //beta cut-off
        if (beta <= alpha) break;
    }


    return best_move_score;

}

/** TODO - possible connections rating
 * @brief Evaluate score on non-terminal state
 * @param player which player move will be evaluated
 * @return score
 */
int Connect4AI::Evaluate(BoardPositionState player) {

    int evaluation_table[6][7]{{3, 4, 5,  7,  5,  4, 3},
                               {4, 6, 8,  10, 8,  6, 4},
                               {5, 8, 11, 13, 11, 8, 5},
                               {5, 8, 11, 13, 11, 8, 5},
                               {4, 6, 8,  10, 8,  6, 4},
                               {3, 4, 5,  7,  5,  4, 3}};


    int score = 0;
    for (int i = 0; i < _number_of_rows; ++i) {
        for (int j = 0; j < _number_of_columns; ++j) {
            if (_board[j][i] == player) {
                score += evaluation_table[i][j];
            }
        }
    }
    //connections of 3 are promoted
    if (CoinsConnected(3, player)) {
        score += 50;
    }

    return score;


}


/** TODO improve this
 * @brief Remove top coin of given column
 * @param column given column
 * @return true if removed, false if not
 */
bool Connect4AI::RemoveTopCoin(int column) {

    if (column >= _number_of_columns) {
        return false;
    }
    int row = 0;
    while (row < _number_of_rows && _board[column][row] == BoardPositionState::FREE) {
        ++row;
    }


    _board[column][row] = BoardPositionState::FREE;
    return true;

}

Connect4AI::Connect4AI(int max_depth) : _max_depth(max_depth) {}







