#include "ai/eval.hh"

namespace ai
{
    board::square relative(const board::square& sq, const int& color)
    {
        return (board::square)(color == board::WHITE ? MIRROR64(sq) : sq);
    }

    int eval(const board::Board& b) //evaluation computed from white point of view and negate the score at the end if side == black
    {
        int res = 0;
        res += b.material_[b.side_] - b.material_[!b.side_];
        res += b.position_[b.side_] - b.position_[!b.side_];
        return res;
    }
}