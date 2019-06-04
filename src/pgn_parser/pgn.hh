#pragma once

#include <vector>

#include "board/pgn-move.hh"
#include "move/move.hh"

namespace pgn_parser
{
    std::vector<move::Move> get_moves(std::vector<board::PgnMove>& pgn_moves);

    int play(std::vector<move::Move> moves, std::vector<std::string> listeners);

    int pgn_play(const std::string& file, std::vector<std::string> listeners);

}
