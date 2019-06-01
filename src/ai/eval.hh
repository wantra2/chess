#pragma once

#include "board/board.hh"

namespace ai
{
    constexpr int pawn_value = 100;
    constexpr int knight_value = 325;
    constexpr int bishop_value = 350;
    constexpr int rook_value = 500;
    constexpr int queen_value = 900;
    constexpr int king_value = 1000000;

    int eval(const board::Board& b);
}