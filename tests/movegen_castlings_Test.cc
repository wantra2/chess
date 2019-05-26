#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"


TEST(movegen_castlings, starting_position_catsling)
{
    board::Board boardd;
    std::vector<move::Move> movelist;
    boardd.gen_castlings(movelist, boardd.bitboards_[0]|boardd.bitboards_[1], board::WHITE);
    boardd.gen_castlings(movelist, boardd.bitboards_[0]|boardd.bitboards_[1], board::BLACK);
    ASSERT_EQ(movelist.size(), 0);
}

TEST(movegen_castlings, starting_position_queen_side)
{
    board::Board boardd;
    std::vector<move::Move> movelist;
    boardd.remove_piece(board::B1, board::KNIGHT, board::Color::WHITE);
    boardd.remove_piece(board::C1, board::BISHOP, board::Color::WHITE);
    boardd.remove_piece(board::D1, board::QUEEN, board::Color::WHITE);
    boardd.gen_castlings(movelist, boardd.bitboards_[0]|boardd.bitboards_[1], board::WHITE);
    boardd.gen_castlings(movelist, boardd.bitboards_[0]|boardd.bitboards_[1], board::BLACK);
    ASSERT_EQ(movelist.size(), 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}