#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"


TEST(movegen_pawn, starting_white_pawns_moves)
{
    board::Board boardd;
    std::vector<move::Move> movelist;
    boardd.gen_pawn_moves_quiet(movelist, board::WHITE);
    ASSERT_EQ(16, movelist.size());
    for (auto m : movelist)
    {
        ASSERT_EQ(move::is_castling(m), false);
        ASSERT_EQ(move::is_promotion(m), false);
    }
}

TEST(movegen_pawn, promotion_white_pawns_moves)
{
    board::Board boardd;
    boardd.bitboards_[(int)board::Color::BLACK] = 0x0;
    boardd.bitboards_[(int)board::Color::WHITE] = 0x00FF000000000000;
    boardd.bitboards_[(int)board::piece_type::PAWN] = 0x00FF000000000000;
    std::vector<move::Move> movelist;
    boardd.gen_pawn_moves_noisy(movelist, board::WHITE);
    ASSERT_EQ(32, movelist.size());
    for (auto m : movelist)
    {
        ASSERT_EQ(move::mv_type(m), move::PROMOTION);
        ASSERT_EQ(move::is_castling(m), false);
    }
}

TEST(movegen_pawn, all)
{
    board::Board b;
    b.add_piece(board::A3, board::PAWN, board::BLACK);
    b.add_piece(board::B3, board::PAWN, board::BLACK);
    b.add_piece(board::C3, board::PAWN, board::BLACK);
    b.add_piece(board::D3, board::PAWN, board::BLACK);
    b.add_piece(board::E3, board::PAWN, board::BLACK);
    b.add_piece(board::F3, board::PAWN, board::BLACK);
    b.add_piece(board::G3, board::PAWN, board::BLACK);
    b.add_piece(board::H3, board::PAWN, board::BLACK);
    std::vector<move::Move> ml;
    b.gen_pawn_moves_noisy(ml, board::WHITE);
    ASSERT_EQ(14, ml.size());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
