#pragma once

#include <cstdint>
#include <vector>

#include "board/color.hh"
#include "board/piece-type.hh"

namespace board
{
    class Board
    {
        using Bitboard = int_fast64_t;
    public:

        using bitboard = int_fast64_t;

        Board();
        ~Board() = default;

        constexpr void generate_board();
        bitboard& get_bitboard(piece_type type);
        bitboard& get_bitboard(Color color);

    private:
        int ply_;
        bitboard bitboards_[8];
        //FIXME: NEED TIMES

    };
}
