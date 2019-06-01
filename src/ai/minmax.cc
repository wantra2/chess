#include "ai/minmax.hh"

namespace ai
{
    static void pick_next(std::vector<move::Move>& ml, const size_t& index, const board::Board& b)
    {
        int best_score = 0;
        size_t best_index = index;
        for (size_t i = best_index; i < ml.size(); ++i)
        {
            int capture_score = lvv_mva[type(b.at(move::move_src(ml[i])))][type(b.at(move::move_dst(ml[i])))];
            if (capture_score > best_score)
            {
                best_score = capture_score;
                best_index = i;
            }
        }
        move::Move tmp = ml[index];
        ml[index] = ml[best_index];
        ml[best_index] = tmp;
    }

    static int quiescence(int alpha, int beta, board::Board& b, search_infos& infos)
    {
        ++infos.nodes;
        int score = eval(b);
        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;
        std::vector<move::Move> ml;
        b.gen_captures(ml);
        score = -INFINITE;
        for (size_t i = 0; i < ml.size(); ++i)
        {
            pick_next(ml, i, b);
            b.do_move(ml[i]);
            score = -quiescence(-beta, -alpha, b, infos);
            b.undo_move(ml[i]);
            if (score > alpha)
            {
                if (score >= beta)
                    return beta;
                alpha = score;
            }
        }
        return alpha;
    }

    static int alphabeta(int alpha, int beta, int depth, board::Board& b, search_infos& infos)
    {
        if (depth <= 0)
            return quiescence(alpha, beta, b, infos);
        ++infos.nodes;

        std::vector<move::Move> ml;
        b.gen_all(ml);
        if (ml.size() == 0)
            return -INFINITE;
        int score = -INFINITE;
        int best_score = -INFINITE;
        move::Move best_move = ml[0];
        for (size_t i = 0; i < ml.size(); ++i)
        {
            pick_next(ml, i, b);
            b.do_move(ml[i]);
            score = -alphabeta(-beta, -alpha, depth-1, b, infos);
            b.undo_move(ml[i]);

            if (score > best_score)
            {
                best_score = score;
                best_move = ml[i];
                infos.best_move = best_move;
                if (score > alpha)
                {
                    if (score >= beta)
                        return beta;
                    alpha = score;
                }
            }
        }
        return alpha;
    }

    void search(board::Board& b, search_infos& infos)
    {
        int best_score = -INFINITE;
        int alpha = -INFINITE;
        int beta = INFINITE;
        for (int curr_depth = 0; curr_depth < infos.depth; ++curr_depth)
        {
            best_score = alphabeta(alpha, beta, curr_depth, b, infos);
            std::cout << "score " << best_score << " depth " << curr_depth << " nodes " << infos.nodes << "\n";
        }
    }
}