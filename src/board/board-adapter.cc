#include "board/board-adapter.hh"

#include "board/piece-type.hh"
#include "board/board.hh"
#include "move/move.hh"
#include "board/bitboard.hh"

namespace board
{
    BoardAdapter::BoardAdapter(Board& board)
        :board_(board)
    {}

    ChessboardInterface::opt_piece_t
    BoardAdapter::operator[](const Position& position) const
    {
        bitboard location = 1ull;
        location = location << move::pos_to_int(position);

        bool found = false;
        piece_type i = piece_type::PAWN;
        for (; i != piece_type::KING; i = (piece_type)((int)i + 1))
        {
            if (location & board_.get_bitboard(i))
            {
                found = true;
                break;
            }
        }
        if (! found)
            return std::nullopt;

        if (location & board_.get_bitboard(Color::WHITE))
            return std::pair<PieceType, Color>(switch_piecetype(i)
                                               , Color::WHITE);

        return std::pair<PieceType, Color>(switch_piecetype(i), Color::BLACK);
    }
}
