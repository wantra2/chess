#include "ai/eval.hh"

namespace ai
{
    int eval(const board::Board& b) //evaluation computed from white point of view and negate the score at the end if side == black
    {
        using namespace board;

        int score = 0;

        score += (popcount(b.bitboards_[PAWN]&b.bitboards_[WHITE]) - popcount(b.bitboards_[PAWN]&b.bitboards_[BLACK])) * pawn_value;
        score += (popcount(b.bitboards_[KNIGHT]&b.bitboards_[WHITE]) - popcount(b.bitboards_[KNIGHT]&b.bitboards_[BLACK])) * knight_value;
        score += (popcount(b.bitboards_[BISHOP]&b.bitboards_[WHITE]) - popcount(b.bitboards_[BISHOP]&b.bitboards_[BLACK])) * bishop_value;
        score += (popcount(b.bitboards_[ROOK]&b.bitboards_[WHITE]) - popcount(b.bitboards_[ROOK]&b.bitboards_[BLACK])) * rook_value;
        score += (popcount(b.bitboards_[QUEEN]&b.bitboards_[WHITE]) - popcount(b.bitboards_[QUEEN]&b.bitboards_[BLACK])) * queen_value;
        score += (popcount(b.bitboards_[KING]&b.bitboards_[WHITE]) - popcount(b.bitboards_[KING]&b.bitboards_[BLACK])) * king_value;

        if (b.side_ == BLACK)
            return -score;
        return score;
    }
}