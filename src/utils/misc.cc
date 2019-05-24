#include "utils/misc.hh"

#include <iostream>
#include <string>

#include "board/board.hh"
#include "board/color.hh"
#include "board/piece-type.hh"
#include "board/bitboard.hh"

namespace utils
{
    void pretty_print(board::Board board)
    {
        int index = 0;
        board::bitboard bit = 0x1;

        while (index < 64)
        {
            if (bit & (board.get_bitboard(board::Color::BLACK)
                       | board.get_bitboard(board::Color::WHITE)))
            {
                std::string color = (board.get_bitboard(board::Color::BLACK) & bit) ?
                    "\e[91m\e[1m" : "\e[1m";
                if (bit & board.get_bitboard(board::piece_type::PAWN))
                    std::cout << color << " P " << "\e[0m";
                else if (bit & board.get_bitboard(board::piece_type::ROOK))
                    std::cout << color << " R " << "\e[0m";
                else if (bit & board.get_bitboard(board::piece_type::BISHOP))
                    std::cout << color << " B " << "\e[0m";
                else if (bit & board.get_bitboard(board::piece_type::KING))
                    std::cout << color << " K " << "\e[0m";
                else if (bit & board.get_bitboard(board::piece_type::QUEEN))
                    std::cout << color << " Q " << "\e[0m";
                else if (bit & board.get_bitboard(board::piece_type::KNIGHT))
                    std::cout << color << " N " << "\e[0m";
            }

            index++;
            bit <<= 1;
            if (index % 8 == 0)
                std::cout << '\n';
        }
    }
}
