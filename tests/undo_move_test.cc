#include <gtest/gtest.h>

#include "board/board.hh"


void do_undo(const board::square& src_square, const board::square& dst_square,
        std::string& fen, const move::MoveType& move_type)
{
    auto move = move::create_move(src_square, dst_square, move_type);
    board::Board b(fen);
    auto bitboard_before = b.bitboards_;
    auto castling_rights_before = b.state_.castling_rights;
    auto en_p_square_before = b.state_.en_p_square;
    b.do_move(move);
    b.undo_move(move);
    for (int i = 0; i < 8; ++i)
    {
        ASSERT_EQ(bitboard_before[i], b.bitboards_[i]);
    }
    ASSERT_EQ(castling_rights_before[0], b.state_.castling_rights[0]);
    ASSERT_EQ(castling_rights_before[1], b.state_.castling_rights[1]);
    ASSERT_EQ(en_p_square_before, b.state_.en_p_square);
}

TEST(undo, white_pawn_move)
{
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    board::square src_square = board::C2;
    board::square dst_square = board::C4;
    do_undo(src_square, dst_square, fen, move::NORMAL);
}

TEST(undo, white_knight_move)
{
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    board::square src_square = board::G1;
    board::square dst_square = board::F3;
    do_undo(src_square, dst_square, fen, move::NORMAL);
}

TEST(undo, black_knight_move)
{
    std::string fen = "rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1";
    board::square src_square = board::B8;
    board::square dst_square = board::C6;
    do_undo(src_square, dst_square, fen, move::NORMAL);
}

TEST(undo, white_small_castling)
{
    std::string fen = "rnbqkbnr/p1ppp1p1/1p3p1p/8/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4";
    board::square src_square = board::E1;
    board::square dst_square = board::G1;
    do_undo(src_square, dst_square, fen, move::CASTLING);
}

TEST(undo, white_en_passant)
{
    std::string fen = "rnbqkbnr/p1p1p1p1/1p5p/3pPp2/2B5/5N2/PPPP1PPP/RNBQ1RK1 w kq d6 0 6";
    board::square src_square = board::E5;
    board::square dst_square = board::D6;
    do_undo(src_square, dst_square, fen, move::EN_PASSANT);
}

TEST(undo, white_big_castling)
{
    std::string fen = "rnbqkbr1/p1ppp1pp/1p6/3n1pB1/Q1PP4/2N5/PP2PPPP/R3KBNR w KQq - 2 6";
    board::square src_square = board::E1;
    board::square dst_square = board::C1;
    do_undo(src_square, dst_square, fen, move::CASTLING);
}
