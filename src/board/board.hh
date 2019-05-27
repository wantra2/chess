#pragma once

#include <cstdint>
#include <vector>

#include "move/move.hh"
#include "board/color.hh"
#include "board/piece-type.hh"
#include "board/bitboard.hh"

namespace board
{
    enum castlings
    {
        WHITE_SMALL,
        WHITE_BIG,
        BLACK_SMALL,
        BLACK_BIG
    };

    enum castlings_sq
    {
        WHITE_00 = 0x60,
        WHITE_000 = 0xe,
        BLACK_00 = 0x6000000000000000,
        BLACK_000 = 0x0e00000000000000
    };

    class Board
    {
    public:

        Board();
        ~Board() = default;

        void generate_board();
        void generate_pieces();

        const bitboard& get_bitboard(piece_type type) const;
        const bitboard& get_bitboard(Color color) const;

        void gen_pawn_moves(std::vector<move::Move>&, const int& color) const;
        void gen_KnightMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets) const;
        void gen_KingMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets) const;
        void gen_queen_bishop_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets) const;
        void gen_queen_rook_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets) const;
        void gen_castlings(std::vector<move::Move>& movelist, const bitboard& occupied, const int& color) const;

        void remove_piece(square position, piece_type type, int color);
        /*void remove_piece(File file, Rank rank, piece_type type, Color color);
        void remove_piece(const bitboard& piece, piece_type type, Color color);*/

        void add_piece(square position, piece_type type, int color);
        /*void add_piece(File file, Rank rank, piece_type type, Color color);
        void add_piece(const bitboard& piece, piece_type type, Color color);*/

        piece_type_with_color at(const square s) const;


        /*these needs to be updated after each move*/
        bitboard bitboards_[8];
        piece_type_with_color pieces_[SQUARE_NB];
        bool castling_rights_[4];
        int ply_;
        int side_;
        int en_p_square;

        /*these are constant*/
        bitboard pawnAttacks_[2][SQUARE_NB];
        bitboard knightAttacks_[SQUARE_NB];
        bitboard kingAttacks_[SQUARE_NB];
        bitboard bishopAttacks_[5248];
        bitboard rookAttacks_[102400];
        Magic bishopMagics_[SQUARE_NB];
        Magic rookMagics_[SQUARE_NB];

    private:
        void init_Knight_and_KingAttacks();
        void init_slide_attacks();
        void init_castling_rights();
        void init_pawn_attacks();

        bool is_attacked(const int& square, const int& color) const;
        void gen_non_pawn(std::vector<move::Move>& movelist, bitboard attacks, const int square_from) const;
        bitboard slider_attacks(const int from_square, const bitboard& occupied, const int offsets[4][2]) const;
        void init_magics(const int square, Magic* table, const bitboard& magic_number, const int offsets[4][2]);

        void do_move(move::Move m);
        void do_castling(square src, square dst);
    };
}
