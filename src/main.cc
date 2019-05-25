#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"
#include "utils/misc.hh"

using namespace board;

int main()
{
    board::Board boardd;
    boardd.bitboards_[(int)board::Color::BLACK] = 0x0000000000010000;
    boardd.bitboards_[(int)board::Color::WHITE] = 0x000000000000FF00;
    boardd.bitboards_[(int)board::piece_type::PAWN] = 0x000800000001FF00;
    utils::pretty_print(boardd);
    std::vector<move::Move> movelist;
    boardd.gen_pawn_moves(movelist, board::Color::WHITE);
    std::cout << "COUNT: " << movelist.size() << '\n';
    for (auto m : movelist)
    {
        std::cout << "TYPE: " << move::mv_type(m) << '\n';
    }
}
