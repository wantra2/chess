#include "board/board.hh"

namespace board
{
    Board::Board()
    {
        bitboard[8] = { 0 };
        generate_board();
        turn = 0;
    }

    void Board::generate_board()
    {
        bitboard[0] = 0x000000000000FFFF; //WHITES
        bitboard[1] = 0xFFFF000000000000; //BLACKS
        bitboard[2] = 0x00FF00000000FF00; //PAWNS
        bitboard[3] = 0x4200000000000042; //KNIGHTS
        bitboard[4] = 0x2400000000000024; //BISHOPS
        bitboard[5] = 0x8100000000000081; //ROOKS
        bitboard[6] = 0x0800000000000008; //QUEENS
        bitboard[7] = 0x1000000000000010; //KINGS
    }
}
