#include "board/board.hh"

#include <iostream>

namespace board
{
    Board::Board()
    {
        generate_board();
        init_Knight_and_KingAttacks();
        ply_ = 0;
    }

    constexpr void Board::generate_board()
    {
        bitboards_[(int)Color::WHITE] = 0x000000000000FFFF; //WHITES
        bitboards_[(int)Color::BLACK] = 0xFFFF000000000000; //BLACKS
        bitboards_[PAWN] = 0x00FF00000000FF00; //PAWNS
        bitboards_[KNIGHT] = 0x4200000000000042; //KNIGHTS
        bitboards_[BISHOP] = 0x2400000000000024; //BISHOPS
        bitboards_[ROOK] = 0x8100000000000081; //ROOKS
        bitboards_[QUEEN] = 0x0800000000000008; //QUEENS
        bitboards_[KING] = 0x1000000000000010; //KINGS
    }

    void Board::init_Knight_and_KingAttacks()
    {
        const int KnightDelta[8][2] = {{-2,-1}, {-2, 1}, {-1,-2}, {-1, 2},{ 1,-2}, { 1, 2}, { 2,-1}, { 2, 1}};
        const int KingDelta[8][2]   = {{-1,-1}, {-1, 0}, {-1, 1}, { 0,-1},{ 0, 1}, { 1,-1}, { 1, 0}, { 1, 1}};
        for (int sq = board::A1; sq < SQUARE_NB; ++sq)
        {
            for (int d = 0; d < 8; ++d)
            {
                square_set(knightAttacks_[sq], board::rank(sq) + KnightDelta[d][0], board::file(sq) + KnightDelta[d][1]);
                square_set(kingAttacks_[sq], board::rank(sq) + KingDelta[d][0], board::file(sq) + KingDelta[d][1]);
            }
        }
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

    void Board::gen_non_pawn(std::vector<move::Move>& movelist, bitboard attacks, const int square_from)
    {
        while (attacks)
        {
            int target_square = poplsb(attacks);
            movelist.emplace_back(move::create_move(square_from, target_square, board::KNIGHT, move::NORMAL));
        }
    }

    void Board::gen_KnightMoves(std::vector<move::Move>& movelist, bitboard knights, const bitboard& targets)
    {
        while (knights)
        {
            int from_square = poplsb(knights);
            gen_non_pawn(movelist, knightAttacks_[from_square] & targets, from_square);
        }
    }
}
