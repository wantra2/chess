#include "utils/perft.hh"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "utils/misc.hh"
#include "move/move.hh"

namespace utils
{
    int perft_scnd(board::Board& board, int depth)
    {
        if (!depth)
            return 1;
        auto list = std::vector<move::Move>();
        board.gen_all(list);

        int res = 0;
        for (auto& move : list)
        {
            board.do_move(move);
            res += perft_scnd(board, depth - 1);
            board.undo_move(move);
        }
        return res;
    }

    int perft(std::string perft_file)
    {
        std::ifstream file(perft_file);
        if (!file)
        {
            std::cerr << "File not found";
            return 0;
        }
        std::string perft;
        std::getline(file, perft);

        std::string tmp = perft.substr(0, perft.size() - 2);
        board::Board board(tmp);
        int depth = perft.back() - '0';
        return perft_scnd(board, depth);
    }
}
