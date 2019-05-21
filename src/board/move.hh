#pragma once

#include <cstdint>

#include "board/position.hh"
#include "board/piece-type.hh"

namespace move
{
    /*
      A Move is an 16 bits int ordered as :
      bits 0 - 5   Move dst
      bits 6 - 11  Move src
      bits 12 - 13 Move flag: 1 -> capture, 2 -> castling, 3 -> en passant
      bits 14 - 16 Promotion to the type piece_type
     */
    using Move = uint16_t;

    /*
      These two functions convert a Move (int16) to a format more suitable for
      the class Position
     */
    board::Rank int_to_rank(int i);
    board::File int_to_file(int i);

    /*
      Returns a Move's source/destination formated as a Position
     */
    board::Position move_src(Move move);
    board::Position move_dst(Move move);

    /*
      Move flags handler
     */
    bool is_capture(Move move);
    bool is_castling(Move move);
    bool is_passant(Move move);

    bool is_promotion(Move move);

    board::piece_type promotion_type(Move move);
}
