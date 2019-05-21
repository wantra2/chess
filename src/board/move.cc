#include "board/move.hh"

namespace move
{
    board::File int_to_file(int i)
    {
        switch (i)
        {
            case 0:
                return board::File::A;
            case 1:
                return board::File::B;
            case 2:
                return board::File::C;
            case 3:
                return board::File::D;
            case 4:
                return board::File::E;
            case 5:
                return board::File::F;
            case 6:
                return board::File::G;
            case 7:
                return board::File::H;
            default:
                throw std::out_of_range("file out of bounds");
        }
    }

    board::Rank int_to_rank(int i)
    {
        switch (i)
        {
            case 0:
                return board::Rank::ONE;
            case 1:
                return board::Rank::TWO;
            case 2:
                return board::Rank::THREE;
            case 3:
                return board::Rank::FOUR;
            case 4:
                return board::Rank::FIVE;
            case 5:
                return board::Rank::SIX;
            case 6:
                return board::Rank::SEVEN;
            case 7:
                return board::Rank::EIGHT;
            default:
                throw std::out_of_range("file out of bounds");
        }
    }

    board::Position move_src(Move move)
    {
        uint8_t s = (move >> 6) & 0x3F;
        board::File file = int_to_file(s / 8);
        board::Rank rank = int_to_rank(s % 8);
        board::Position pos(file, rank);
        return pos;
    }

    board::Position move_dst(Move move)
    {
        uint8_t d = move & 0x3F;
        board::File file = int_to_file(d / 8);
        board::Rank rank = int_to_rank(d % 8);
        board::Position pos(file, rank);
        return pos;
    }

    bool is_castling(Move move)
    {
        return ((move >> 12) & 0x3) == MoveType::CASTLING;
    }

    bool is_passant(Move move)
    {
        return ((move >> 12) & 0x3) == MoveType::EN_PASSANT;
    }

    bool is_promotion(Move move)
    {
        return ((move >> 12) & 0x3) == MoveType::PROMOTION;
    }

    board::piece_type promotion_type(Move move)
    {
        return (board::piece_type)(3 + ((move >> 14) & 0x3));
    }

    int file_to_int(board::File f)
    {
        switch (f)
        {
            case board::File::A:
                return 0;
            case board::File::B:
                return 1;
            case board::File::C:
                return 2;
            case board::File::D:
                return 3;
            case board::File::E:
                return 4;
            case board::File::F:
                return 5;
            case board::File::G:
                return 6;
            case board::File::H:
                return 7;
            default:
                throw std::out_of_range("how");
        }
    }

    int rank_to_int(board::Rank r)
    {
        switch (r)
        {
            case board::Rank::ONE:
                return 0;
            case board::Rank::TWO:
                return 1;
            case board::Rank::THREE:
                return 2;
            case board::Rank::FOUR:
                return 3;
            case board::Rank::FIVE:
                return 4;
            case board::Rank::SIX:
                return 5;
            case board::Rank::SEVEN:
                return 6;
            case board::Rank::EIGHT:
                return 7;
            default:
                throw std::out_of_range("how");

        }
    }

    int pos_to_int(board::Position pos)
    {
        return file_to_int(pos.file_get()) * 10
            + rank_to_int(pos.rank_get());
    }

    Move create_move(board::Position from, board::Position to,
            board::piece_type prom, MoveType move_type)
    {
        return (((((prom << 2) | move_type) << 6) | pos_to_int(from))
                << 6) | pos_to_int(to);
    }
}
