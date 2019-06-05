#include "board/position.hh"
#include "move/move.hh"

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

    Position to_position(const square cell)
    {
        File f = move::int_to_file(fileof(cell));
        Rank r = move::int_to_rank(rankof(cell));
        Position pos(f, r);
        return pos;
    }
}
