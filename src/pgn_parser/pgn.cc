#include "pgn_parser/pgn.hh"

#include <vector>
#include <optional>
#include <string>
#include <iostream>
#include <fstream>
#include <utils/misc.hh>

#include "pgn_parser/pgn-parser.hh"
#include "board/pgn-move.hh"
#include "board/board.hh"
#include "board/board-adapter.hh"
#include "board/piece-type.hh"
#include "move/move.hh"

namespace pgn_parser
{
    std::vector<move::Move> get_moves(const std::vector<board::PgnMove>& pgn_moves)
    {
        std::vector<move::Move> res;
        for (auto i : pgn_moves)
        {
            board::square from = board::to_square(move::rank_to_int(i.start_.rank_get()),
                                                  move::file_to_int(i.start_.file_get()));
            board::square to = board::to_square(move::rank_to_int(i.end_.rank_get()),
                                                move::file_to_int(i.end_.file_get()));
            auto pt = board::piece_type::NONE;
            if (i.promotion_ != std::nullopt)
                pt = board::switch_piecetype(i.promotion_.value());
            move::MoveType type = move::MoveType::NORMAL;
            if (i.piece_ == board::PieceType::KING and abs(to - from) == 2)
                type = move::MoveType::CASTLING;
            res.emplace_back(move::create_move(from, to, pt, type));
        }
        return res;
    }

    int play(std::vector<move::Move> moves, std::vector<std::string> listeners)
    {
        std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        board::Board board(fen);
        board::BoardAdapter adapter(board, listeners);
        for (auto i : moves)
        {
            board::square king = static_cast<board::square>(board::getlsb(
                    adapter.board_.bitboards_[board::KING] & adapter.board_.bitboards_[adapter.board_.side_]));
            if (adapter.board_.is_attacked(king, adapter.board_.side_)) {
                for (const auto l : adapter.board_.listeners_)
                    l->on_player_check(static_cast<board::Color>(adapter.board_.side_));
            }
            adapter.do_move(i);
//            if (adapter.board_.is_finished())
//                return 0;
        }
        return 0;
    }

    int pgn_play(const std::string& file, std::vector<std::string> listeners)
    {
        return play(get_moves(parse_pgn(file)), listeners);
    }
}
