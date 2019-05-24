#pragma once

#include <utility>
#include <cstdint>
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

    enum
    {
        RANK_8 = 0xFF00000000000000ull,
        RANK_7 = 0x00FF000000000000ull,
        RANK_6 = 0x0000FF0000000000ull,
        RANK_5 = 0x000000FF00000000ull,
        RANK_4 = 0x00000000FF000000ull,
        RANK_3 = 0x0000000000FF0000ull,
        RANK_2 = 0x000000000000FF00ull,
        RANK_1 = 0x00000000000000FFull,

        FILE_A = 0x0101010101010101ull,
        FILE_B = 0x0202020202020202ull,
        FILE_C = 0x0404040404040404ull,
        FILE_D = 0x0808080808080808ull,
        FILE_E = 0x1010101010101010ull,
        FILE_F = 0x2020202020202020ull,
        FILE_G = 0x4040404040404040ull,
        FILE_H = 0x8080808080808080ull,
    };

    const uint64_t Files[8] = {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};
    const uint64_t Ranks[8] = {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};

    int rankof(const int square);

    int fileof(const int square);

    int to_square(const int rank, const int file);

    bool valid_coordinates(const int rank, const int file);

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
