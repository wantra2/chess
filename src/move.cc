#include "move.hh"

namespace board
{
    Move::Move(const square from, const square to)
    :move_{(from << 6) + to}
    {
    }
    Move::Move(const square from, const square to, const Piecetype pt, const Movetype mt)
    :move_{mt + ((pt - 3) << 12) + (from << 6) + to}
    {
    }

    square Move::to() const
    {
        return (square)(move_ & 0x3F);
    }
    square Move::from() const
    {
        return (square)((move_ >> 6) & 0x3F);
    }
    Movetype Move::type() const
    {
        return (Movetype)(move_ & (3 << 14));
    }
    Piecetype Move::prom() const
    {
        return (Piecetype)(((move_ >> 12) & 3) + 3);
    }
    uint16_t Move::get() const
    {
        return move_;
    }
}