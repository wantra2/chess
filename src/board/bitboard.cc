#include <iostream>
#include "board/bitboard.hh"

namespace board
{
    void square_set(bitboard& bboard, const int& rank, const int& file)
    {
        if ((rank >= 0 && rank <= 7) && (file >= 0 && file <= 7))
            bboard = bboard | (1ull << to_square(rank, file));
    }

    int getlsb(const bitboard& bboard)
    {
        return __builtin_ctzll(bboard);
    }

    int poplsb(bitboard& bboard)
    {
        int lsb = getlsb(bboard);
        bboard = bboard & (bboard - 1);
        return lsb;
    }

    int popcount(const bitboard& bboard)
    {
        return __builtin_popcountll(bboard);
    }

    bitboard slider_attacks(const square& from_square, const bitboard& occupied, const int offsets[4][2])
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

    void init_magics(const square& square, Magic* table, const bitboard& magic_number, const int offsets[4][2])
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

    internal_bitboards int_bb = {};

    void init_internal_bitboards(internal_bitboards& bb)
    {
        //init pawns attack

        for (int sq = A1; sq < H8; ++sq)
        {
            for (int d = 0; d < 2; ++d)
            {
                square_set(bb.pawnAttacks_[WHITE][sq], rankof((square)sq) + white_pawn_offsets[d][0], fileof((square)sq) + white_pawn_offsets[d][1]);
                square_set(bb.pawnAttacks_[BLACK][sq], rankof((square)sq) + black_pawn_offsets[d][0], fileof((square)sq) + black_pawn_offsets[d][1]);
            }
        }

        //init knight and king attacks

        for (int sq = A1; sq < SQUARE_NB; ++sq)
        {
            for (int d = 0; d < 8; ++d)
            {
                square_set(bb.knightAttacks_[sq], rankof((square)sq) + KnightOffsets[d][0], fileof((square)sq) + KnightOffsets[d][1]);
                square_set(bb.kingAttacks_[sq], rankof((square)sq) + KingOffsets[d][0], fileof((square)sq) + KingOffsets[d][1]);
            }
        }

        //init slide attacks
        bb.bishopMagics_[0].offset = bb.bishopAttacks_;
        bb.rookMagics_[0].offset = bb.rookAttacks_;


        for (int sq = A1; sq < H8; ++sq)
        {
            init_magics((square)sq, bb.bishopMagics_, BishopMagicNumbers[sq], bishop_offsets);
            init_magics((square)sq, bb.rookMagics_, RookMagicNumbers[sq], rook_offsets);
        }
    }
}
