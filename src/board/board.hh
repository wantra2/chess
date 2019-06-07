#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

#include "move/move.hh"
#include "board/color.hh"
#include "board/piece-type.hh"
#include "board/bitboard.hh"
#include "listener/listener.hh"
#include "board/hash_keys.hh"


namespace board
{
    enum castlings
    {
        NO_CASTLING,     //00
        SMALL,           //01
        BIG,             //10
        BOTH = BIG|SMALL //11
    };

    struct State
    {
        piece_type captured;
        int castling_rights[2];
        square en_p_square;
    };

    extern std::vector<State> gamestates;

    class Board
    {
    public:

        Board(std::string& fen);
        ~Board() = default;

        void set_listeners(std::vector<listener::Listener*> listeners)
        {listeners_ = listeners;}

        void gen_pawn_moves_quiet(std::vector<move::Move>&, const int& color) const;
        void gen_pawn_moves_noisy(std::vector<move::Move>&, const int& color) const;
        void gen_KnightMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets) const;
        void gen_KingMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets) const;
        void gen_queen_bishop_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets) const;
        void gen_queen_rook_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets) const;
        void gen_castlings(std::vector<move::Move>& movelist, const bitboard& occupied, const int& color) const;
        void gen_all(std::vector<move::Move>& movelist);
        void gen_captures(std::vector<move::Move>& movelist);

        void remove_piece(const square& position, const piece_type& type, const int& color);
        void add_piece(const square& position, const piece_type& type, const int& color);

        piece_type_with_color at(const square& s) const;

        void do_move(const move::Move& m);
        void undo_move(const move::Move& m);
        void do_move_null();
        void undo_move_null();

        void do_castling(const square& src, const square& dst);
        void undo_castling(const square& src, const square& dst);

        bool is_attacked(const square& square, const int& color) const;

        bool is_finished() const;

//        move::Move pv_[16]; //16 = max depth
//        uint64_t key_;
        State state_; //updated in do_move/undo_move
        bitboard bitboards_[8]; //updated in addpiece/removepiece
        piece_type_with_color pieces_[SQUARE_NB]; //updated in addpiece/removepiece
        int side_; //updated manually
        int ply_; //updated manually (not used for 50 rule!)
        int material_[2];
        int position_[2];
        std::unordered_map<uint64_t, move::Move> table_;
        uint64_t hash_;

    private:
        std::vector<listener::Listener*> listeners_;
        void gen_non_pawn(std::vector<move::Move>& movelist, bitboard attacks, const square& square_from) const;
    };
}
