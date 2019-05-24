#pragma once

#include "board/board.hh"
#include "board/bitboard.hh"

namespace utils
{
    void pretty_print(board::Board board);
    void print_bitboard(board::bitboard bb);
}
