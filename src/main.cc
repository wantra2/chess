#include <iostream>

#include "board/board.hh"
#include "board/board-adapter.hh"
#include "board/color.hh"
#include "board/piece-type.hh"

int main(int, char**) {
    board::Board tmp = board::Board();
    auto adapt = board::BoardAdapter(tmp);

    std::cout << "Hello World\n";
}
