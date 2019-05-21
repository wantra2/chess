#include "board/move.hh"

namespace move
{
    board::File int_to_file(int i)
    {
        switch (i)
        {
            case 0:
                return board::File::A;
            case 1:
                return board::File::B;
            case 2:
                return board::File::C;
            case 3:
                return board::File::D;
            case 4:
                return board::File::E;
            case 5:
                return board::File::F;
            case 6:
                return board::File::G;
            case 7:
                return board::File::H;
            default:
                throw std::out_of_range("file out of bounds")
        }
    }

    board::Rank int_to_rank(int i)
    {
        switch (i)
        {
            case 0:
                return board::Rank::ONE;
            case 1:
                return board::Rank::TWO;
            case 2:
                return board::Rank::THREE;
            case 3:
                return board::Rank::FOUR;
            case 4:
                return board::Rank::FIVE;
            case 5:
                return board::Rank::SIX;
            case 6:
                return board::Rank::SEVEN;
            case 7:
                return board::Rank::EIGHT;
            default:
                throw std::out_of_range("file out of bounds")
        }
    }

    board::Position move_src(Move move)
    {
        uint8_t s = (move >> 6) & 0x3F;
        board::File file = int_to_file(s / 8);
        board::Rank rank = int_to_rank(s % 8);
        board::Position pos(file, rank);
        return pos;
    }
}
