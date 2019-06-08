#pragma once

#include <array>
#include <optional>

namespace board
{
    /* PieceType is an enum representing every possible
     * piece type present on the board. The char associated
     * with each value is the ascii char representing the
     * piece on the board */
    enum class PieceType
    {
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN,
        KING, // Last position allows better optimization (order-move)
    };

    enum piece_type : int
    {
        WHITE,
        BLACK,
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING,
        NONE = 0,
    };

    enum piece_type_with_color : int
    {
        VOID,
        WHITE_PAWN,
        WHITE_KNIGHT,
        WHITE_BISHOP,
        WHITE_ROOK,
        WHITE_QUEEN,
        WHITE_KING,
        BLACK_PAWN,
        BLACK_KNIGHT,
        BLACK_BISHOP,
        BLACK_ROOK,
        BLACK_QUEEN,
        BLACK_KING
    };

    piece_type type(const piece_type_with_color& pt);

    using opt_piecetype_t = std::optional<PieceType>;

    /* Can be useful to iterate over PieceTypes */
    constexpr std::array<PieceType, 6> piecetype_array{
        PieceType::QUEEN,  PieceType::ROOK, PieceType::BISHOP,
        PieceType::KNIGHT, PieceType::PAWN, PieceType::KING};

    inline PieceType char_to_piece(const char c)
    {
        switch (c)
        {
        case 'P':
            return PieceType::PAWN;
        case 'N':
            return PieceType::KNIGHT;
        case 'B':
            return PieceType::BISHOP;
        case 'R':
            return PieceType::ROOK;
        case 'Q':
            return PieceType::QUEEN;
        case 'K':
            return PieceType::KING;
        default:
            throw std::invalid_argument("Unknown piece");
        }
    }

    PieceType switch_piece_type(const piece_type type);
    piece_type switch_piecetype(const PieceType type);

} // namespace board
