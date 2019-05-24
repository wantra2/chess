#include <iostream>

#include "board/board.hh"
#include "board/board-adapter.hh"
#include "board/color.hh"
#include "board/piece-type.hh"

using namespace board;

int main(int, char**) {
    Board tmp;
    uint64_t oui = ((RANK_1 | RANK_8) & ~Ranks[0]) | ((FILE_A | FILE_H) & ~Files[0]);
    std::cout << oui;
}
