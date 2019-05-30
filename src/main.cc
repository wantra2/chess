#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"
#include "utils/misc.hh"
#include "utils/options.hh"
#include "board/board-adapter.hh"

using namespace board;

int main(int argc, char* argv[])
{
    std::vector<std::string> listeners;
    auto vm = utils::parse_options(argc, argv);
    if (!vm)
        return 1;
    if (vm->count("pgn"))
    {
        std::cout << "the pgn file is: " << (*vm)["pgn"].as<std::string>() << '\n';
    }
    if (vm->count("listeners"))
    {
        std::cout << "the listener plugins are: \t";
        listeners = (*vm)["listeners"].as<std::vector<std::string>>();
        for (auto i : (*vm)["listeners"].as<std::vector<std::string>>())
            std::cout << i << '\t';
        std::cout << '\n';
    }
    if (vm->count("perft"))
    {
        std::cout << "the perft file is: " << (*vm)["perft"].as<std::string>() << '\n';
    }

    std::cout << "listeners list: ";
    for (auto i : listeners)
        std::cout << i << ", ";
    std::cout << " end of list\n";
    Board b;
    BoardAdapter ba(b, listeners);
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
    std::cout << "\n\n";
    b.do_move(move::create_move(E1, G1, move::CASTLING));
    utils::pretty_print(b);
    std::cout << "\n\n";
    return 0;
}
