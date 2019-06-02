#include "ai/minmax.hh"

namespace ai
{
    std::unordered_map<uint64_t, move::Move> h_map;

    static int get_pv(const int depth, board::Board& b)
    {
        int count = 0;
        std::vector<move::Move> ml;
        auto m = h_map.find(b.key_);
        while (m != h_map.end() && count < depth)
        {
            move::Move move = m->second;
            b.do_move(move);
            ml.push_back(move);
            b.pv_[count++] = move;
            m = h_map.find(b.key_);
        }
        while (b.ply_ > 0)
        {
            b.undo_move(ml.back());
            ml.pop_back();
        }
        return count;
    }

    static void pick_next(std::vector<move::Move>& ml, const size_t& index, const board::Board& b)
    {
        int best_score = 0;
        size_t best_index = index;
        for (size_t i = index; i < ml.size(); ++i)
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

    static int alphabeta(int alpha, int beta, int depth, board::Board& b, search_infos& infos, bool do_null)
    {
        if (depth <= 0)
            return quiescence(alpha, beta, b, infos);
        ++infos.nodes;

        bool in_check = b.is_attacked((board::square)board::getlsb(b.bitboards_[board::KING]&b.bitboards_[b.side_]), b.side_);
        if (in_check)
            ++depth;

        int score = -INFINITE;

        if (do_null && !in_check && b.ply_ &&
        ((b.bitboards_[board::QUEEN]|b.bitboards_[board::ROOK]) & b.bitboards_[b.side_]) && depth >=4)
        {
            b.do_move_null();
            score = -alphabeta(-beta, -beta + 1, depth-4, b, infos, false);
            b.undo_move_null();
            if (score >= beta)
                return beta;
        }

        std::vector<move::Move> ml;
        b.gen_all(ml);
        if (ml.size() == 0)
            return -INFINITE;
        bool dont_pick_first = false;
        const auto m = h_map.find(b.key_);
        if (m != h_map.end())
        {
            move::Move move = m->second;
            for (size_t i = 0; i < ml.size(); ++i)
            {
                if (ml[i] == move)
                {
                    move::Move tmp = ml[0];
                    ml[0] = ml[i];
                    ml[i] = tmp;
                    dont_pick_first = true;
                    break;
                }
            }
        }

        score = -INFINITE;
        int save_alpha = alpha;
        move::Move best_move = ml[0];
        for (size_t i = 0; i < ml.size(); ++i)
        {
            if (i != 0 || !dont_pick_first)
            {
                pick_next(ml, i, b);
                dont_pick_first = false;
            }
            b.do_move(ml[i]);
            score = -alphabeta(-beta, -alpha, depth-1, b, infos, true);
            b.undo_move(ml[i]);


            if (score > alpha)
            {
                if (score >= beta)
                {
                    if (b.at(move::move_dst(ml[i])) == board::VOID)
                    {
                        b.killers_[1][b.ply_] = b.killers_[0][b.ply_];
                        b.killers_[0][b.ply_] = ml[i];
                    }
                    return beta;
                }
                alpha = score;
                best_move = ml[i];
            }

        }
        if (alpha != save_alpha)
            h_map[b.key_] = best_move;
        return alpha;
    }

    void search(board::Board& b, search_infos& infos)
    {
        int best_score = -INFINITE;
        move::Move best_move;
        for (int curr_depth = 0; curr_depth < infos.depth; ++curr_depth)
        {
            best_score = alphabeta(-INFINITE, INFINITE, curr_depth, b, infos, true);
            int pv_num = get_pv(curr_depth, b);
            best_move = b.pv_[0];
            infos.best_move = best_move;
            std::cout << "depth " << curr_depth << " score " << best_score << " best move "
                << utils::move_to_uci(best_move) << " nodes " << infos.nodes << "\n";
            std::cout << "principal variation ";
            for (int i = 0; i < pv_num; ++i)
            {
                std::cout << b.pv_[i] << " ";
            }
            std::cout << "\n";
        }
    }
}