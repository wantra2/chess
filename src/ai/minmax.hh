#pragma once

#include "board/board.hh"
#include "ai/eval.hh"

namespace ai
{
    int alphabetamax(board::Board& b, int alpha, int beta, int depth);
    int alphabetamin(board::Board& b, int alpha, int beta, int depth);
}