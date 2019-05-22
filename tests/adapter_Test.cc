#include <gtest/gtest.h>
#include <iostream>

#include "board/board.hh"
#include "board/board-adapter.hh"

TEST(board, rooks)
{
    board::Board act = board::Board();
    auto adapt = board::BoardAdapter(act);
    ASSERT_EQ((*adapt[board::Position(board::File::A, board::Rank::ONE)]).first
              , board::PieceType::ROOK);
    ASSERT_EQ((*adapt[board::Position(board::File::H, board::Rank::ONE)]).first
              , board::PieceType::ROOK);
    ASSERT_EQ((*adapt[board::Position(board::File::A, board::Rank::EIGHT)]).first
              , board::PieceType::ROOK);
    ASSERT_EQ((*adapt[board::Position(board::File::H, board::Rank::EIGHT)]).first
              , board::PieceType::ROOK);
}

TEST(board, pawns)
{
    board::Board act = board::Board();
    auto adapt = board::BoardAdapter(act);
    ASSERT_EQ((*adapt[board::Position(board::File::A, board::Rank::TWO)]).first
              , board::PieceType::PAWN);
    ASSERT_EQ((*adapt[board::Position(board::File::H, board::Rank::TWO)]).first
              , board::PieceType::PAWN);
    ASSERT_EQ((*adapt[board::Position(board::File::A, board::Rank::SEVEN)]).first
              , board::PieceType::PAWN);
    ASSERT_EQ((*adapt[board::Position(board::File::H, board::Rank::SEVEN)]).first
              , board::PieceType::PAWN);
}

TEST(board, KNGHT)
{
    board::Board act = board::Board();
    auto adapt = board::BoardAdapter(act);
    ASSERT_EQ((*adapt[board::Position(board::File::B, board::Rank::ONE)]).first
              , board::PieceType::KNIGHT);
    ASSERT_EQ((*adapt[board::Position(board::File::G, board::Rank::ONE)]).first
              , board::PieceType::KNIGHT);
    ASSERT_EQ((*adapt[board::Position(board::File::B, board::Rank::EIGHT)]).first
              , board::PieceType::KNIGHT);
    ASSERT_EQ((*adapt[board::Position(board::File::G, board::Rank::EIGHT)]).first
              , board::PieceType::KNIGHT);
}

TEST(board, BISHOP)
{
    board::Board act = board::Board();
    auto adapt = board::BoardAdapter(act);
    ASSERT_EQ((*adapt[board::Position(board::File::C, board::Rank::ONE)]).first
              , board::PieceType::BISHOP);
    ASSERT_EQ((*adapt[board::Position(board::File::F, board::Rank::ONE)]).first
              , board::PieceType::BISHOP);
    ASSERT_EQ((*adapt[board::Position(board::File::C, board::Rank::EIGHT)]).first
              , board::PieceType::BISHOP);
    ASSERT_EQ((*adapt[board::Position(board::File::F, board::Rank::EIGHT)]).first
              , board::PieceType::BISHOP);
}

TEST(board, QUEEN)
{
    board::Board act = board::Board();
    auto adapt = board::BoardAdapter(act);
    ASSERT_EQ((*adapt[board::Position(board::File::D, board::Rank::ONE)]).first
              , board::PieceType::QUEEN);
    ASSERT_EQ((*adapt[board::Position(board::File::D, board::Rank::EIGHT)]).first
              , board::PieceType::QUEEN);
}

TEST(board, whites)
{
    board::Board act = board::Board();
    auto adapt = board::BoardAdapter(act);
    ASSERT_EQ((*adapt[board::Position(board::File::A, board::Rank::ONE)]).second
              , board::Color::WHITE);
    ASSERT_EQ((*adapt[board::Position(board::File::H, board::Rank::ONE)]).second
              , board::Color::WHITE);
    ASSERT_EQ((*adapt[board::Position(board::File::A, board::Rank::TWO)]).second
              , board::Color::WHITE);
    ASSERT_EQ((*adapt[board::Position(board::File::H, board::Rank::TWO)]).second
              , board::Color::WHITE);
}

TEST(board, blacks)
{
    board::Board act = board::Board();
    auto adapt = board::BoardAdapter(act);
    ASSERT_EQ((*adapt[board::Position(board::File::A, board::Rank::EIGHT)]).second
              , board::Color::BLACK);
    ASSERT_EQ((*adapt[board::Position(board::File::H, board::Rank::EIGHT)]).second
              , board::Color::BLACK);
    ASSERT_EQ((*adapt[board::Position(board::File::A, board::Rank::SEVEN)]).second
              , board::Color::BLACK);
    ASSERT_EQ((*adapt[board::Position(board::File::H, board::Rank::SEVEN)]).second
              , board::Color::BLACK);
}
