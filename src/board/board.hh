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
        std::vector<move::Move> gen_king_moves(Color color);
        std::vector<move::Move> gen_queen_moves(Color color);
        std::vector<move::Move> gen_rook_moves(Color color);
        std::vector<move::Move> gen_bishop_moves(Color color);
        std::vector<move::Move> gen_knight_moves(Color color);
        std::vector<move::Move> gen_pawn_moves(Color color);

    private:
        int ply_;
        bitboard bitboards_[8];
        //FIXME: NEED TIMES

    };
}
