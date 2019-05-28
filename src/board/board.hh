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
        NO_CASTLING,     //00
        SMALL,           //01
        BIG,             //10
        BOTH = BIG|SMALL //11
    };

    enum castlings_sq_index
    {
        index_00,
        index_000
    };

    struct State
    {
        piece_type captured;
    };

    class Board
    {
    public:

        Board();
        ~Board() = default;

        void gen_pawn_moves(std::vector<move::Move>&, const int& color) const;
        void gen_KnightMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets) const;
        void gen_KingMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets) const;
        void gen_queen_bishop_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets) const;
        void gen_queen_rook_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets) const;
        void gen_castlings(std::vector<move::Move>& movelist, const bitboard& occupied, const int& color) const;

        void remove_piece(const square& position, const piece_type& type, const int& color);
        void add_piece(const square& position, const piece_type& type, const int& color);

        piece_type_with_color at(const square& s) const;
        void do_move(const move::Move& m);
        void undo_move(const move::Move& m);

        /*these needs to be updated after each move*/
        bitboard bitboards_[8];
        piece_type_with_color pieces_[SQUARE_NB];
        int castling_rights_[2];
        int ply_;
        int side_;
        square en_p_square;
        std::vector<State> states_;

        /*these are constant*/
        bitboard castlings_sq[2][2];
        bitboard pawnAttacks_[2][SQUARE_NB];
        bitboard knightAttacks_[SQUARE_NB];
        bitboard kingAttacks_[SQUARE_NB];
        bitboard bishopAttacks_[5248];
        bitboard rookAttacks_[102400];
        Magic bishopMagics_[SQUARE_NB];
        Magic rookMagics_[SQUARE_NB];

    private:
        void generate_board();
        void generate_pieces();
        void init_Knight_and_KingAttacks();
        void init_slide_attacks();
        void init_castling();
        void init_pawn_attacks();

        bool is_attacked(const square& square, const int& color) const;
        void gen_non_pawn(std::vector<move::Move>& movelist, bitboard attacks, const square& square_from) const;
        bitboard slider_attacks(const square& from_square, const bitboard& occupied, const int offsets[4][2]) const;
        void init_magics(const square& square, Magic* table, const bitboard& magic_number, const int offsets[4][2]);

        void do_castling(const square& src, const square& dst);
        void undo_castling(const square& src, const square& dst);
    };
}
