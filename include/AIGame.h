//
// Created by Lukasz-Lap on 12.05.2020.
//

#pragma once

/**
 * @brief Interface required to perform minimax algorithm, with alpha beta pruning. In derived class appropriate data
 *        structure required (selected by user)
 */
class AIGame {
public:
    virtual int FindBestMove() = 0;
    virtual int Minimize(int alpha, int beta, int depth) = 0;
    virtual int Maximize(int alpha, int beta, int depth) = 0;
};




