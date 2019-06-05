#include "ai/eval.hh"

namespace ai
{
    int eval(const board::Board& b) //evaluation computed from white point of view and negate the score at the end if side == black
    {
        using namespace board;

        int score = 0;

        score += (popcount(b.bitboards_[PAWN]&b.bitboards_[b.side_]) - popcount(b.bitboards_[PAWN]&b.bitboards_[!b.side_])) * pawn_value;
        score += (popcount(b.bitboards_[KNIGHT]&b.bitboards_[b.side_]) - popcount(b.bitboards_[KNIGHT]&b.bitboards_[!b.side_])) * knight_value;
        score += (popcount(b.bitboards_[BISHOP]&b.bitboards_[b.side_]) - popcount(b.bitboards_[BISHOP]&b.bitboards_[!b.side_])) * bishop_value;
        score += (popcount(b.bitboards_[ROOK]&b.bitboards_[b.side_]) - popcount(b.bitboards_[ROOK]&b.bitboards_[!b.side_])) * rook_value;
        score += (popcount(b.bitboards_[QUEEN]&b.bitboards_[b.side_]) - popcount(b.bitboards_[QUEEN]&b.bitboards_[!b.side_])) * queen_value;
        score += (popcount(b.bitboards_[KING]&b.bitboards_[b.side_]) - popcount(b.bitboards_[KING]&b.bitboards_[!b.side_])) * king_value;

        return score;
    }
}