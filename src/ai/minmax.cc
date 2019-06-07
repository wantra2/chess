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

    static void pick_move(const board::Board& board, std::vector<move::Move>& ml, const int index)
    {
        int bestscore = score(board, ml[index]);
        int bestindex = index;
        for (size_t i = index+1; i < ml.size(); ++i)
        {
            int scor = score(board, ml[i]);
            if (scor > bestscore)
            {
                bestscore = scor;
                bestindex = i;
            }
        }
        if (bestindex != index)
        {
            XOR_SWAP(ml[index], ml[bestindex]);
        }
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

        for (size_t i = 0; i < move_list.size(); ++i)
        {
            pick_move(board, move_list, i);

            board.do_move(move_list[i]);
            int score = -1 * quiescence(board, -1 * beta, -1 * alpha);
            board.undo_move(move_list[i]);
            if (score >= beta)
                return beta;
            if (score > alpha)
                alpha = score;
        }
        return alpha;
    }

    int alpha_beta(board::Board& board, int alpha, int beta, int depth, move::Move* best)
    {
        if (depth <= 0)
            return quiescence(board, alpha, beta);

        std::vector<move::Move> move_list;
        board.gen_all(move_list);

        board::bitboard kingBB = board.bitboards_[board::KING]&board.bitboards_[board.side_];
        if (!kingBB)
            return -INFINITE;

        bool incheck = board.is_attacked((board::square)board::getlsb(kingBB), board.side_);
        if (!move_list.size()) 
        {
            if (incheck) 
                return -INFINITE;
            else 
                return 0;            
        }
        if (incheck)
            ++depth;
        
        for (size_t i = 0; i < move_list.size(); ++i)
        {
            pick_move(board, move_list, i);

            board.do_move(move_list[i]);
            int score = -alpha_beta(board, -beta, -alpha, depth-1, best);
            board.undo_move(move_list[i]);

            if (score >= beta)
                return beta;

            if (score > alpha) 
            {
                alpha = score;
                *best = move_list[i];
            }
        }
        return alpha;
    }
}