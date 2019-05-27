#include <gtest/gtest.h>
#include <iostream>
#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"
#include "utils/misc.hh"

using namespace board;

int main()
{
    board::Board boardd;
    std::vector<move::Move> movelist;
    boardd.gen_queen_rook_moves(movelist, boardd.bitboards_[board::ROOK]&boardd.bitboards_[0], boardd.bitboards_[0]|boardd.bitboards_[1], 0xffffffffffffffff);
    for (auto m : movelist)
    {
        std::cout << move::move_src(m) << "-"<< move::move_dst(m)<<'\n';
    }
}
