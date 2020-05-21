//
// Created by Lukasz-Lap on 12.05.2020.
//

#pragma once

#include "Connect4.h"
#include "AIGame.h"
#include <iostream>

class Connect4AI : public Connect4, public AIGame {
private:
    int _max_depth;

    bool RemoveTopCoin(int column);


    int Evaluate(BoardPositionState player);

    int Minimize(int alpha, int beta, int depth) override;

    int Maximize(int alpha, int beta, int depth) override;


public:
    void SetMaxDepth(int depth);
    explicit Connect4AI(int max_depth);

    int FindBestMove() override;


};




