#include "utils/misc.hh"

#include <iostream>
#include <string>
#include <cstdint>
#include <list>
#include <cstdlib>

#include "board/board.hh"
#include "board/color.hh"
#include "board/piece-type.hh"
#include "board/bitboard.hh"

namespace utils
{
    void pretty_print(const board::Board& board)
    {
        int index = 64;
        board::bitboard bit = 0x8000000000000000;

        while (index > 0)
        {
            if (bit & (board.bitboards_[board::BLACK]
                       | board.bitboards_[board::WHITE]))
            {
                std::string color = (board.bitboards_[board::BLACK] & bit) ?
                    "\e[91m\e[1m" : "\e[1m";
                if (bit & board.bitboards_[board::PAWN])
                    std::cout << color << " P " << "\e[0m";
                else if (bit & board.bitboards_[board::ROOK])
                    std::cout << color << " R " << "\e[0m";
                else if (bit & board.bitboards_[board::BISHOP])
                    std::cout << color << " B " << "\e[0m";
                else if (bit & board.bitboards_[board::KING])
                    std::cout << color << " K " << "\e[0m";
                else if (bit & board.bitboards_[board::QUEEN])
                    std::cout << color << " Q " << "\e[0m";
                else if (bit & board.bitboards_[board::KNIGHT])
                    std::cout << color << " N " << "\e[0m";
            }

            else
            {
                std::cout << " . ";
            }
            index--;
            bit >>= 1;
            if (index % 8 == 0)
                std::cout << '\n';
        }
    }


    void print_bitboard(const board::bitboard& bb)
    {
        int index = 63;
        std::list<std::string> s;
        while (index >= 0)
        {
            if (((1ull << index) & bb))
                s.push_front("| X |");
            else
                s.push_front("|   |");

            if (index % 8 == 0)
            {
                s.push_front("\n");
            }
            --index;
        }
        for (auto str : s)
            std::cout << str;
        std::cout << '\n';
    }

    board::piece_type char_to_piece(const char& c)
    {
        switch (c)
        {
        case 'p':
            return board::PAWN;
            break;
        case 'P':
            return board::PAWN;
            break;
        case 'n':
            return board::KNIGHT;
            break;
        case 'N':
            return board::KNIGHT;
            break;
        case 'b':
            return board::BISHOP;
            break;
        case 'B':
            return board::BISHOP;
            break;
        case 'r':
            return board::ROOK;
            break;
        case 'R':
            return board::ROOK;
            break;
        case 'q':
            return board::QUEEN;
            break;
        case 'Q':
            return board::QUEEN;
            break;
        case 'k':
            return board::KING;
            break;
        case 'K':
            return board::KING;
            break;
        default:
            break;
        }
        return board::PAWN;
    }

    static std::string square_to_uci(const board::square& sq)
    {
        std::string tbr = "";
        tbr += board::fileof(sq)+'a';
        tbr += board::rankof(sq)+'1';
        return tbr;
    }

    static std::string prom_to_char(const board::piece_type& piece)
    {
        switch (piece)
        {
        case board::KNIGHT:
            return "n";
            break;
        case board::BISHOP:
            return "b";
            break;
        case board::ROOK:
            return "r";
            break;
        case board::QUEEN:
            return "q";
            break;
        default:
            return "";
            break;
        }
        return "";
    }

    static board::piece_type char_to_prom(const char& c)
    {
        switch (c)
        {
        case 'n':
            return board::KNIGHT;
        case 'b':
            return board::BISHOP;
        case 'r':
            return board::ROOK;
        case 'q':
            return board::QUEEN;
        default:
            break;
        }
        return board::KNIGHT;
    }

    std::string move_to_uci(const move::Move& m)
    {
        std::string prom = move::is_promotion(m) ? prom_to_char(move::promotion_type(m)) : "";
        return square_to_uci(move::move_src(m))+square_to_uci(move::move_dst(m))+prom;
    }


    move::Move uci_to_move(const std::string& uci_move, const board::Board& b)
    {
        int src_file = uci_move[0] - 'a';
        int src_rank = uci_move[1] - '1';
        int dst_file = uci_move[2] - 'a';
        int dst_rank = uci_move[3] - '1';
        board::square src_square = board::to_square(src_rank, src_file);
        board::square dst_square = board::to_square(dst_rank, dst_file);
        board::piece_type src_pt = board::type(b.at(src_square));
        if (uci_move[4])
            return move::create_move(src_square, dst_square, char_to_prom(uci_move[5]), move::PROMOTION);
        if (src_pt == board::KING && abs(dst_file - src_file > 1))
            return move::create_move(src_square, dst_square, move::CASTLING);
        if (dst_square == b.state_.en_p_square && src_pt == board::PAWN)
            return move::create_move(src_square, dst_square, move::EN_PASSANT);
        return move::create_move(src_square, dst_square);
    }
}
