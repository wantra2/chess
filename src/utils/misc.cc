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
        switch (sq)
        {
        case board::A1:
            return "a1";
            break;
        case board::A2:
            return "a2";
            break;
        case board::A3:
            return "a3";
            break;
        case board::A4:
            return "a4";
            break;
        case board::A5:
            return "a5";
            break;
        case board::A6:
            return "a6";
            break;
        case board::A7:
            return "a7";
            break;
        case board::A8:
            return "a8";
            break;
        case board::B1:
            return "b1";
            break;
        case board::B2:
            return "b2";
            break;
        case board::B3:
            return "b3";
            break;
        case board::B4:
            return "b4";
            break;
        case board::B5:
            return "b5";
            break;
        case board::B6:
            return "b6";
            break;
        case board::B7:
            return "b7";
            break;
        case board::B8:
            return "b8";
            break;
        case board::C1:
            return "c1";
            break;
        case board::C2:
            return "c2";
            break;
        case board::C3:
            return "c3";
            break;
        case board::C4:
            return "c4";
            break;
        case board::C5:
            return "c5";
            break;
        case board::C6:
            return "c6";
            break;
        case board::C7:
            return "c7";
            break;
        case board::C8:
            return "c8";
            break;
        case board::D1:
            return "d1";
            break;
        case board::D2:
            return "d2";
            break;
        case board::D3:
            return "d3";
            break;
        case board::D4:
            return "d4";
            break;
        case board::D5:
            return "d5";
            break;
        case board::D6:
            return "d6";
            break;
        case board::D7:
            return "d7";
            break;
        case board::D8:
            return "d8";
            break;
        case board::E1:
            return "e1";
            break;
        case board::E2:
            return "e2";
            break;
        case board::E3:
            return "e3";
            break;
        case board::E4:
            return "e4";
            break;
        case board::E5:
            return "e5";
            break;
        case board::E6:
            return "e6";
            break;
        case board::E7:
            return "e7";
            break;
        case board::E8:
            return "e8";
            break;
        case board::F1:
            return "f1";
            break;
        case board::F2:
            return "f2";
            break;
        case board::F3:
            return "f3";
            break;
        case board::F4:
            return "f4";
            break;
        case board::F5:
            return "f5";
            break;
        case board::F6:
            return "f6";
            break;
        case board::F7:
            return "f7";
            break;
        case board::F8:
            return "f8";
            break;
        case board::G1:
            return "g1";
            break;
        case board::G2:
            return "g2";
            break;
        case board::G3:
            return "g3";
            break;
        case board::G4:
            return "g4";
            break;
        case board::G5:
            return "g5";
            break;
        case board::G6:
            return "g6";
            break;
        case board::G7:
            return "g7";
            break;
        case board::G8:
            return "g8";
            break;
        case board::H1:
            return "h1";
            break;
        case board::H2:
            return "h2";
            break;
        case board::H3:
            return "h3";
            break;
        case board::H4:
            return "h4";
            break;
        case board::H5:
            return "h5";
            break;
        case board::H6:
            return "h6";
            break;
        case board::H7:
            return "h7";
            break;
        case board::H8:
            return "h8";
            break;
        default:
            break;
        }
        return "";
    }

    std::string move_to_uci(const move::Move& m)
    {
        return square_to_uci(move::move_src(m))+square_to_uci(move::move_dst(m));
    }
}
