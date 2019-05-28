#include "board/board.hh"

namespace board
{
    void Board::remove_piece(square position, piece_type type, int color)
    {
        bitboards_[type] ^= (0x1 << position);
        bitboards_[color] ^= (0x1 << position);
        pieces_[position] = board::piece_type_with_color::VOID;
    }

    void Board::add_piece(square position, piece_type type, int color)
    {
        bitboards_[type] |= (0x1 << position);
        bitboards_[color] |= (0x1 << position);
        pieces_[position] = (piece_type_with_color)(type - 1 + color * 6);
    }

    piece_type_with_color Board::at(const square s) const
    {
        return pieces_[s];
    }

    void Board::do_move(move::Move m)
    {
        const int direction = side_ == WHITE ? 8 : -8;
        const square dst = move::move_dst(m);
        const square src = move::move_src(m);
        const move::MoveType movetype = move::mv_type(m);
        square cap_sq = dst;
        int captured_piece = pieces_[dst];

        if (movetype == move::MoveType::EN_PASSANT)
        {
            captured_piece = WHITE_PAWN + (6 * side_);
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


    }
}
