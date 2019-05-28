#include "board/board.hh"

#include "utils/misc.hh"
#include "board/bitboard.hh"
#include "position.hh"

#include <iostream>

namespace board
{
    Board::Board()
    {
        generate_board();
        generate_pieces();
        init_pawn_attacks();
        init_slide_attacks();
        init_Knight_and_KingAttacks();
        init_castling();
        ply_ = 0;
        side_ = WHITE;
        en_p_square = SQUARE_NB;
    }

    void Board::init_castling()
    {
        castling_rights_[WHITE] = BOTH;
        castling_rights_[BLACK] = BOTH;
        castlings_sq[WHITE][index_00] = 0x60;
        castlings_sq[WHITE][index_000] = 0xe;
        castlings_sq[BLACK][index_00] =  0x6000000000000000;
        castlings_sq[BLACK][index_000] = 0x0e00000000000000;
    }

    void Board::generate_board()
    {
        bitboards_[WHITE] = 0x000000000000FFFF; //WHITES
        bitboards_[BLACK] = 0xFFFF000000000000; //BLACKS
        bitboards_[PAWN] = 0x00FF00000000FF00; //PAWNS
        bitboards_[KNIGHT] = 0x4200000000000042; //KNIGHTS
        bitboards_[BISHOP] = 0x2400000000000024; //BISHOPS
        bitboards_[ROOK] = 0x8100000000000081; //ROOKS
        bitboards_[QUEEN] = 0x0800000000000008; //QUEENS
        bitboards_[KING] = 0x1000000000000010; //KINGS
    }

    void Board::generate_pieces()
    {
        pieces_[0] = piece_type_with_color::WHITE_ROOK;
        pieces_[1] = piece_type_with_color::WHITE_KNIGHT;
        pieces_[2] = piece_type_with_color::WHITE_BISHOP;
        pieces_[3] = piece_type_with_color::WHITE_QUEEN;
        pieces_[4] = piece_type_with_color::WHITE_KING;
        pieces_[5] = piece_type_with_color::WHITE_BISHOP;
        pieces_[6] = piece_type_with_color::WHITE_KNIGHT;
        pieces_[7] = piece_type_with_color::WHITE_ROOK;
        for (int i = 8; i < 16; ++i)
            pieces_[i] = piece_type_with_color::WHITE_PAWN;
        for (int i = 16; i < 48; ++i)
            pieces_[i] = piece_type_with_color::VOID;
        for (int i = 48; i < 56; ++i)
            pieces_[i] = piece_type_with_color::BLACK_PAWN;
        pieces_[56] = piece_type_with_color::BLACK_ROOK;
        pieces_[57] = piece_type_with_color::BLACK_KNIGHT;
        pieces_[58] = piece_type_with_color::BLACK_BISHOP;
        pieces_[59] = piece_type_with_color::BLACK_QUEEN;
        pieces_[60] = piece_type_with_color::BLACK_KING;
        pieces_[61] = piece_type_with_color::BLACK_BISHOP;
        pieces_[62] = piece_type_with_color::BLACK_KNIGHT;
        pieces_[63] = piece_type_with_color::BLACK_ROOK;

    }

    void Board::init_pawn_attacks()
    {
        const int white_pawn_offsets[2][2] = {{ 1,-1}, { 1,1}};
        const int black_pawn_offsets[2][2] = {{-1,-1}, {-1,1}};
        for (int sq = A1; sq < H8; ++sq)
        {
            for (int d = 0; d < 2; ++d)
            {
                square_set(pawnAttacks_[WHITE][sq], rankof((square)sq) + white_pawn_offsets[d][0], fileof((square)sq) + white_pawn_offsets[d][1]);
                square_set(pawnAttacks_[BLACK][sq], rankof((square)sq) + black_pawn_offsets[d][0], fileof((square)sq) + black_pawn_offsets[d][1]);
            }
        }
    }

    void Board::gen_castlings(std::vector<move::Move>& movelist, const bitboard& occupied, const int& color) const
    {
            const square kingsquare = side_ == WHITE ? E1 : E8;
            const int f1_sq = side_ == WHITE ? F1 : F8;
            const int d1_sq = side_ == WHITE ? D1 : D8;
            const bool king_attacked = is_attacked(kingsquare, color);

            if ((castling_rights_[color] & 1) &&
                ((occupied & castlings_sq[color][index_00]) == 0) &&
                !king_attacked && !is_attacked((square)f1_sq, color))
            {
                movelist.emplace_back(move::create_move(kingsquare, (square)(kingsquare+2), move::CASTLING));
            }

            if ((castling_rights_[color] & 2) &&
                ((occupied & castlings_sq[color][index_000]) == 0) &&
                !king_attacked && !is_attacked((square)d1_sq, color))
            {
                movelist.emplace_back(move::create_move(kingsquare, (square)(kingsquare-2), move::CASTLING));
            }
    }

    void Board::init_Knight_and_KingAttacks()
    {
        const int KnightOffsets[8][2] = {{-2,-1}, {-2, 1}, {-1,-2}, {-1, 2},{ 1,-2}, { 1, 2}, { 2,-1}, { 2, 1}};
        const int KingOffsets[8][2]   = {{-1,-1}, {-1, 0}, {-1, 1}, { 0,-1},{ 0, 1}, { 1,-1}, { 1, 0}, { 1, 1}};
        for (int sq = A1; sq < SQUARE_NB; ++sq)
        {
            for (int d = 0; d < 8; ++d)
            {
                square_set(knightAttacks_[sq], rankof((square)sq) + KnightOffsets[d][0], fileof((square)sq) + KnightOffsets[d][1]);
                square_set(kingAttacks_[sq], rankof((square)sq) + KingOffsets[d][0], fileof((square)sq) + KingOffsets[d][1]);
            }
        }
    }

    void Board::init_slide_attacks()
    {
        bishopMagics_[0].offset = bishopAttacks_;
        rookMagics_[0].offset = rookAttacks_;

        const int bishop_offsets[4][2] = {{-1,-1}, {-1, 1}, { 1,-1}, { 1, 1}};
        const int rook_offsets[4][2]   = {{-1, 0}, { 0,-1}, { 0, 1}, { 1, 0}};

        for (int sq = A1; sq < H8; ++sq)
        {
            init_magics((square)sq, bishopMagics_, BishopMagicNumbers[sq], bishop_offsets);
            init_magics((square)sq, rookMagics_, RookMagicNumbers[sq], rook_offsets);
        }
    }

    bitboard Board::slider_attacks(const square& from_square, const bitboard& occupied, const int offsets[4][2]) const
    {
        int rank, file;
        bitboard tbr = 0ull;
        for (int d = 0; d < 4; ++d)
        {
            for (rank = rankof(from_square) + offsets[d][0],
                 file = fileof(from_square) + offsets[d][1]
                 ;
                 valid_coordinates(rank, file)
                 ;
                 rank += offsets[d][0], file += offsets[d][1])
            {
                square_set(tbr, rank, file);
                if (occupied & (1ull << to_square(rank, file)))
                    break;
            }
        }
        return tbr;
    }

    void Board::init_magics(const square& square, Magic* table, const bitboard& magic_number, const int offsets[4][2])
    {
        const bitboard edgesmask = ((RANK_1 | RANK_8) & ~Ranks[rankof(square)]) | ((FILE_A | FILE_H) & ~Files[fileof(square)]);
        table[square].magic_number = magic_number;
        table[square].mask = slider_attacks(square, 0ull, offsets) & ~edgesmask;
        table[square].shift_needed = 64 - popcount(table[square].mask);
        if (square < H8)
            table[square + 1].offset = table[square].offset + (1ull << popcount(table[square].mask));
        bitboard occupied = 0ull;
        unsigned index = table[square].compute_index(occupied);
        table[square].offset[index] = slider_attacks(square, occupied, offsets);
        occupied = (occupied - table[square].mask) & table[square].mask;
        while (occupied)
        {
            index = table[square].compute_index(occupied);
            table[square].offset[index] = slider_attacks(square, occupied, offsets);
            occupied = (occupied - table[square].mask) & table[square].mask;
        }
    }

    void Board::gen_non_pawn(std::vector<move::Move>& movelist, bitboard attacks, const square& square_from) const
    {
        while (attacks)
        {
            const int target_square = poplsb(attacks);
            movelist.emplace_back(move::create_move(square_from, (square)target_square));
        }
    }

    void Board::gen_KnightMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets) const
    {
        bitboard knights = bitboards_[KNIGHT] & bitboards_[color];
        while (knights)
        {
            const int from_square = poplsb(knights);
            gen_non_pawn(movelist, knightAttacks_[from_square] & targets, (square)from_square);
        }
    }

    void Board::gen_KingMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets) const
    {
        bitboard king = bitboards_[KING] & bitboards_[color];
        const int from_square = poplsb(king);
        gen_non_pawn(movelist, kingAttacks_[from_square] & targets, (square)from_square);
    }

    void Board::gen_queen_bishop_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets) const
    {
        bitboard pieces = (bitboards_[QUEEN]|bitboards_[BISHOP]) & bitboards_[color];
        while (pieces)
        {
            const int sq = poplsb(pieces);
            bitboard attacks = bishopMagics_[sq].offset[bishopMagics_[sq].compute_index(occupied)];
            gen_non_pawn(movelist, attacks & targets, (square)sq);
        }
    }

    void Board::gen_queen_rook_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets) const
    {
        bitboard pieces = (bitboards_[QUEEN]|bitboards_[ROOK]) & bitboards_[color];
        while (pieces)
        {
            const int sq = poplsb(pieces);
            bitboard attacks = rookMagics_[sq].offset[rookMagics_[sq].compute_index(occupied)];
            gen_non_pawn(movelist, attacks & targets, (square)sq);
        }
    }

    bool Board::is_attacked(const square& square, const int& color) const
    {
        const bitboard occupied = bitboards_[WHITE]|bitboards_[BLACK];
        const bitboard bishop_attacks = bishopMagics_[square].offset[bishopMagics_[square].compute_index(occupied)];
        const bitboard rook_attacks = rookMagics_[square].offset[rookMagics_[square].compute_index(occupied)];

        return pawnAttacks_[color][square] & (bitboards_[PAWN] & bitboards_[!color])
            || knightAttacks_[square] & (bitboards_[KNIGHT] & bitboards_[!color])
            || kingAttacks_[square] & (bitboards_[KING] & bitboards_[!color])
            || bishop_attacks & ((bitboards_[BISHOP]|bitboards_[QUEEN]) & bitboards_[!color])
            || rook_attacks & ((bitboards_[ROOK]|bitboards_[QUEEN]) & bitboards_[!color]);
    }

    void Board::gen_pawn_moves(std::vector<move::Move>& movelist, const int& color) const
    {
        const int direction = color == WHITE ? 8 : -8;
        const int two_times_direction = color == WHITE ? 16 : -16;
        const bitboard fileh = color == WHITE ? FILE_H : NOTHING;
        const bitboard filea = color == BLACK ? FILE_A : NOTHING;
        const bitboard fileh2 = color == WHITE ? FILE_H : NOTHING;
        const bitboard filea2 = color == WHITE ? FILE_A : NOTHING;
        const bitboard rank7 = color == WHITE ? RANK_7 : RANK_2;
        const bitboard rank3 = color == WHITE ? RANK_3 : RANK_6;
        const bitboard pawns_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & rank7;
        const bitboard pawns_not_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & ~rank7;
        const bitboard ennemy = bitboards_[!color];
        const bitboard empty = ~(bitboards_[WHITE]|bitboards_[BLACK]);
        //standard non-capture
        bitboard push1 = (pawns_not_on_rank7 << direction) & empty;
        bitboard push2 = ((push1 & rank3) << direction) & empty;

        while (push1)
        {
            const int sq = poplsb(push1);
            movelist.emplace_back(move::create_move((square)(sq-direction), (square)sq));
        }
        while (push2)
        {
            const int sq = poplsb(push2);
            movelist.emplace_back(move::create_move((square)(sq-two_times_direction), (square)sq));
        }

        //promotions
        bitboard cap1 = (pawns_on_rank7 << (direction+1) & ~filea) & ennemy;
        bitboard cap2 = ((pawns_on_rank7 << (direction-1)) & ~fileh) & ennemy;
        bitboard prom = (pawns_on_rank7 << (direction)) & empty;

        while (cap1)
        {
            const int sq = poplsb(cap1);
            movelist.emplace_back(move::create_move((square)(sq-1-direction), (square)sq, KNIGHT, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq-1-direction), (square)sq, BISHOP, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq-1-direction), (square)sq, ROOK, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq-1-direction), (square)sq, QUEEN, move::PROMOTION));
        }
        while (cap2)
        {
            const int sq = poplsb(cap2);
            movelist.emplace_back(move::create_move((square)(sq+1-direction), (square)sq, KNIGHT, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq+1-direction), (square)sq, BISHOP, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq+1-direction), (square)sq, ROOK, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq+1-direction), (square)sq, QUEEN, move::PROMOTION));
        }
        while (prom)
        {
            const int sq = poplsb(prom);
            movelist.emplace_back(move::create_move((square)(sq-direction), (square)sq, KNIGHT, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq-direction), (square)sq, BISHOP, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq-direction), (square)sq, ROOK, move::PROMOTION));
            movelist.emplace_back(move::create_move((square)(sq-direction), (square)sq, QUEEN, move::PROMOTION));
        }
        //captures
        bitboard cap3 = (pawns_not_on_rank7 << (direction+1) & ~filea2) & ennemy;
        bitboard cap4 = (pawns_not_on_rank7 << (direction-1) & ~fileh2) & ennemy;

        while (cap3)
        {
            const int sq = poplsb(cap3);
            movelist.emplace_back(move::create_move((square)(sq-1-direction), (square)sq));
        }
        while (cap4)
        {
            const int sq = poplsb(cap4);
            movelist.emplace_back(move::create_move((square)(sq+1-direction), (square)sq));
        }
        //en passant
        if (en_p_square != SQUARE_NB)
        {
            bitboard en_p_candidates = pawns_not_on_rank7 & pawnAttacks_[!color][en_p_square];
            while (en_p_candidates)
            {
                const int sq = poplsb(en_p_candidates);
                movelist.emplace_back(move::create_move((square)sq, en_p_square, move::EN_PASSANT));
            }
        }
    }

    void Board::do_castling(const square& src, const square& dst)
    {
        const int shift = side_ == piece_type::WHITE ? 0 : 56;
        bitboard rook = (dst>src) ? 1ull << (shift+7) : (1ull<<shift);
        const square rookpos = (square)poplsb(rook);
        const square rookdst = (dst>src) ? (square)(dst-1) : (square)(dst+1);

        remove_piece(src, piece_type::KING, side_);
        remove_piece(rookpos, piece_type::ROOK, side_);
        add_piece(dst, piece_type::KING, side_);
        add_piece(rookdst, piece_type::ROOK, side_);
    }
}
