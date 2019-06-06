#include "ai/minmax.hh"

namespace ai
{
    static int quiescence(board::Board& board, int alpha, int beta)
    {
        int score = eval(board);
        if (board.ply_ > 30)
        {
            return score;
        }
        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;
        std::vector<move::Move> move_list;
        board.gen_captures(move_list);
        for (const auto& move : move_list)
        {
            board.do_move(move);
            score = -1 * quiescence(board, -1 * beta, -1 * alpha);
            board.undo_move(move);
            if (score >= beta)
                return beta;
            if (score > alpha)
                alpha = score;
        }
        return alpha;
    }

    static int alpha_beta(board::Board& board, int alpha, int beta, int depth)
    {
        if (depth <= 0)
        {
            return quiescence(board, alpha, beta);
        }
        std::vector<move::Move> move_list;
        board.gen_all(move_list);
        bool can_move = false;
        for (const auto& m : move_list)
        {
            board.do_move(m);
            int score = -alpha_beta(board, -beta, -alpha, depth-1);
            board.undo_move(m);

            if (score > -INFINITE)
                can_move = true;

            if (score >= beta)
                return beta;

            if (score > alpha) 
                alpha = score;
        }

        if (!can_move) 
        {
            if (board.is_attacked((board::square)board::getlsb(board.bitboards_[board::KING]&board.bitboards_[board.side_]), board.side_)) 
                return -INFINITE;
            else 
                return 0;            
        }

        return alpha;
    }

    int root_search(board::Board& board, int alpha, int beta, int depth, move::Move* best_move)
    {
        std::vector<move::Move> ml;
        board.gen_all(ml);
        for (const auto& m : ml)
        {
            board.do_move(m);
            int score = -alpha_beta(board, -beta, -alpha, depth-1);
            board.undo_move(m);
            if (score > alpha)
            {
                alpha = score;
                *best_move = m;
            }
        }

        return alpha;        
    }
}