#include "utils/misc.hh"

#include <iostream>
#include <string>
#include <cstdint>
#include <list>

#include "board/board.hh"
#include "board/color.hh"
#include "board/piece-type.hh"
#include "board/bitboard.hh"

namespace utils
{
    void pretty_print(board::Board board)
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


    void print_bitboard(board::bitboard bb)
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
    }
}
