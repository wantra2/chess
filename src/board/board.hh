#pragma once

#include <cstdint>
#include <vector>

#include "move/move.hh"
#include "board/color.hh"
#include "board/piece-type.hh"
#include "board/bitboard.hh"

namespace board
{
    enum EdgesMask
    {
        UP = 0xFF00000000000000,
        LEFT = 0x0101010101010101,
        RIGHT = 0x8080808080808080,
        DOWN = 0x00000000000000FF
    };

    class Board
    {
    public:

        Board();
        ~Board() = default;

        constexpr void generate_board();

        inline bitboard& get_bitboard(piece_type type);
        inline bitboard& get_bitboard(Color color);

        void init_Knight_and_KingAttacks();

        void gen_KnightMoves(std::vector<move::Move>& movelist, bitboard knights, const bitboard& targets);
        void gen_KingMoves(std::vector<move::Move>& movelist, bitboard king, const bitboard& targets);
        void gen_pawn_moves(std::vector<move::Move>& movelist, Color color);

        std::vector<move::Move> gen_king_moves(Color color);
        std::vector<move::Move> gen_queen_moves(Color color);
        std::vector<move::Move> gen_rook_moves(Color color);
        std::vector<move::Move> gen_bishop_moves(Color color);
        std::vector<move::Move> gen_knight_moves(Color color);


        void check_pawn_capture(const int position, bitboard& piece,
                                Color color, std::vector<move::Move>& movelist);

        int ply_;
        bitboard bitboards_[8];
        bitboard knightAttacks_[SQUARE_NB] = {0};
        bitboard kingAttacks_[SQUARE_NB] = {0};

        //FIXME: NEED TIMES
    private:
        void gen_non_pawn(std::vector<move::Move>& movelist, bitboard attacks, const int square_from);
    };
}
