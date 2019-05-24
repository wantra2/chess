#include "board/position.hh"

namespace board
{
    int rankof(const int square)
    {return square / 8;}

    int fileof(const int square)
    {return square % 8;}

    int to_square(const int rank, const int file)
    {return rank * 8 + file;}

    bool valid_coordinates(const int rank, const int file)
    {return (rank >= 0 && rank <= 7) && (file >= 0 && file <= 7);}
}