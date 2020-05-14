//
// Created by Lukasz-Lap on 12.05.2020.
//

#pragma once

#include "Connect4.h"
#include "AIGame.h"
#include <iostream>

class Connect4AI : public Connect4, public AIGame {
private:
    const int _max_depth;
public:
    Connect4AI();

private:
    bool RemoveTopCoin(int column);


public:
    void TakeTurn() override;

    int MiniMax(int depth, bool is_maximizing) override;

    int FindBestMove() override;
};




