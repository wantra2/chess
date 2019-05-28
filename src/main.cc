#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"
#include "utils/misc.hh"

int main()
{
    board::Board b;
    utils::pretty_print(b);
    std::cout << "---------------\n";
    b.do_move(move::create_move(board::E2, board::E4));
    utils::pretty_print(b);
    std::cout << "---------------\n";
    b.do_move(move::create_move(board::E7, board::E5));
    utils::pretty_print(b);
    std::cout << "---------------\n";
    b.do_move(move::create_move(board::D2, board::D4));
    utils::pretty_print(b);
    return 0;
}
