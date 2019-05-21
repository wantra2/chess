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
        int ply_;
        int_fast64_t bitboards_[8];
        //FIXME: NEED TIMES

    };
}
