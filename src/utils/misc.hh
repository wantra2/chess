#pragma once

#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/piece-type.hh"

namespace utils
{
    void pretty_print(const board::Board& board);
    void print_bitboard(const board::bitboard& bb);
    board::piece_type char_to_piece(const char& c);
    std::string move_to_uci(const move::Move& m);
    std::string prom_to_char(const board::piece_type& piece);
}
