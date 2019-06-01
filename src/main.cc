#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <cstring>

#include "move/move.hh"
#include "board/board.hh"
#include "board/bitboard.hh"
#include "board/color.hh"
#include "utils/misc.hh"
#include "utils/options.hh"
#include "board/board-adapter.hh"
#include "ai/uci.hh"
#include "ai/minmax.hh"

using namespace board;

void uci_loop()
{
    init_internal_bitboards();
    ai::init("ThugChess");
    while (1)
    {
        std::string str = ai::get_board();
        char* input = &str[0u];
        char* token = std::strtok(input, " ");
        token = std::strtok(NULL, " ");
        std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
        if (strcmp(token, "startpos") == 0)
        {
            token = std::strtok(NULL, " ");
            if (token)
                token = std::strtok(NULL, " ");
        }
        else
        {
            token = std::strtok(NULL, "m");
            fen = token;
            std::strtok(NULL, " ");
            token = std::strtok(NULL, " ");
        }

        Board b(fen);
        while (token)
        {
            move::Move m = utils::uci_to_move(std::string(token), b);
            b.do_move(m);
            token = std::strtok(NULL, " ");
        }
        ai::search_infos infos{0, 5, 0};
        ai::search(b, infos);
        ai::play_move(utils::move_to_uci(infos.best_move));
    }
}

int main(int argc, char* argv[])
{
    std::vector<std::string> listeners;
    auto vm = utils::parse_options(argc, argv);
    if (!vm)
        return 1;
    if (vm->count("pgn"))
    {
        std::cout << "the pgn file is: " << (*vm)["pgn"].as<std::string>() << '\n';
        return 0;
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
        return 0;
    }

    uci_loop();
    //call uci_loop if no arguments are given
    return 0;
}
