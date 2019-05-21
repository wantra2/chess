#pragma once

#include "board/chessboard-interface.hh"
#include "board/board.hh"

namespace board
{
    class BoardAdapter : public ChessboardInterface
    {
    public:
        BoardAdapter(Board& board); // Missing: the listener_manager
        ~BoardAdapter() = default;

        opt_piece_t operator[](const Position& position) const override;

    private:
        Board& board_;
        // MISSING: The listener_manager
    };
}
