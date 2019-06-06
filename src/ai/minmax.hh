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
    constexpr int lvv_mva[8][8] =
    {         /*P*/  /*N*/  /*B*/  /*R*/  /*Q*/  /*K*/
        {0, 0,    0,     0,     0,     0,     0,     0},
        {0, 0,    0,     0,     0,     0,     0,     0},
/*P*/   {0, 0, 6002, 20225, 20250, 20400, 20800, 26900},
/*N*/   {0, 0, 4775, 6004 , 20025, 20175, 20575, 26675},
/*B*/   {0, 0, 4750, 4975 , 6006 , 20150, 20550, 26650},
/*R*/   {0, 0, 4600, 4825 , 4850 , 6008 , 20400, 26500},
/*Q*/   {0, 0, 4200, 4425 , 4450 , 4600 , 6010 , 26100},
/*K*/   {0, 0, 3100, 3325 , 3350 , 3500 , 3900 , 26000}
    };
    extern std::unordered_map<uint64_t, move::Move> h_map;
    int root_search(board::Board& board, int alpha, int beta, int depth, move::Move* best_move);
}