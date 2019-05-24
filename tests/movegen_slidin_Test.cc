#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"


TEST(movegen_sliding, starting_white_pawns_moves)
{
    board::Board boardd;
    std::vector<move::Move> movelist;
    boardd.gen_queen_bishop_moves(movelist, boardd.bitboards_[0] | boardd.bitboards_[1], 0, 0xffffffffffffffff);
    ASSERT_EQ(movelist.size(), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
