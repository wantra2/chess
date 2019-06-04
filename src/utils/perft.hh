#pragma once

#include "board/board.hh"

#include <string>

namespace utils
{
    int perft_scnd(board::Board& board, int depth);
    int perft(std::string perft);
}
