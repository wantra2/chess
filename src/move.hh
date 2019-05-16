#pragma once

#include "types.hh"

namespace board
{
    class Move
    {
    public:
        Move(const square from, const square to);
        Move(const square from, const square to, const Piecetype pt, const Movetype mt);

        square to() const;
        square from() const;
        Movetype type() const;
        Piecetype prom() const;
        uint16_t get() const;

    private:
        const uint16_t move_;
    };
}