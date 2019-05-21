#include "board/piece-type.hh"

namespace board
{
    PieceType switch_piecetype(const piece_type type)
    {
        switch(type)
        {
        case (piece_type::PAWN):
            return PieceType::PAWN;

        case (piece_type::KNIGHT):
            return PieceType::KNIGHT;

        case (piece_type::BISHOP):
            return PieceType::BISHOP;

        case (piece_type::ROOK):
            return PieceType::ROOK;

        case (piece_type::QUEEN):
            return PieceType::QUEEN;

        case (piece_type::KING):
            return PieceType::KING;

        default:
            throw std::out_of_range("Non-corresponding piece types");
        }
    }
}
