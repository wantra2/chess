#include "ai/minmax.hh"

namespace ai
{
    static int score(const board::Board& board, const move::Move& move)
    {
        int res = 0;
        const board::square src = move::move_src(move);
        const board::square dst = move::move_dst(move);
        const board::piece_type_with_color captured = board.pieces_[dst];
        const board::piece_type_with_color piece = board.pieces_[src];
        res -= pieceSquareTable[type(piece)][relative(src, board.side_)];
        res += pieceSquareTable[type(piece)][relative(dst, board.side_)];
        if (captured)
        {
            res += materials[type(captured)];
            res += pieceSquareTable[type(captured)][relative(dst, !board.side_)];
        }
        return res;
    }

    #define XOR_SWAP(a, b) a = a ^ b; b = a ^ b; a = a ^ b;

    static void pick_move(const board::Board& board, std::vector<move::Move>& ml)
    {
        int bestscore = -INFINITE;
        int bestindex = 0;
        for (size_t i = 0; i < ml.size(); ++i)
        {
            if (score(board, ml[i]) > bestscore)
            {
                bestscore = score(board, ml[i]);
                bestindex = i;
            }
        }
        XOR_SWAP(ml[0], ml[bestindex]);
    }

    static int quiescence(board::Board& board, int alpha, int beta)
    {
        int score = eval(board);
        
        if (board.ply_ >= 20)
            return score;

        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;

        std::vector<move::Move> move_list;
        board.gen_captures(move_list);
        for (const auto& move : move_list)
        {
            pick_move(board, move_list);

            board.do_move(move);
            int score = -1 * quiescence(board, -1 * beta, -1 * alpha);
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
            return quiescence(board, alpha, beta);

        std::vector<move::Move> move_list;
        board.gen_all(move_list);

        if (!move_list.size()) 
        {
            if (board.is_attacked((board::square)board::getlsb(board.bitboards_[board::KING]&board.bitboards_[board.side_]), board.side_)) 
                return -INFINITE;
            else 
                return 0;            
        }
        
        for (const auto& m : move_list)
        {
            pick_move(board, move_list);

            board.do_move(m);
            int score = -alpha_beta(board, -beta, -alpha, depth-1);
            board.undo_move(m);

            if (score >= beta)
                return beta;

            if (score > alpha) 
                alpha = score;
        }
        return alpha;
    }

    int root_search(board::Board& board, int alpha, int beta, int depth, move::Move* best_move)
    {
        std::vector<move::Move> ml;
        board.gen_all(ml);
        for (const auto& m : ml)
        {
            pick_move(board, ml);

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