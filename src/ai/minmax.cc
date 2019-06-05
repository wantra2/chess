#include "ai/minmax.hh"

namespace ai
{
    int alpha_beta(board::Board& board, int alpha, int beta, int depth, move::Move bestest[16])
    {
        if (depth == 0)
        {
            return eval(board);
        }
        std::vector<move::Move> move_list;
        board.gen_all(move_list);
        int score = -INFINITE;
        for (const auto& move : move_list)
        {
            board.do_move(move);
            int tmp_score = -1 * alpha_beta(board, -1 * beta, -1 * alpha, depth - 1, bestest);
            board.undo_move(move);
            if (tmp_score > score)
            {
                score = tmp_score;
                if (score > alpha)
                {
                    alpha = score;
                    bestest[depth] = move;
                    if (alpha >= beta)
                    {
                        return score;
                    }
                }
            }
        }
        return score;
    }

    move::Move search(board::Board& board, int depth)
    {
        int score = -INFINITE;
        move::Move bestest[16];
        move::Move best_move;
        for (int i = 0; i < depth; ++i)
        {
            score = alpha_beta(board, -INFINITE, INFINITE, i, bestest);
            best_move = bestest[i];
            std::cout << "best move: " << best_move << " score: " << score << '\n';
        }
        return bestest[0];
    }
}