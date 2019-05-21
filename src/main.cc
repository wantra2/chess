#include <iostream>

#include "board/board.hh"
#include "board/board-adapter.hh"
#include "board/chessboard-interface.hh"

int main(int, char**) {
    board::Board tmp = board::Board();
    auto adapt = board::BoardAdapter(tmp);

    board::Position pos = board::Position(board::File::A, board::Rank::ONE);
    std::cout << (int)(*(adapt[pos])).first << std::endl;
    std::cout << "Hello, world!\n";
}
