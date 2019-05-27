#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"

//This testsuite does not check for legality, it only ensure correct encoding of moves

TEST(move, basic)
{
  move::Move m = move::create_move(board::A2, board::A4, board::KNIGHT, move::NORMAL);
  ASSERT_EQ(move::mv_type(m), move::NORMAL);
  ASSERT_EQ(move::move_src(m), board::A2);
  ASSERT_EQ(move::move_dst(m), board::A4);
  ASSERT_EQ(move::is_castling(m), false);
  ASSERT_EQ(move::is_passant(m), false);
  ASSERT_EQ(move::is_promotion(m), false);
  ASSERT_EQ(move::mv_type(m), move::MoveType::NORMAL);
}

TEST(move, promo_knight)
{
  move::Move m = move::create_move(board::A1, board::H8, board::KNIGHT, move::PROMOTION);
  ASSERT_EQ(move::mv_type(m), move::PROMOTION);
  ASSERT_EQ(move::move_src(m), board::A1);
  ASSERT_EQ(move::move_dst(m), board::H8);
  ASSERT_EQ(move::is_castling(m), false);
  ASSERT_EQ(move::is_passant(m), false);
  ASSERT_EQ(move::is_promotion(m), true);
  ASSERT_EQ(move::promotion_type(m), board::KNIGHT);
}

TEST(move, castling)
{
  move::Move m = move::create_move(board::A1, board::H8, move::CASTLING);
  ASSERT_EQ(move::mv_type(m), move::CASTLING);
  ASSERT_EQ(move::move_src(m), board::A1);
  ASSERT_EQ(move::move_dst(m), board::H8);
  ASSERT_EQ(move::is_castling(m), true);
  ASSERT_EQ(move::is_passant(m), false);
  ASSERT_EQ(move::is_promotion(m), false);
}

TEST(move, en_passant)
{
  move::Move m = move::create_move(board::A1, board::H8, board::KNIGHT, move::EN_PASSANT);
  ASSERT_EQ(move::mv_type(m), move::EN_PASSANT);
  ASSERT_EQ(move::move_src(m), board::A1);
  ASSERT_EQ(move::move_dst(m), board::H8);
  ASSERT_EQ(move::is_castling(m), false);
  ASSERT_EQ(move::is_passant(m), true);
  ASSERT_EQ(move::is_promotion(m), false);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
