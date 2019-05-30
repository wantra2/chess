#include "ai/minmax.hh"

namespace ai
{

    int alphabetamax(board::Board& b, int alpha, int beta, int depth)
    {
        if (depth <= 0)
            return eval(b);

        std::vector<move::Move> ml;
        int score;

        b.gen_all(ml);
        for (const auto m : ml)
        {
            b.do_move(m);
            score = alphabetamin(b, alpha, beta, depth-1);
            b.undo_move(m);
            if (score >= beta)
                return beta;
            if (score > alpha)
                alpha = score;
        }
        return alpha;
    }

    int alphabetamin(board::Board& b, int alpha, int beta, int depth)
    {
        if (depth <= 0)
            return eval(b);

        std::vector<move::Move> ml;
        int score;

        b.gen_all(ml);
        for (const auto m : ml)
        {
            b.do_move(m);
            score = alphabetamax(b, alpha, beta, depth-1);
            b.undo_move(m);
            if (score <= alpha)
                return alpha;
            if (score < alpha)
                beta = score;
        }
        return beta;
    }
}