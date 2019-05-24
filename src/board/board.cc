#include "board/board.hh"

#include "bitboard.hh"

#include <iostream>

namespace board
{
    Board::Board()
    {
        generate_board();
        init_Knight_and_KingAttacks();
        init_slide_attacks();
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

    inline bitboard& Board::get_bitboard(piece_type type)
    {
        return bitboards_[(int)type];
    }

    inline bitboard& Board::get_bitboard(Color color)
    {
        return bitboards_[(int)color];
    }

    void Board::init_Knight_and_KingAttacks()
    {
        const int KnightOffsets[8][2] = {{-2,-1}, {-2, 1}, {-1,-2}, {-1, 2},{ 1,-2}, { 1, 2}, { 2,-1}, { 2, 1}};
        const int KingOffsets[8][2]   = {{-1,-1}, {-1, 0}, {-1, 1}, { 0,-1},{ 0, 1}, { 1,-1}, { 1, 0}, { 1, 1}};
        for (int sq = board::A1; sq < SQUARE_NB; ++sq)
        {
            for (int d = 0; d < 8; ++d)
            {
                square_set(knightAttacks_[sq], rankof(sq) + KnightOffsets[d][0], fileof(sq) + KnightOffsets[d][1]);
                square_set(kingAttacks_[sq], rankof(sq) + KingOffsets[d][0], fileof(sq) + KingOffsets[d][1]);
            }
        }
    }

    void Board::init_slide_attacks()
    {
        bishopMagics_[0].offset = bishopAttacks_;
        rookMagics_[0].offset = rookAttacks_;

        const int bishop_offsets[4][2] = {{-1,-1}, {-1, 1}, { 1,-1}, { 1, 1}};
        const int rook_offsets[4][2]   = {{-1, 0}, { 0,-1}, { 0, 1}, { 1, 0}};

        for (int square = A1; square < H8; ++square)
        {
            init_magics(square, bishopMagics_, BishopMagicNumbers[square], bishop_offsets);
            init_magics(square, rookMagics_, RookMagicNumbers[square], rook_offsets);
        }
    }

    bitboard Board::slider_attacks(const int from_square, const bitboard& occupied, const int offsets[4][2])
    {
        int rank, file;
        bitboard tbr = 0;
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
                if (occupied & (1 << to_square(rank, file)))
                    break;
            }
        }
        return tbr;
    }

    void Board::init_magics(const int square, Magic* table, const bitboard& magic_number, const int offsets[4][2])
    {
        const bitboard edgesmask = ((RANK_1 | RANK_8) & ~Ranks[rankof(square)]) | ((FILE_A | FILE_H) & ~Files[fileof(square)]);
        table[square].magic_number = magic_number;
        table[square].mask = slider_attacks(square, 0, offsets) & ~edgesmask;
        table[square].shift_needed = 64 - popcount(table[square].mask);
        if (square < H8)
            table[square + 1].offset = table[square].offset + (1 << popcount(table[square].mask));
        bitboard occupied = 0;
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

    void Board::gen_KingMoves(std::vector<move::Move>& movelist, bitboard king, const bitboard& targets)
    {
        int from_square = poplsb(king);
        gen_non_pawn(movelist, kingAttacks_[from_square] & targets, from_square);
    }

    void Board::gen_queen_bishop_moves(std::vector<move::Move>& movelist, bitboard pieces, const bitboard& occupied, const bitboard& targets)
    {
        while (pieces)
        {
            int sq = poplsb(pieces);
            bitboard attacks = bishopAttacks_[bishopMagics_[sq].offset[bishopMagics_[sq].compute_index(occupied)]];
            gen_non_pawn(movelist, attacks & targets, sq);
        }
    }

     void Board::gen_queen_rook_moves(std::vector<move::Move>& movelist, bitboard pieces, const bitboard& occupied, const bitboard& targets)
    {
        while (pieces)
        {
            int sq = poplsb(pieces);
            bitboard attacks = rookAttacks_[rookMagics_[sq].offset[rookMagics_[sq].compute_index(occupied)]];
            gen_non_pawn(movelist, attacks & targets, sq);
        }
    }

    static inline bool check_promote(const bitboard& piece, Color color)
    {
        EdgesMask limit = (bool)color ? EdgesMask::DOWN : EdgesMask::UP;
        return (piece & limit) != 0;
    }

    void Board::gen_pawn_moves(std::vector<move::Move>& movelist, Color color)
    {
        int direction = (bool)color ? -8 : 8; // The enum color states that WHITE = false, BLACK = true
        bitboard starting = (bool)color ? 0x00FF000000000000 : 0x000000000000FF00;

        bitboard pieces = get_bitboard(color) & get_bitboard(piece_type::PAWN);
        bitboard all = get_bitboard(Color::BLACK) & get_bitboard(Color::WHITE);

        bitboard bit = 1;
        for (int ite = 0; ite < 64; ite++, bit <<= 1)
        {
            if(pieces & bit)
            {
                std::cout << "Found: " << ite << '\n';
                check_pawn_capture(ite, bit, color, movelist);
                bitboard moved = bit << direction;
                if ((moved & all) != 0)
                    continue;
                move::MoveType type = check_promote(moved, color) ?
                    move::MoveType::PROMOTION : move::MoveType::NORMAL;
                std::cout << "TYPE: " << type << '\n';
                movelist.emplace_back(move::create_move((square)ite,
                                                        (square)(ite + direction)
                                                        , piece_type::PAWN, type));
                moved <<= direction;
                if ((bit & starting) && !(moved & all))
                {
                    movelist.emplace_back(move::create_move((square)ite,
                                                            (square)(ite + 2 * direction),
                                                            piece_type::PAWN,
                                                            move::MoveType::EN_PASSANT));

                }
            }
        }
    }

    void Board::check_pawn_capture(const int position, bitboard& piece,
                                   Color color, std::vector<move::Move>& movelist)
    {
        int direction = (bool)color ? -1 : 1;
        bitboard enemies = get_bitboard((Color)(!(bool)color));

        bitboard tmp = (piece << (direction * 9) & enemies);
        if (tmp)
        {
            move::MoveType type = check_promote(tmp, color) ?
                move::MoveType::PROMOTION : move::MoveType::NORMAL;
            movelist.emplace_back(move::create_move((square)position,
                                               (square)(position + direction * 9)
                                               , piece_type::PAWN, type));
        }

        if ((tmp = (piece << (direction * 7) & enemies)))
        {
            move::MoveType type = check_promote(tmp, color) ?
                move::MoveType::PROMOTION : move::MoveType::NORMAL;
            movelist.emplace_back(move::create_move((square)position,
                                                    (square)(position + direction * 7)
                                                    , piece_type::PAWN, type));
        }
    }

}
