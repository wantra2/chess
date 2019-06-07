#include <gtest/gtest.h>
#include <iostream>
#include "board/board.hh"
#include "utils/misc.hh"

TEST(uci_to_move, a1a5)
{
    std::string fen = "2kr1bnr/pp5p/3p2p1/3Np3/2PpP3/3P1p2/PPQB1PqP/R4RK1 w - - 0 16";
    board::Board board(fen);
    auto move = utils::uci_to_move("a1a5", fen);
    ASSERT_EQ(move::move_src(move), board::A1);
    ASSERT_EQ(move::move_dst(move), board::A5);
}