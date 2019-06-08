#include <gtest/gtest.h>

#include "utils/misc.hh"
#include "board/board.hh"

TEST(gen_pawn_moves, move_right_at_bounds)
{
    std::string fen = "5r1k/pN2n2p/6p1/2P5/b7/P4P2/1b3P1P/1R1R2K1 w - - 1 27";
    std::vector<move::Move> move_list;
    board::Board board(fen);
    board::init_internal_bitboards(board::int_bb);
    board.gen_all(move_list);
    for (auto& move : move_list)
        ASSERT_NE("h2a4", utils::move_to_uci(move));
}