#pragma once

#include <dlfcn.h>
#include <iostream>

#include "board/chessboard-interface.hh"
#include "board/board.hh"
#include "listener/listener.hh"
#include "move/move.hh"

namespace board
{
    class BoardAdapter : public ChessboardInterface
    {
    public:
        BoardAdapter(Board& board, std::vector<std::string> listeners);
        ~BoardAdapter();

        opt_piece_t operator[](const Position& position) const override;
        void do_move(move::Move move);

        Board& board_;
    private:
        std::vector<void *> handles_;
        std::vector<listener::Listener*> listeners_;
    };
}
