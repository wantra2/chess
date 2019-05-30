#pragma ocne

#include "board/board.hh"

namespace ai
{
    constexpr int pawn_value = 1;
    constexpr int knight_value = 3;
    constexpr int bishop_value = 3;
    constexpr int rook_value = 5;
    constexpr int queen_value = 9;
    constexpr int king_value = 100000;

    int eval(const board::Board& b);
}