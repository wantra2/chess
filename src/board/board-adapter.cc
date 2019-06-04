#include "board/board-adapter.hh"

#include "board/piece-type.hh"
#include "board/board.hh"
#include "move/move.hh"
#include "board/bitboard.hh"

namespace board
{
    BoardAdapter::BoardAdapter(Board& board, std::vector<std::string> listeners)
        : board_(board)
    {
        for (auto& i : listeners)
        {
            auto handle = dlopen(i.c_str(), RTLD_LAZY);
            handles_.emplace_back(handle);
            auto symbol = dlsym(handle, "listener_create");
            if (symbol == nullptr)
                std::cout << "symbol not found\n";
            else
            {
                listener::Listener* listener = reinterpret_cast<listener::Listener*(*)()>(symbol)();
                listeners_.emplace_back(listener);
            }
        }
        board_.set_listeners(listeners_);
    }

    BoardAdapter::~BoardAdapter()
    {
        for (auto i : handles_)
            dlclose(i);
    }

    ChessboardInterface::opt_piece_t
    BoardAdapter::operator[](const Position& position) const
    {
        bitboard location = 1ull;
        location = location << move::pos_to_int(position);

        bool found = false;
        piece_type i = piece_type::PAWN;
        for (; i != piece_type::KING; i = (piece_type)((int)i + 1))
        {
            if (location & board_.bitboards_[i])
            {
                found = true;
                break;
            }
        }
        if (! found)
            return std::nullopt;

        if (location & board_.bitboards_[(int)Color::WHITE])
            return std::pair<PieceType, Color>(switch_piecetype(i)
                                               , Color::WHITE);

        return std::pair<PieceType, Color>(switch_piecetype(i), Color::BLACK);
    }

    void BoardAdapter::do_move(move::Move move)
    {
        board_.do_move(move);
    }
}
