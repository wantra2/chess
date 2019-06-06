#include <gtest/gtest.h>

#include "board/board.hh"

TEST(is_attacked, king)
{
    board::init_internal_bitboards(board::int_bb);
    std::string fen = "rnbqk1nr/pppp1ppp/4p3/2b5/8/N6N/PPPPPPPP/R1BQKB1R w KQkq - 2 3";
    board::Board board(fen);
    ASSERT_TRUE(board.is_attacked(board::F2, board::WHITE));
    ASSERT_FALSE(board.is_attacked(board::G1, board::WHITE));
}
