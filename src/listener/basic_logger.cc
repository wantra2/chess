#include <iostream>
#include "listener/basic_logger.hh"
#include "board/chessboard-interface.hh"
#include "board/piece-type.hh"
#include "board/position.hh"
#include "board/color.hh"

namespace listener
{
    void Basic_logger::register_board(const board::ChessboardInterface& board_interface)
    {}
    void Basic_logger::on_game_finished()
    {
        std::cout << "[game_finished]\t\n";
    }
    void Basic_logger::on_piece_moved(const board::PieceType piece,
                                        const board::Position& from,
                                        const board::Position& to)
    {
        std::cout << "[move]\tboard::PieceType: " << (int)piece << '\n';
    }
    void Basic_logger::on_piece_taken(const board::PieceType piece,
                                        const board::Position& at)
    {
        std::cout << "[piece_taken]\tpiece: " << (int)piece << " file: "
                  << (int)at.file_get() << " rank: " << (int)at.rank_get() << "\n";
    }
    void Basic_logger::on_piece_promoted(const board::PieceType piece,
                                        const board::Position& at)
    {
        std::cout << "Piece promoted\n";
    }
    void Basic_logger::on_kingside_castling(const board::Color color)
    {
        std::cout << "[kingside castling]\tcolor: " << (int)color << '\n';
    }
    void Basic_logger::on_queenside_castling(const board::Color color)
    {
        std::cout << "[queenside castling]\tcolor: " << (int)color << '\n';
    }
    void Basic_logger::on_player_check(const board::Color color)
    {
        std::cout << "[check]\t: color: " << (int)color << '\n';
    }
    void Basic_logger::on_player_mat(const board::Color color)
    {
        std::cout << "[mat]\t: color: " << (int)color << '\n';
    }
    void Basic_logger::on_player_disqualified(const board::Color color)
    {
        std::cout << "[disqualified]\t: color: " << (int)color << '\n';
    }
    void Basic_logger::on_draw()
    {}
}
