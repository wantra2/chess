#pragma once

#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/piece-type.hh"

namespace utils
{
    void pretty_print(board::Board board);
    void print_bitboard(board::bitboard bb);
    board::piece_type char_to_piece(const char& c);
}
