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
    b.do_move(move::create_move(board::E2, board::E4));
    b.do_move(move::create_move(board::D7, board::D5));
    b.do_move(move::create_move(board::E4, board::D5));
    utils::pretty_print(b);
    b.undo_move(move::create_move(board::E4, board::D5));
    utils::pretty_print(b);
    return 0;
}
