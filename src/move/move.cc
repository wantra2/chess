#include "move/move.hh"

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

    board::square move_src(const Move move)
    {
        return board::square((move >> 6) & 0x3F);
    }

    board::square move_dst(const Move move)
    {
        return board::square(move & 0x3F);
    }

    bool is_castling(const Move move)
    {
        return ((move >> 12) & 0x3) == MoveType::CASTLING;
    }

    bool is_passant(const Move move)
    {
        return ((move >> 12) & 0x3) == MoveType::EN_PASSANT;
    }

    bool is_promotion(const Move move)
    {
        return ((move >> 12) & 0x3) == MoveType::PROMOTION;
    }

    move::MoveType mv_type(const Move move)
    {
        return move::MoveType((move >> 12) & 0x3);
    }

    board::piece_type promotion_type(const Move move)
    {
        return board::piece_type(3 + ((move >> 14) & 0x3));
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
        return rank_to_int(pos.rank_get()) * 8
            + file_to_int(pos.file_get());
    }

    Move create_move(const int square_from, const int square_to,
            const board::piece_type prom, const MoveType move_type)
    {
        return (move_type << 12) + ((prom - board::KNIGHT) << 12) + (square_from << 6) + square_to;
    }
}
