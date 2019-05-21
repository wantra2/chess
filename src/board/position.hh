#pragma once

#include <utility>

#include "utils/utype.hh"

namespace board
{
    /* The file enum represent the colomns
     * on the board */
    enum class File
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
    };

    /* The rank enum represent the lines
     * on the board */
    enum class Rank
    {
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
    };

    enum square
    {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8,
        SQUARE_NB = 64
    };


    /* Position represent a coordinate on the board */
    class Position final
    {
    public:
        Position(File file, Rank rank);

        File file_get() const;
        Rank rank_get() const;

        bool operator==(const Position& pos) const;
        bool operator!=(const Position& pos) const;

    private:
        File file_;
        Rank rank_;
    };

} // namespace board

#include "position.hxx"
