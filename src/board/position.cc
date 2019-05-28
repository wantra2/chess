#include "board/position.hh"

namespace board
{
    int rankof(const square& square)
    {return square / 8;}

    int fileof(const square& square)
    {return square % 8;}

    square to_square(const int& rank, const int& file)
    {return (square)(rank * 8 + file);}

    bool valid_coordinates(const int& rank, const int& file)
    {return (rank >= 0 && rank <= 7) && (file >= 0 && file <= 7);}
}
