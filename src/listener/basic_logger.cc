#include <iostream>
#include "listener/basic_logger.hh"
#include "board/chessboard-interface.hh"
#include "board/piece-type.hh"
#include "board/position.hh"
#include "board/color.hh"

namespace listener
{
    void Basic_logger::register_board(const board::ChessboardInterface& board_interface)
    {
        std::cout << "hocus pocus, prepare your anus\n";
    }
    void Basic_logger::on_game_finished()
    {
        std::cout << "Game finished\n";
    }
    void Basic_logger::on_piece_moved(const board::PieceType piece,
                                        const board::Position& from,
                                        const board::Position& to)
    {
        std::cout << "Piece moved\n";
    }
    void Basic_logger::on_piece_taken(const board::PieceType piece,
                                        const board::Position& at)
    {
        std::cout << "Piece taken\n";
    }
    void Basic_logger::on_piece_promoted(const board::PieceType piece,
                                        const board::Position& at)
    {
        std::cout << "Piece promoted\n";
    }
    void Basic_logger::on_kingside_castling(const board::Color color)
    {
        std::cout << "Castling kingside\n";
    }
    void Basic_logger::on_queenside_castling(const board::Color color)
    {
        std::cout << "Castling queenside\n";
    }
    void Basic_logger::on_player_check(const board::Color color)
    {
        std::cout << "Check\n";
    }
    void Basic_logger::on_player_mat(const board::Color color)
    {
        std::cout << "Checkmate\n";
    }
    void Basic_logger::on_player_pat(const board::Color color)
    {
        std::cout << "Stalemate\n";
    }
    void Basic_logger::on_player_timeout(const board::Color color)
    {
        std::cout << "Timeout\n";
    }
    void Basic_logger::on_player_disqualified(const board::Color color)
    {
        std::cout << "Disqualification\n";
    }
    void Basic_logger::on_draw()
    {
        std::cout << "Draw\n";
    }
}


