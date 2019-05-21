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
        bitboards_[0] = 0x000000000000FFFF; //WHITES
        bitboards_[1] = 0xFFFF000000000000; //BLACKS
        bitboards_[2] = 0x00FF00000000FF00; //PAWNS
        bitboards_[3] = 0x4200000000000042; //KNIGHTS
        bitboards_[4] = 0x2400000000000024; //BISHOPS
        bitboards_[5] = 0x8100000000000081; //ROOKS
        bitboards_[6] = 0x0800000000000008; //QUEENS
        bitboards_[7] = 0x1000000000000010; //KINGS
    }

    Board::bitboard& Board::get_bitboard(piece_type type)
    {
        return bitboards_[(int)type];
    }

    Board::bitboard& Board::get_bitboard(Color color)
    {
        return bitboards_[(int)color];
    }
}
