#include "board/piece-type.hh"

namespace board
{
    PieceType switch_piece_type(const piece_type type)
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

    piece_type switch_piecetype(const PieceType type)
    {
        switch(type)
        {
        case (PieceType::PAWN):
            return piece_type::PAWN;
        case (PieceType::KNIGHT):
            return piece_type::KNIGHT;
        case (PieceType::BISHOP):
            return piece_type::BISHOP;
        case (PieceType::ROOK):
            return piece_type::ROOK;
        case (PieceType::QUEEN):
            return piece_type::QUEEN;
        case (PieceType::KING):
            return piece_type::KING;
        default:
            throw std::out_of_range("Non-corresponding piece types");
        }
    }

    piece_type type(const piece_type_with_color& pt)
    {
        switch(pt)
        {
            case (WHITE_PAWN):
                return PAWN;

            case (BLACK_PAWN):
                return PAWN;

            case (WHITE_KNIGHT):
                return KNIGHT;

            case (BLACK_KNIGHT):
                return KNIGHT;

            case (WHITE_BISHOP):
                return BISHOP;

            case (BLACK_BISHOP):
                return BISHOP;

            case (WHITE_ROOK):
                return ROOK;

            case (BLACK_ROOK):
                return ROOK;

            case (WHITE_QUEEN):
                return QUEEN;

            case (BLACK_QUEEN):
                return QUEEN;

            case (WHITE_KING):
                return KING;

            case (BLACK_KING):
                return KING;

            default:
                return NONE;
        }
    }
}
