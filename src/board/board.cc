#include "board/board.hh"

namespace board
{
    Board::Board()
    {
        bitboard_[8] = { 0 };
        generate_board();
        turn_ = 0;
    }

    void Board::generate_board()
    {
        bitboard_[0] = 0x000000000000FFFF; //WHITES
        bitboard_[1] = 0xFFFF000000000000; //BLACKS
        bitboard_[2] = 0x00FF00000000FF00; //PAWNS
        bitboard_[3] = 0x4200000000000042; //KNIGHTS
        bitboard_[4] = 0x2400000000000024; //BISHOPS
        bitboard_[5] = 0x8100000000000081; //ROOKS
        bitboard_[6] = 0x0800000000000008; //QUEENS
        bitboard_[7] = 0x1000000000000010; //KINGS
    }
}
