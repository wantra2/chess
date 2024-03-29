#include "pgn_parser/pgn.hh"

#include <vector>
#include <algorithm>
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
        int mask = 0x1FFF;
        adapter.board_.hashes_.emplace_back(adapter.board_.hash_);
        for (auto i : moves)
        {
            if (adapter.board_.is_pat())
                return 0;
            if (adapter.board_.is_draw())
                return 0;
//            std::vector<move::Move> ml;
//            adapter.board_.gen_all(ml);
//            if (move::mv_type(i) == move::PROMOTION &&  ml.end() == std::find(ml.begin(), ml.end(), i))
//            {
//                for (const auto l : adapter.board_.listeners_)
//                    l->on_player_disqualified(static_cast<board::Color>(adapter.board_.side_));
//                return 0;
//            }
//            if (ml.end() == std::find(ml.begin(), ml.end(), i&mask) && ml.end() == std::find(ml.begin(), ml.end(), i))
//            {
//                for (const auto l : adapter.board_.listeners_)
//                    l->on_player_disqualified(static_cast<board::Color>(adapter.board_.side_));
//                return 0;
//            }

            board::square king = static_cast<board::square>(board::getlsb(
                    adapter.board_.bitboards_[board::KING] & adapter.board_.bitboards_[adapter.board_.side_]));
            if (adapter.board_.is_attacked(king, adapter.board_.side_)) {
                for (const auto l : adapter.board_.listeners_)
                    l->on_player_check(static_cast<board::Color>(adapter.board_.side_));
            }
            adapter.do_move(i);
            adapter.board_.hashes_.emplace_back(adapter.board_.hash_);
            if (adapter.board_.is_finished())
                return 0;
        }
        return 0;
    }

    int pgn_play(const std::string& file, std::vector<std::string> listeners)
    {
        return play(get_moves(parse_pgn(file)), listeners);
    }
}
