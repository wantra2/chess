#pragma once

namespace board
{
    /* The Color enum represent a side. */
    enum class Color : bool
    {
        WHITE = false,
        BLACK = true
    };

#ifndef STUDENT
    constexpr Color other_color(Color color) noexcept
    {
        return Color::WHITE == color ? Color::BLACK : Color::WHITE;
    }
#endif

} // namespace board
