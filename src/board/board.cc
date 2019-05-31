#include "board/board.hh"

#include "utils/misc.hh"
#include "board/bitboard.hh"
#include "position.hh"

#include <iostream>

namespace board
{
    std::vector<State> gamestates;

    Board::Board(std::string& fen)
    {
        //init pieces bb
        bitboards_[WHITE] = 0ull; //WHITES
        bitboards_[BLACK] = 0ull; //BLACKS
        bitboards_[PAWN] = 0ull; //PAWNS
        bitboards_[KNIGHT] = 0ull; //KNIGHTS
        bitboards_[BISHOP] = 0ull; //BISHOPS
        bitboards_[ROOK] = 0ull; //ROOKS
        bitboards_[QUEEN] = 0ull; //QUEENS
        bitboards_[KING] = 0ull; //KINGS
        //pieces square array
        for (int i = 0; i < SQUARE_NB; ++i)
            pieces_[i] = piece_type_with_color::VOID;

        int sq = A8;
        char *fen_ptr = &fen[0u];
        State st{NONE, {NO_CASTLING, NO_CASTLING}, SQUARE_NB};
        for (; !isspace(*fen_ptr); ++fen_ptr)
        {
            if (isdigit(*fen_ptr))
                sq += (*fen_ptr - '0');
            else if (*fen_ptr == '/')
                sq -= 16;
            else
            {
                const int color = isupper(*fen_ptr) ? WHITE : BLACK;
                piece_type pt = utils::char_to_piece(*fen_ptr);
                add_piece((square)sq, pt, color);
                ++sq;
            }
        }

        side_ = *(++fen_ptr) == 'w' ? WHITE : BLACK;
        ++fen_ptr;
        ++fen_ptr;

        for(; !isspace(*fen_ptr) && *fen_ptr != '-'; ++fen_ptr)
        {
            const int color = islower(*fen_ptr) ? BLACK : WHITE;
            const char token = toupper(*fen_ptr);
            if (token == 'K')
                st.castling_rights[color] |= 1;
            if (token == 'Q')
                st.castling_rights[color] |= 2;
        }
        if (*fen_ptr == '-')
            ++fen_ptr;
        ++fen_ptr;

        if (*fen_ptr != '-')
        {
            const char file = *fen_ptr;
            const char rank = *(++fen_ptr);
            st.en_p_square = to_square(rank-49, file-97);
        }

        gamestates.emplace_back(st);
        state_ = st;
    }

    void Board::gen_castlings(std::vector<move::Move>& movelist, const bitboard& occupied, const int& color) const
    {
            const square kingsquare = side_ == WHITE ? E1 : E8;
            const int f1_sq = side_ == WHITE ? F1 : F8;
            const int d1_sq = side_ == WHITE ? D1 : D8;
            const bool king_attacked = is_attacked(kingsquare, color);

            if ((state_.castling_rights[color] & 1) &&
                ((occupied & castlings_sq[color][index_00]) == 0) &&
                !king_attacked && !is_attacked((square)f1_sq, color))
            {
                movelist.emplace_back(move::create_move(kingsquare, (square)(kingsquare+2), move::CASTLING));
            }

            if ((state_.castling_rights[color] & 2) &&
                ((occupied & castlings_sq[color][index_000]) == 0) &&
                !king_attacked && !is_attacked((square)d1_sq, color))
            {
                movelist.emplace_back(move::create_move(kingsquare, (square)(kingsquare-2), move::CASTLING));
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

    void Board::gen_pawn_moves_quiet(std::vector<move::Move>& movelist, const int& color) const
    {
        const int direction = color == WHITE ? 8 : -8;
        const int two_times_direction = color == WHITE ? 16 : -16;
        const bitboard rank7 = color == WHITE ? RANK_7 : RANK_2;
        const bitboard pawns_not_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & ~rank7;
        const bitboard rank3 = color == WHITE ? RANK_3 : RANK_6;
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
    }

    void Board::gen_pawn_moves_noisy(std::vector<move::Move>& movelist, const int& color) const
    {
        const int direction = color == WHITE ? 8 : -8;
        const bitboard fileh = color == WHITE ? FILE_H : NOTHING;
        const bitboard filea = color == BLACK ? FILE_A : NOTHING;
        const bitboard fileh2 = color == WHITE ? FILE_H : NOTHING;
        const bitboard filea2 = color == WHITE ? FILE_A : NOTHING;
        const bitboard rank7 = color == WHITE ? RANK_7 : RANK_2;
        const bitboard pawns_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & rank7;
        const bitboard pawns_not_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & ~rank7;
        const bitboard ennemy = bitboards_[!color];
        const bitboard empty = ~(bitboards_[WHITE]|bitboards_[BLACK]);

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
        if (state_.en_p_square != SQUARE_NB)
        {
            bitboard en_p_candidates = pawns_not_on_rank7 & pawnAttacks_[!color][state_.en_p_square];
            while (en_p_candidates)
            {
                const int sq = poplsb(en_p_candidates);
                movelist.emplace_back(move::create_move((square)sq, state_.en_p_square, move::EN_PASSANT));
            }
        }
    }

    void Board::do_castling(const square& src, const square& dst)
    {
        const square a1sq = side_ == WHITE ? A1 : A8;
        const square h1sq = side_ == WHITE ? H1 : H8;
        const square rookpos = (dst > src) ? h1sq : a1sq;
        const square rookdst = (rookpos == a1sq) ? (square)(dst+1) : (square)(dst-1);

        remove_piece(src, piece_type::KING, side_);
        remove_piece(rookpos, piece_type::ROOK, side_);
        add_piece(dst, piece_type::KING, side_);
        add_piece(rookdst, piece_type::ROOK, side_);
    }

    void Board::undo_castling(const square& src, const square& dst)
    {
        const square a1sq = side_ == WHITE ? A1 : A8;
        const square h1sq = side_ == WHITE ? H1 : H8;
        const square rooksrc = (dst > src) ? h1sq : a1sq;
        const square rookpos = (rooksrc == a1sq) ? (square)(dst+1) : (square)(dst-1);

        remove_piece(dst, piece_type::KING, side_);
        remove_piece(rookpos, piece_type::ROOK, side_);
        add_piece(src, piece_type::KING, side_);
        add_piece(rooksrc, piece_type::ROOK, side_);
    }

    void Board::gen_all(std::vector<move::Move>& movelist)
    {
        const bitboard ennemy = bitboards_[!side_];
        const bitboard allies = bitboards_[side_];
        const bitboard occupied = ennemy|allies;
        const bitboard empty = ~occupied;

        gen_pawn_moves_noisy(movelist, side_);
        gen_KnightMoves(movelist, side_, ennemy);
        gen_queen_bishop_moves(movelist, side_, occupied, ennemy);
        gen_queen_rook_moves(movelist, side_, occupied, ennemy);
        gen_KingMoves(movelist, side_, ennemy);

        gen_pawn_moves_quiet(movelist, side_);
        gen_KnightMoves(movelist, side_, empty);
        gen_queen_bishop_moves(movelist, side_, occupied, empty);
        gen_queen_rook_moves(movelist, side_, occupied, empty);
        gen_KingMoves(movelist, side_, empty);
        gen_castlings(movelist, occupied, side_);
    }
}
