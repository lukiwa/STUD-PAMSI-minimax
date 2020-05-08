//
// Created by Lukasz-Lap on 06.05.2020.
//
#include <algorithm>
#include "AlgorithmFunctions.h"


int algorithm::MiniMax(std::array<std::array<BoardPositionState, 6>, 7> board, int depth, bool is_maximizing) {
    return 51;

}

/**
 * @brief Check whether there are available moves left at the board
 * @param board connect4 board
 * @return true if are available, false otherwise
 */
bool isMoveAvailable(const std::array<std::array<BoardPositionState, 6>, 7> &board) {
    for (const auto &i: board) {
        auto res = std::find(i.begin(), i.end(), BoardPositionState::FREE);
        if (res != i.end()) {
            return true;
        }
    }
    return false;
}