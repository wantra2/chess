#include "board/board.hh"

#include <iostream>

namespace board
{
    Board::Board()
    {
        generate_board();
        ply_ = 0;
    }

    constexpr void Board::generate_board()
    {
        bitboards_[(int)Color::WHITE] = 0x000000000000FFFF; //WHITES
        bitboards_[(int)Color::BLACK] = 0xFFFF000000000000; //BLACKS
        bitboards_[piece_type::PAWN] = 0x00FF00000000FF00; //PAWNS
        bitboards_[piece_type::KNIGHT] = 0x4200000000000042; //KNIGHTS
        bitboards_[piece_type::BISHOP] = 0x2400000000000024; //BISHOPS
        bitboards_[piece_type::ROOK] = 0x8100000000000081; //ROOKS
        bitboards_[piece_type::QUEEN] = 0x0800000000000008; //QUEENS
        bitboards_[piece_type::KING] = 0x1000000000000010; //KINGS
    }

    Board::bitboard& Board::get_bitboard(piece_type type)
    {
        return bitboards_[(int)type];
    }

    Board::bitboard& Board::get_bitboard(Color color)
    {
        return bitboards_[(int)color];
    }

    std::vector<move::Move> Board::gen_king_moves(Color color)
    {
        bitboard occupied = bitboards_[(int)color];
        bitboard b = bitboards_[piece_type::KING]
            & bitboards_[(int)color];
        bitboard bit = 1;
        std::vector<move::Move> move_list;
        uint8_t i = 0;
        while (i < 64)
        {
            if (b & bit)
            {
                if (((b >> 9) & occupied) == 0)
                    move_list.push_back((i << 6) | (i - 9));
                if (((b >> 8) & occupied) == 0)
                    move_list.push_back((i << 6) | (i - 8));
                if (((b >> 7) & occupied) == 0)
                    move_list.push_back((i << 6) | (i - 7));
                if (((b >> 1) & occupied) == 0)
                    move_list.push_back((i << 6) | (i - 1));
                if (((b << 1) & occupied) == 0)
                    move_list.push_back((i << 6) | (i + 1));
                if (((b << 7) & occupied) == 0)
                    move_list.push_back((i << 6) | (i + 7));
                if (((b << 8) & occupied) == 0)
                    move_list.push_back((i << 6) | (i + 8));
                if (((b << 9) & occupied) == 0)
                    move_list.push_back((i << 6) | (i + 9));
                break;
            }
            bit <<= 1;
            ++i;
        }
        return move_list;
    }

    std::vector<move::Move> Board::gen_knight_moves(Color color)
    {
        bitboard occupied = bitboards_[(int)color];
        bitboard b = bitboards_[piece_type::KNIGHT]
            & bitboards_[(int)color];
        bitboard bit = 1;
        std::vector<move::Move> move_list;
        uint8_t i = 0;
        while (i < 64)
        {
            if (b & bit)
            {
                if (((b >> 17) & occupied) == 0)
                    move_list.push_back((i << 6) | (i - 17));
                if (((b >> 15) & occupied) == 0)
                    move_list.push_back((i << 6) | (i - 15));
            }
        }
        return move_list;
    }
}
