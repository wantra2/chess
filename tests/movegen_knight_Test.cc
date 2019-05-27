#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"


TEST(movegen_knight, starting_white_knights_moves)
{
  board::Board boardd;
  std::vector<move::Move> movelist;
  boardd.gen_KnightMoves(movelist, board::WHITE, 0xFFFFFFFFFFFFFFFF);
  ASSERT_EQ(6, movelist.size());
  for (auto m : movelist)
  {
    ASSERT_EQ(move::mv_type(m), move::NORMAL);
    ASSERT_EQ(move::is_castling(m), false);
    ASSERT_EQ(move::is_passant(m), false);
    ASSERT_EQ(move::is_promotion(m), false);
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}