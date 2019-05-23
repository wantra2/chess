#include "board/bitboard.hh"

namespace board
{
    void square_set(bitboard& bboard, const int rank, const int file)
    {
        if ((rank >= 0 && rank <= 7) && (file >= 0 && file <= 7))
            bboard = bboard | (0x1 << board::to_square(rank, file));
    }

    int getlsb(const bitboard& bboard)
    {
        return __builtin_ctzll(bboard);
    }

    int poplsb(bitboard& bboard)
    {
        int lsb = getlsb(bboard);
        bboard = bboard & (bboard - 1);
        return lsb;
    }
}