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

        const bitboard& get_bitboard(piece_type type) const;
        const bitboard& get_bitboard(Color color) const;
        const bitboard& knightAttacks(const int square) const;
        const bitboard& kingAttacks(const int square) const;
        const bitboard& bishopAttacks(const int index) const;
        const bitboard& rookAttacks(const int index) const;
        const Magic& bishopMagics(const int square) const;
        const Magic& rookMagics(const int square) const;

        void gen_KnightMoves(std::vector<move::Move>& movelist, bitboard knights, const bitboard& targets) const;
        void gen_KingMoves(std::vector<move::Move>& movelist, bitboard king, const bitboard& targets) const;
        void gen_queen_bishop_moves(std::vector<move::Move>& movelist, bitboard pieces, const bitboard& occupied, const bitboard& targets) const;
        void gen_queen_rook_moves(std::vector<move::Move>& movelist, bitboard pieces, const bitboard& occupied, const bitboard& targets) const;
        void gen_pawn_moves(std::vector<move::Move>& movelist, Color color) const;

        void check_pawn_capture(const int position, bitboard& piece,
                                Color color, std::vector<move::Move>& movelist) const;


        void remove_piece(square position, piece_type type, Color color);
        void remove_piece(File file, Rank rank, piece_type type, Color color);
        void remove_piece(const bitboard& piece, piece_type type, Color color);

        void add_piece(square position, piece_type type, Color color);
        void add_piece(File file, Rank rank, piece_type type, Color color);
        void add_piece(const bitboard& piece, piece_type type, Color color);

        bitboard bitboards_[8];
    private:

        int ply_;

        bitboard knightAttacks_[SQUARE_NB] = {0};
        bitboard kingAttacks_[SQUARE_NB] = {0};
        bitboard bishopAttacks_[5248] = {0};
        bitboard rookAttacks_[102400] = {0};
        Magic bishopMagics_[SQUARE_NB];
        Magic rookMagics_[SQUARE_NB];

        void init_Knight_and_KingAttacks();
        void init_slide_attacks();
        void gen_non_pawn(std::vector<move::Move>& movelist, bitboard attacks, const int square_from) const;
        bitboard slider_attacks(const int from_square, const bitboard& occupied, const int offsets[4][2]) const;
        void init_magics(const int square, Magic* table, const bitboard& magic_number, const int offsets[4][2]);
    };
}
