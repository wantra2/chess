#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "board/board.hh"
#include "ai/eval.hh"
#include "utils/misc.hh"
#include "move/move.hh"

namespace ai
{
    struct search_infos
    {
        int nodes;
        int depth;
        move::Move best_move;
    };

    constexpr int INFINITE = 500000;
    
    int root_search(board::Board& board, int alpha, int beta, int depth, move::Move* best_move);
}