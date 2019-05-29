#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"
#include "utils/misc.hh"
#include "utils/options.hh"

using namespace board;

int main(int argc, char* argv[])
{
    Board b;
    utils::pretty_print(b);
    std::cout << "\n\n";
    b.do_move(move::create_move(G1, H3));
    utils::pretty_print(b);
    std::cout << "\n\n";
    b.do_move(move::create_move(E7, E5));
    utils::pretty_print(b);
    std::cout << "\n\n";
    b.do_move(move::create_move(E2, E4));
    utils::pretty_print(b);
    std::cout << "\n\n";
    b.do_move(move::create_move(A7, A5));
    utils::pretty_print(b);
    std::cout << "\n\n";
    b.do_move(move::create_move(F1, E2));
    utils::pretty_print(b);
    std::cout << "\n\n";
    b.do_move(move::create_move(H7, H6));
    utils::pretty_print(b);
    std::cout << "\n\n";
    b.do_move(move::create_move(E1, G1, move::CASTLING));
    utils::pretty_print(b);
    std::cout << "\n\n";
    std::cout << b.at(D1);
    std::cout << "\n" << std::hex << (b.bitboards_[QUEEN]&b.bitboards_[WHITE]);
    b.undo_move(move::create_move(E1, G1, move::CASTLING));
    utils::pretty_print(b);
    return 0;
}
