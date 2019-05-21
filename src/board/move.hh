#pragma once

#include <cstdint>

#include "board/position.hh"
#include "board/piece-type.hh"

namespace move
{
    using Move = uint16_t;
    board::Position move_src(Move move);
    board::Position move_dst(Move move);
    bool is_capture(Move move);
    bool is_castling(Move move);
    bool is_promotion(Move move);
    board::piece_type promotion_type(Move move);
}
