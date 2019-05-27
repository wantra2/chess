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
      bits 12 - 13 Move flag: 1 -> promotion, 2 -> castling, 3 -> en passant
      bits 14 - 15 Promotion to the type piece_type
     */
    using Move = uint16_t;
    enum MoveType
    {
        NORMAL,
        PROMOTION,
        CASTLING,
        EN_PASSANT
    };

    /*
      These two functions convert a Move (int16) to a format more suitable for
      the class Position
     */
    board::Rank int_to_rank(int i);
    board::File int_to_file(int i);

    /*
      Returns a Move's source/destination formated as a Position
     */
    board::square move_src(const Move move);
    board::square move_dst(const Move move);

    /*
      Move flags handler
     */
    bool is_castling(const Move move);
    bool is_passant(const Move move);

    bool is_promotion(const Move move);

    move::MoveType mv_type(const Move move);

    board::piece_type promotion_type(const Move move);

    int pos_to_int(board::Position pos);

    Move create_move(const int square_from, const int square_to,
            const board::piece_type prom, const MoveType move_type);

    Move create_move(const int square_from, const int square_to);

    Move create_move(const int square_from, const int square_to, const MoveType move_type);
}
