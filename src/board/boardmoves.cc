#include "board/board.hh"

namespace board
{
    void Board::remove_piece(square position, piece_type type, int color)
    {
        bitboards_[type] ^= (0x1 << position);
        bitboards_[color] ^= (0x1 << position);
        pieces_[position] = board::piece_type_with_color::VOID;
    }
/*
    void Board::remove_piece(File file, Rank rank, piece_type type, Color color)
    {
        bitboards_[type] ^= (0x1 << to_square((int)rank, (int)file));
        bitboards_[(int)color] ^= (0x1 << to_square((int)rank, (int)file));
    }

    void Board::remove_piece(const bitboard& piece, piece_type type, Color color)
    {
        bitboards_[type] ^= piece;
        bitboards_[(int)color] ^= piece;
    }*/

    void Board::add_piece(square position, piece_type type, int color)
    {
        bitboards_[type] |= (0x1 << position);
        bitboards_[(int)color] |= (0x1 << position);
        pieces_[position] = (piece_type_with_color)(type - 1 + color * 6);
    }
/*
    void Board::add_piece(File file, Rank rank, piece_type type, Color color)
    {
        bitboards_[type] |= (0x1 << to_square((int)rank, (int)file));
        bitboards_[(int)color] |= (0x1 << to_square((int)rank, (int)file));
    }

    void Board::add_piece(const bitboard& piece, piece_type type, Color color)
    {
        bitboards_[type] |= piece;
        bitboards_[(int)color] |= piece;
    }*/

    piece_type_with_color Board::at(const square s) const
    {
        return pieces_[s];
    }

    void Board::do_move(move::Move m)
    {
        square dst = move::move_dst(m);
        square src = move::move_src(m);
        piece_type_with_color eventually_captured_piece = pieces_[dst];
        if (move::mv_type(m) == move::MoveType::EN_PASSANT)
        {
            if (side_ == piece_type::WHITE)
                eventually_captured_piece = board::piece_type_with_color::BLACK_PAWN;
            else
                eventually_captured_piece = board::piece_type_with_color::WHITE_PAWN;
        }
        if (move::mv_type(m) == move::MoveType::CASTLING)
            do_castling(src, dst);
        side_ = not side_;
        ++ply_;
    }
}
