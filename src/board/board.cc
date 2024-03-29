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
//        for (int j = 0; j < 16; ++j)
//        {
//            pv_[j] = 0;
//        }
        
        //hash key
        hash_ = 0ull;
        material_[WHITE] = 0;
        material_[BLACK] = 0;
        position_[WHITE] = 0;
        position_[BLACK] = 0;
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
        for (int i = A1; i < SQUARE_NB; i++)
            pieces_[i] = VOID;

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
        ply_ = 0;
        gamestates.emplace_back(st);
        state_ = st;
        //generate board hash (piece hash is handled in addpiece/remove piece)
        if (side_ == WHITE)
            hash_ ^= h_keys.side_key;
//        if (st.en_p_square != SQUARE_NB)
//            key_ ^= h_keys.piece_keys[VOID][st.en_p_square];
    }

    void Board::gen_castlings(std::vector<move::Move>& movelist, const bitboard& occupied, const int& color)
    {
            const square kingsquare = side_ == WHITE ? E1 : E8;

            if ((state_.castling_rights[color] & 1) &&
                ((occupied & castlings_sq[color][index_00]) == 0))
            {
                move::Move m = move::create_move(kingsquare, (square)(kingsquare+2), move::CASTLING);
                if (is_legal(m))
                    movelist.emplace_back(m);
            }

            if ((state_.castling_rights[color] & 2) &&
                ((occupied & castlings_sq[color][index_000]) == 0))
            {
                auto m = move::create_move(kingsquare, (square)(kingsquare-2), move::CASTLING);
                if (is_legal(m))
                    movelist.emplace_back(m);
            }
    }

    void Board::gen_non_pawn(std::vector<move::Move>& movelist, bitboard attacks, const square& square_from)
    {
        while (attacks)
        {
            const int target_square = poplsb(attacks);
            move::Move m = move::create_move(square_from, (square)target_square);
            if (is_legal(m))
                movelist.emplace_back(m);
        }
    }

    void Board::gen_KnightMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets)
    {
        bitboard knights = bitboards_[KNIGHT] & bitboards_[color];
        while (knights)
        {
            const int from_square = poplsb(knights);
            gen_non_pawn(movelist, int_bb.knightAttacks_[from_square] & targets, (square)from_square);
        }
    }

    void Board::gen_KingMoves(std::vector<move::Move>& movelist, const int& color, const bitboard& targets)
    {
        bitboard king = bitboards_[KING] & bitboards_[color];
        const int from_square = poplsb(king);
        gen_non_pawn(movelist, int_bb.kingAttacks_[from_square] & targets, (square)from_square);
    }

    void Board::gen_queen_bishop_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets)
    {
        bitboard pieces = (bitboards_[QUEEN]|bitboards_[BISHOP]) & bitboards_[color];
        while (pieces)
        {
            const int sq = poplsb(pieces);
            bitboard attacks = int_bb.bishopMagics_[sq].offset[int_bb.bishopMagics_[sq].compute_index(occupied)];
            gen_non_pawn(movelist, attacks & targets, (square)sq);
        }
    }

    void Board::gen_queen_rook_moves(std::vector<move::Move>& movelist, const int& color, const bitboard& occupied, const bitboard& targets)
    {
        bitboard pieces = (bitboards_[QUEEN]|bitboards_[ROOK]) & bitboards_[color];
        while (pieces)
        {
            const int sq = poplsb(pieces);
            bitboard attacks = int_bb.rookMagics_[sq].offset[int_bb.rookMagics_[sq].compute_index(occupied)];
            gen_non_pawn(movelist, attacks & targets, (square)sq);
        }
    }

    bool Board::is_attacked(const square& square, const int& color) const
    {
        const bitboard occupied = bitboards_[WHITE]|bitboards_[BLACK];
        const bitboard bishop_attacks = int_bb.bishopMagics_[square].offset[int_bb.bishopMagics_[square].compute_index(occupied)];
        const bitboard rook_attacks = int_bb.rookMagics_[square].offset[int_bb.rookMagics_[square].compute_index(occupied)];

        return int_bb.pawnAttacks_[color][square] & (bitboards_[PAWN] & bitboards_[!color])
            || int_bb.knightAttacks_[square] & (bitboards_[KNIGHT] & bitboards_[!color])
            || int_bb.kingAttacks_[square] & (bitboards_[KING] & bitboards_[!color])
            || bishop_attacks & ((bitboards_[BISHOP]|bitboards_[QUEEN]) & bitboards_[!color])
            || rook_attacks & ((bitboards_[ROOK]|bitboards_[QUEEN]) & bitboards_[!color]);
    }

    bool Board::is_finished()
    {
        std::vector<move::Move> move_list;
        bitboard unoccupied = bitboards_[WHITE] | bitboards_[BLACK];
        unoccupied = ~unoccupied;
        int opposite_side = side_ == WHITE ? BLACK : WHITE;
        const bitboard capturable = bitboards_[opposite_side];
        const bitboard target = unoccupied | capturable;
        gen_KingMoves(move_list, side_, target);
        const square king = (square)(getlsb(bitboards_[KING] & bitboards_[side_]));
        int act_side = side_;
        gen_all(move_list);
        for (auto& move : move_list)
        {
            do_move_without_listeners(move);
            const square king_tmp = (square)(getlsb(bitboards_[KING] & bitboards_[act_side]));
            if (not is_attacked((square)king_tmp, act_side)) {
                undo_move(move);
                return false;
            }
            undo_move(move);
        }
        if (is_attacked((square)king, side_))
        {
            for (auto l : listeners_) {
                l->on_player_mat(static_cast<Color>(side_));
            }
            for (auto l : listeners_) {
                l->on_game_finished();
            }
            return true;
        }
        return false;
    }

    bool Board::is_pat()
    {
        const square king = (square)(getlsb(bitboards_[KING] & bitboards_[side_]));
        if (is_attacked(king, side_))
            return false;
        std::vector<move::Move> moves;
        gen_all(moves);
        for (auto& move : moves)
        {
            do_move_without_listeners(move);
            const square old_king = (square)(getlsb(bitboards_[KING] & bitboards_[!side_]));
            if (not is_attacked(old_king, !side_)) {
                undo_move(move);
                return false;
            }
            undo_move(move);
        }
        for (auto l : listeners_)
            l->on_player_pat(static_cast<Color>(side_));
        for (auto l : listeners_)
            l->on_game_finished();
        return true;
    }

    bool Board::is_draw()
    {
        int count = 1;
        for (std::size_t i = 0; i < hashes_.size() - 1; ++i)
        {
            for (std::size_t j = i + 1; j < hashes_.size(); ++j)
            {
                if (hashes_[i] == hashes_[j])
                    ++count;
                if (count == 3) {
                    for (auto l : listeners_)
                        l->on_player_pat(static_cast<Color>(side_));
                    for (auto l : listeners_)
                        l->on_game_finished();

                    return true;
                }
            }
            count = 1;
        }
        return false;
    }

    bool Board::is_legal(move::Move move)
    {
        bool in_check = is_attacked((square)getlsb(bitboards_[KING] & bitboards_[side_]), side_);
        if (in_check)
        {
            do_move(move);
            if (is_attacked((square)getlsb(bitboards_[KING] & bitboards_[!side_]), !side_))
            {
                undo_move(move);
                return false;
            }
            undo_move(move);
            return true;
        }
        do_move(move);
        if (is_attacked((square)getlsb(bitboards_[KING] & bitboards_[!side_]), !side_))
        {
            undo_move(move);
            return false;
        }
        undo_move(move);
        return true;
    }


    void Board::gen_pawn_moves_quiet(std::vector<move::Move>& movelist, const int& color)
    {
        const int direction = color == WHITE ? 8 : -8;
        const int two_times_direction = color == WHITE ? 16 : -16;
        const bitboard rank7 = color == WHITE ? RANK_7 : RANK_2;
        const bitboard pawns_not_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & ~rank7;
        const bitboard rank3 = color == WHITE ? RANK_3 : RANK_6;
        const bitboard empty = ~(bitboards_[WHITE]|bitboards_[BLACK]);
        const bitboard pawns_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & rank7;
        
        //promotion
        bitboard prom = (utils::shift(pawns_on_rank7, (direction))) & empty;
        while (prom)
        {
            const int sq = poplsb(prom);
            move::Move m = move::create_move((square)(sq-direction), (square)sq, KNIGHT, move::PROMOTION);
            if (is_legal(m))
                movelist.emplace_back(m);
            m = move::create_move((square)(sq-direction), (square)sq, BISHOP, move::PROMOTION);
            if (is_legal(m))
                movelist.emplace_back(m);
            m = move::create_move((square)(sq-direction), (square)sq, ROOK, move::PROMOTION);
            if (is_legal(m))
                movelist.emplace_back(m);
            m = move::create_move((square)(sq-direction), (square)sq, QUEEN, move::PROMOTION);
            if (is_legal(m))
                movelist.emplace_back(m);
        }
        //standard non-capture
        bitboard push1 = (utils::shift(pawns_not_on_rank7, direction)) & empty;
        bitboard push2 = (utils::shift((push1 & rank3), direction)) & empty;

        while (push1)
        {
            const int sq = poplsb(push1);
            move::Move m = move::create_move((square)(sq-direction), (square)sq);
            if (is_legal(m))
                movelist.emplace_back(m);
        }
        while (push2)
        {
            const int sq = poplsb(push2);
            move::Move m = move::create_move((square)(sq-two_times_direction), (square)sq);
            if (is_legal(m))
                movelist.emplace_back(m);
        }
    }

    void Board::gen_pawn_moves_noisy(std::vector<move::Move>& movelist, const int& color)
    {
        const int direction = color == WHITE ? 8 : -8;
        const bitboard fileh = FILE_H;//color == WHITE ? FILE_H : FILE_A;
        const bitboard filea = FILE_A;//color == BLACK ? FILE_H : FILE_A;
        const bitboard rank7 = color == WHITE ? RANK_7 : RANK_2;
        const bitboard pawns_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & rank7;
        const bitboard pawns_not_on_rank7 = (bitboards_[color] & bitboards_[PAWN]) & ~rank7;
        const bitboard ennemy = bitboards_[!color];

        //promotions cap
        bitboard cap1 = ((utils::shift(pawns_on_rank7, (direction+1)))) & ~filea & ennemy;
        bitboard cap2 = ((utils::shift(pawns_on_rank7, (direction-1)))) & ~fileh & ennemy;

        while (cap1)
        {
            const int sq = poplsb(cap1);
            auto tmp = move::create_move((square)(sq-1-direction), (square)sq, KNIGHT, move::PROMOTION);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
            tmp = move::create_move((square)(sq-1-direction), (square)sq, BISHOP, move::PROMOTION);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
            tmp = move::create_move((square)(sq-1-direction), (square)sq, ROOK, move::PROMOTION);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
            tmp = move::create_move((square)(sq-1-direction), (square)sq, QUEEN, move::PROMOTION);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
        }
        while (cap2)
        {
            const int sq = poplsb(cap2);
            auto tmp = move::create_move((square)(sq+1-direction), (square)sq, KNIGHT, move::PROMOTION);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
            tmp = move::create_move((square)(sq+1-direction), (square)sq, BISHOP, move::PROMOTION);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
            tmp = move::create_move((square)(sq+1-direction), (square)sq, ROOK, move::PROMOTION);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
            tmp = move::create_move((square)(sq+1-direction), (square)sq, QUEEN, move::PROMOTION);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
        }
        
        //captures
        bitboard cap3 = (utils::shift(pawns_not_on_rank7, (direction+1)) & ~filea) & ennemy;
        bitboard cap4 = (utils::shift(pawns_not_on_rank7, (direction-1)) & ~fileh) & ennemy;

        while (cap3)
        {
            const int sq = poplsb(cap3);
            auto tmp = move::create_move((square)(sq-1-direction), (square)sq);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
        }
        while (cap4)
        {
            const int sq = poplsb(cap4);
            auto tmp = move::create_move((square)(sq+1-direction), (square)sq);
            if (is_legal(tmp))
                movelist.emplace_back(tmp);
        }
        //en passant
        if (state_.en_p_square != SQUARE_NB)
        {
            bitboard en_p_candidates = pawns_not_on_rank7 & int_bb.pawnAttacks_[!color][state_.en_p_square];
            while (en_p_candidates)
            {
                const int sq = poplsb(en_p_candidates);
                auto tmp = move::create_move((square)sq, state_.en_p_square, move::EN_PASSANT);
                if (is_legal(tmp))
                    movelist.emplace_back(tmp);
            }
        }
    }

    void Board::do_castling(const square& src, const square& dst) {
        const square a1sq = side_ == WHITE ? A1 : A8;
        const square h1sq = side_ == WHITE ? H1 : H8;
        const square rookpos = (dst > src) ? h1sq : a1sq;
        const square rookdst = (rookpos == a1sq) ? (square) (dst + 1) : (square) (dst - 1);

        if (rookpos == h1sq) {
            for (auto l : listeners_) {
                l->on_kingside_castling((Color) side_);
            }
        } else {
            for (auto l : listeners_) {
                l->on_queenside_castling((Color) side_);
            }
        }
        remove_piece(src, piece_type::KING, side_);
        remove_piece(rookpos, piece_type::ROOK, side_);
        add_piece(dst, piece_type::KING, side_);
        add_piece(rookdst, piece_type::ROOK, side_);
    }

    void Board::do_castling_without_listeners(const square& src, const square& dst) {
        const square a1sq = side_ == WHITE ? A1 : A8;
        const square h1sq = side_ == WHITE ? H1 : H8;
        const square rookpos = (dst > src) ? h1sq : a1sq;
        const square rookdst = (rookpos == a1sq) ? (square) (dst + 1) : (square) (dst - 1);

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

    void Board::gen_captures(std::vector<move::Move>& movelist)
    {
        const bitboard ennemy = bitboards_[!side_];
        const bitboard allies = bitboards_[side_];
        const bitboard occupied = ennemy|allies;

        gen_pawn_moves_noisy(movelist, side_);
        gen_KnightMoves(movelist, side_, ennemy);
        gen_queen_bishop_moves(movelist, side_, occupied, ennemy);
        gen_queen_rook_moves(movelist, side_, occupied, ennemy);
        gen_KingMoves(movelist, side_, ennemy);
    }
}
