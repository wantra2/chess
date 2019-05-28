#include "board/board.hh"

namespace board
{
    void Board::remove_piece(const square& position, const piece_type& type, const int& color)
    {
        bitboards_[type] ^= (1ull << position);
        bitboards_[color] ^= (1ull << position);
        pieces_[position] = board::piece_type_with_color::VOID;
    }

    void Board::add_piece(const square& position, const piece_type& type, const int& color)
    {
        bitboards_[type] |= (1ull << position);
        bitboards_[color] |= (1ull << position);
        pieces_[position] = (piece_type_with_color)(type - 1 + color * 6);
    }

    piece_type_with_color Board::at(const square& s) const
    {
        return pieces_[s];
    }

    void Board::do_move(const move::Move& m)
    {
        states_.push_back(State{NONE});
        const int direction = side_ == WHITE ? 8 : -8;
        const square dst = move::move_dst(m);
        const square src = move::move_src(m);
        const move::MoveType movetype = move::mv_type(m);
        square cap_sq = dst;
        piece_type_with_color captured_piece = pieces_[dst];

        if (movetype == move::MoveType::EN_PASSANT)
        {
            captured_piece = (piece_type_with_color)(WHITE_PAWN + (6 * side_));
            cap_sq = (square)(dst - direction);
        }

        if (movetype == move::MoveType::CASTLING)
        {
            do_castling(src, dst);
            captured_piece = VOID;
            castling_rights_[side_] = NO_CASTLING;
        }

        if (captured_piece != VOID)
            remove_piece(cap_sq, type(captured_piece), !side_);

        if (en_p_square != SQUARE_NB)
            en_p_square = SQUARE_NB;


        piece_type src_pt = type(pieces_[src]);
        if (src_pt == piece_type::KING)
            castling_rights_[side_] = NO_CASTLING;
        else
        {
            const square a1 = side_ == WHITE ? A1 : A8;
            const square h1 = side_ == WHITE ? H1 : H8;
            if (src == a1)
                castling_rights_[side_] &= ~2;
            if (src == h1)
                castling_rights_[side_] &= ~1;
        }

        remove_piece(src, src_pt, side_);
        add_piece(dst, src_pt, side_);

        const int pos = side_ == WHITE ? 16 : -16;
        if (src_pt == piece_type::PAWN)
        {
            if (dst == src + pos)
                en_p_square = (square)(src + direction);
            if (movetype == move::PROMOTION)
            {
                remove_piece(dst, src_pt, side_);
                add_piece(dst, move::promotion_type(m), side_);
            }
        }
        states_[states_.size()-1].captured = type(captured_piece);
        ++ply_;
        side_ = !side_;
    }

    void Board::undo_move(const move::Move& m)
    {
        side_ = !side_;
        const int direction = side_ == WHITE ? 8 : -8;
        const square src = move::move_src(m);
        const square dst = move::move_dst(m);
        const piece_type_with_color colored_pt = at(dst);
        piece_type pt = type(colored_pt);
        const move::MoveType movetype = move::mv_type(m);
        if (movetype == move::PROMOTION)
        {
            remove_piece(dst, pt, side_);
            add_piece(dst, PAWN, side_);
            pt = PAWN;
        }
        if (movetype == move::CASTLING)
        {
            undo_castling(src, dst);
        }
        else
        {
            remove_piece(dst, pt, side_);
            add_piece(src, pt, side_);
            if (states_[states_.size()-1].captured != NONE)
            {
                if (movetype == move::EN_PASSANT)
                    add_piece((square)(dst-direction), PAWN, !side_);
                else
                    add_piece(dst, states_[states_.size()-1].captured, !side_);
            }
        }
        --ply_;
        states_.pop_back();
    }
}
