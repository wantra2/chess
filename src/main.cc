#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"
#include "utils/misc.hh"
#include "utils/options.hh"


int main(int argc, char* argv[])
{
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
        for (auto i : (*vm)["listeners"].as<std::vector<std::string>>())
            std::cout << i << '\t';
        std::cout << '\n';
    }
    if (vm->count("perft"))
    {
        std::cout << "the perft file is: " << (*vm)["perft"].as<std::string>() << '\n';
    }

    board::Board b;
    b.do_move(move::create_move(board::E2, board::E4));
    b.do_move(move::create_move(board::D7, board::D5));
    b.do_move(move::create_move(board::E4, board::D5));
    utils::pretty_print(b);
    b.undo_move(move::create_move(board::E4, board::D5));
    utils::pretty_print(b);
    return 0;
}
