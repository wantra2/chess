#include "board/board.hh"

#include <iostream>

namespace board
{
    Board::Board()
    {
        generate_board();
        ply_ = 0;
    }

    constexpr void Board::generate_board()
    {
        bitboards_[(int)Color::WHITE] = 0x000000000000FFFF; //WHITES
        bitboards_[(int)Color::BLACK] = 0xFFFF000000000000; //BLACKS
        bitboards_[piece_type::PAWN] = 0x00FF00000000FF00; //PAWNS
        bitboards_[piece_type::KNIGHT] = 0x4200000000000042; //KNIGHTS
        bitboards_[piece_type::BISHOP] = 0x2400000000000024; //BISHOPS
        bitboards_[piece_type::ROOK] = 0x8100000000000081; //ROOKS
        bitboards_[piece_type::QUEEN] = 0x0800000000000008; //QUEENS
        bitboards_[piece_type::KING] = 0x1000000000000010; //KINGS
    }

    Board::bitboard& Board::get_bitboard(piece_type type)
    {
        return bitboards_[(int)type];
    }

    Board::bitboard& Board::get_bitboard(Color color)
    {
        return bitboards_[(int)color];
    }

    std::vector<move::Move> bitboard_to_moves(bitboard b)
    {
        if (not b)
            return 0;
        bitboard bit = 1;
        std::vector<move::Move> moves;
        int i = 0;
        while (i < 64)
        {
            if (b & bit)
                moves.push_back(i);
            bit <<= 1;
            ++i;
        }
    }

}
