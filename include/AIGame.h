//
// Created by Lukasz-Lap on 12.05.2020.
//

#pragma once


class AIGame {
public:
    virtual int FindBestMove() = 0;

    virtual int MiniMax(int node, int depth, bool is_maximizing) = 0;
};




