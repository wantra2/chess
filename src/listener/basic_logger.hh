#pragma once

#include "listener/listener.hh"

namespace listener
{
    class Basic_logger : public Listener
    {
    public:

        void
        register_board(const board::ChessboardInterface& board_interface) override;


        void on_game_finished() override;


        void on_piece_moved(const board::PieceType piece,
                                    const board::Position& from,
                                    const board::Position& to) override;


        void on_piece_taken(const board::PieceType piece,
                                    const board::Position& at) override;


        void on_piece_promoted(const board::PieceType piece,
                                       const board::Position& at) override;


        void on_kingside_castling(const board::Color color) override;


        void on_queenside_castling(const board::Color color) override;


        void on_player_check(const board::Color color) override;


        void on_player_mat(const board::Color color) override;


        void on_player_pat(const board::Color color) override;


        void on_player_disqualified(const board::Color color) override;


        void on_draw() override;
    };
}
