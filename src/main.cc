#include <iostream>

#include "board/board.hh"
#include "board/board-adapter.hh"
#include "board/color.hh"
#include "board/piece-type.hh"

using namespace board;

int main(int, char**) {
    bitboard prout = 0;
    std::cout << poplsb(prout);
}
