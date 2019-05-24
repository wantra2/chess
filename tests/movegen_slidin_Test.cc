#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"


TEST(movegen_sliding, starting_position_queen)
{
    board::Board boardd;
    std::vector<move::Move> movelist;
    boardd.gen_queen_bishop_moves(movelist, boardd.get_bitboard(board::QUEEN), 0ull, 0xffffffffffffffff);
    boardd.gen_queen_rook_moves(movelist, boardd.get_bitboard(board::QUEEN), 0ull, 0xffffffffffffffff);
    ASSERT_EQ(movelist.size(), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
