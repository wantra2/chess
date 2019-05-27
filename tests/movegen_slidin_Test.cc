#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"


TEST(movegen_sliding, starting_position_queens_no_blockers)
{
    board::Board boardd;
    std::vector<move::Move> movelist;
    boardd.gen_queen_bishop_moves(movelist, boardd.bitboards_[board::QUEEN], 0ull, 0xffffffffffffffff);
    boardd.gen_queen_rook_moves(movelist, boardd.bitboards_[board::QUEEN], 0ull, 0xffffffffffffffff);
    ASSERT_EQ(movelist.size(), 42);
}

TEST(movegen_sliding, white_rooks_starting_pos_)
{
    board::Board boardd;
    std::vector<move::Move> movelist;
    boardd.gen_queen_rook_moves(movelist, boardd.bitboards_[board::ROOK]&boardd.bitboards_[0], boardd.bitboards_[0]|boardd.bitboards_[1], 0xffffffffffff0000);
    ASSERT_EQ(movelist.size(), 0);
}

TEST(movegen_sliding, white_bishop_pieces_starting_pos)
{
    board::Board b;
    std::vector<move::Move> movelist;
    b.gen_queen_bishop_moves(movelist, b.bitboards_[board::WHITE]&b.bitboards_[board::BISHOP], b.bitboards_[board::WHITE]|b.bitboards_[board::BLACK], 0xffffffffffff0000);
    ASSERT_EQ(movelist.size(), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
