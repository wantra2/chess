#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"


TEST(movegen_sliding, starting_position_white_queens_bishop_no_blockers)
{
    board::Board b;
    std::vector<move::Move> ml;
    b.gen_queen_bishop_moves(ml, board::WHITE, 0ull, 0x000000000000000800);
    b.gen_queen_rook_moves(ml, board::WHITE, 0ull, 0x000000000000000800);
    ASSERT_EQ(2, ml.size());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
