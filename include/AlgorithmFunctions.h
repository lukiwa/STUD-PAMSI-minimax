//
// Created by Lukasz-Lap on 06.05.2020.
//

#pragma once

#include <memory>
#include <vector>
#include "BoardPositionState.h"


namespace algorithm {


    int MiniMax(std::array<std::array<BoardPositionState, 6>, 7> board, int depth, bool is_maximizing);

    bool isMoveAvailable(const std::array<std::array<BoardPositionState, 15>, 15> &arr);

}

