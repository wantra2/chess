#include "board/board.hh"

namespace board
{
    void Board::remove_piece(square position, piece_type type, Color color)
    {
        bitboards_[type] ^= (0x1 << position);
        bitboards_[(int)color] ^= (0x1 << position);
    }

    void Board::remove_piece(File file, Rank rank, piece_type type, Color color)
    {
        bitboards_[type] ^= (0x1 << to_square((int)rank, (int)file));
        bitboards_[(int)color] ^= (0x1 << to_square((int)rank, (int)file));
    }

    void Board::remove_piece(const bitboard& piece, piece_type type, Color color)
    {
        bitboards_[type] ^= piece;
        bitboards_[(int)color] ^= piece;
    }

    void Board::add_piece(square position, piece_type type, Color color)
    {
        bitboards_[type] |= (0x1 << position);
        bitboards_[(int)color] |= (0x1 << position);
    }

    void Board::add_piece(File file, Rank rank, piece_type type, Color color)
    {
        bitboards_[type] |= (0x1 << to_square((int)rank, (int)file));
        bitboards_[(int)color] |= (0x1 << to_square((int)rank, (int)file));
    }

    void Board::add_piece(const bitboard& piece, piece_type type, Color color)
    {
        bitboards_[type] |= piece;
        bitboards_[(int)color] |= piece;
    }
}
