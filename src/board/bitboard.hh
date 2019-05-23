#pragma once

#include <stdint.h>
#include "board/position.hh"

namespace board
{
    using bitboard = uint64_t;

    void square_set(bitboard& bboard, const int rank, const int file);
    int getlsb(const bitboard& bboard);
    int poplsb(bitboard& bboard);
}