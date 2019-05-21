#pragma once

#include <cstdint>

#include "board/color.hh"

namespace board
{
    class Board
    {
    public:
        Board();
        ~Board() = default;

        void generate_board();

    private:
        int_fast64_t bitboards_[];
        int turn_;
        //FIXME: NEED TIMES

    }
}
