#include "types.hh"
#include "move.hh"
#include "bitboards.hh"

namespace board
{
    void make_promotions(Movelist& ml, square to, square ksq, gentype Type, Direction D)
    {
        if (Type == CAPTURES || Type == EVASIONS || Type == NON_EVASIONS)
            ml.push_back(Move((square)(to - D), to, queen, PROMOTION));

        if (Type == QUIETS || Type == EVASIONS || Type == NON_EVASIONS)
        {
            ml.push_back(Move((square)(to - D), to, rook, PROMOTION));
            ml.push_back(Move((square)(to - D), to, bishop, PROMOTION));
            ml.push_back(Move((square)(to - D), to, knight, PROMOTION));
        }

        // Knight promotion is the only promotion that can give a direct check
        // that's not already included in the queen promotion.
        if (Type == QUIET_CHECKS && (PseudoAttacks[knight][to] & SquareBB[ksq]))
            ml.push_back(Move((square)(to - D), to, knight, PROMOTION));
    }
}