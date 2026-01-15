#include "engine.hpp"
#include <algorithm>
#include <iostream>

// --- PeSTO TABLES ---
// Format: A1-H1, A2-H2 ... A8-H8
const int mg_table[6][64] = {
    // Pawn
    { 0,   0,   0,   0,   0,   0,   0,   0,  98,  82,  77,  68,  71,  99, 102,  91,  -6,   6,  10,  45,  56,  25,  22,  -1, -14,  -5,  -3,  12,  17,  -4,  -3, -14, -11,  -4,  13,  14,  15,  14,  -4, -11, -30,  -8,  -4,  -3,  -4,  -3,  -8, -30, -28, -15, -23, -30, -30, -23, -15, -28,   0,   0,   0,   0,   0,   0,   0,   0},
    // Knight
    {-167, -89, -34, -49,  61, -97, -15, -107, -73, -41,  72,  36,  23,  62,   7, -21, -20,  17,  33,   7,  29,  11,  17, -14,  -9,  17,  19,  53,  37,  69,  18,  22, -13,   4,  16,  13,  28,  19,  21,  -8, -23,  -9,  12,  10,  19,  17,  25, -16, -29, -53, -12,  -3,  -1,   0, -14, -31, -48, -28, -29, -99, -28, -31, -33, -18},
    // Bishop
    {-33,   6, -39, -21, -20, -39,   6, -33, -11,  15,  11,  15,  35, -15,  10, -14,  12,   5,  15,  10,  40,  20,   5,  10,  15,  21,  30,  30,  35,  20,  15,  15,  15,  15,  20,  25,  20,  25,  20,  10,  10,  15,  15,  15,  15,  15,  10,   5,  -5,  10,  10,  10,  10,  10,   5,  -2, -15,  -5, -15, -10, -10, -15,  -5, -15},
    // Rook
    { 32,  42,  32,  51,  63,   9,  31,  43,  27,  32,  58,  62,  80,  67,  26,  44,  -5,  19,  26,  36,  17,  45,  61,  16, -24, -11,   7,  26,  24,  35,  -8, -20, -36, -26, -12,  -1,   9,  -7,   6, -23, -45, -25, -16, -17,   3,   0,  -5, -33, -44, -16, -20,  -9,  -1,  11,  -6, -71, -19, -13,   1,  17,  16,   7, -37, -26},
    // Queen
    {-28,   0,  29,  12,  59,  44,  43,  28, -24, -39,  -5,   1, -16,  57,  28,  54, -13, -17,   7,   8,  29,  56,  47,  57, -27, -27, -16, -16,  -1,  17,  -5,  -7, -35, -36, -20,  -3, -14,  15, -15, -27, -21, -30, -39, -40, -35, -33, -14, -28, -22, -23, -30, -37, -37, -30, -19, -25, -33, -28, -24, -43, -18, -32, -20, -41},
    // King
    {-65,  23,  16, -15, -56, -34,   2,  13,  29,  -1, -20,  -7,  -8,  -4, -38, -29,  -9,  24,   2, -16, -20,   6,  22, -22, -17, -20, -12, -27, -30, -25, -14, -36, -49, -12, -27, -39, -46, -44, -33, -51, -14, -14, -22, -46, -44, -30, -15, -27,   1,   7,  -8, -64, -43, -16,   9,   8, -15,  36,  12, -54,   8, -28,  24,  14}
};

const int eg_table[6][64] = {
    // Pawn
    { 0,   0,   0,   0,   0,   0,   0,   0,  13,   8,   8,  10,  13,   0,   2,  -7,   4,   7,  -6,   1,   0,   4,   5,  -5,  -1,   3,  -1,  -1,  -2,  -1,   6,   4,  -5,   3,  -3,   1,   2,  -1,   1,   1,  -2,  -2,   1,   2,   3,   0,  -5,  -4,  -4,  -4,   1,   5,   6,   5,   4,  -5,   0,   0,   0,   0,   0,   0,   0,   0},
    // Knight
    {-58, -38, -13, -28, -31, -27, -63, -99, -25,  -8, -25,  -2,  -9, -25, -24, -52, -24, -20,  10,   9,  -1,  -9, -19, -41, -17,   3,  22,  22,  22,  11,   8, -18, -18,  -6,  16,  25,  16,  17,   4, -14, -23, -3,  -1,  15,  10,  -3, -20, -22, -42, -20, -10,  -5,  -2, -20, -23, -44, -29, -51, -23, -15, -22, -18, -50, -64},
    // Bishop
    {-14, -21, -11,  -8,  -7,  -9, -17, -24,  -8,  -4,   7, -12,  -3, -13,  -4, -14,   2,  -8,   0,  -1,  -2,   6,   0,   4,  -3,   9,  12,   9,  14,  10,   3,   2,  -6,   3,  13,  19,   7,  10,  -3,  -9, -12,  -3,   8,  10,  13,   3,  -7, -15, -14, -18,  -7,  -1,   4,  -9, -15, -27, -23,  -9, -23,  -5, -10, -16, -17, -28},
    // Rook
    { 13,  10,  18,  15,  12,  12,   8,   5,  11,  13,  13,  11,  -3,   3,   8,   3,   7,   7,   7,   5,   4,  -3,  -5,  -3,   1,   1,   1,   1,   2,  -1,  -2,  -1,  -2,  -2,   1,   1,  -3,  -5,  -6,  -2,  -5,   3,   1,  -5,  -3,  -6,  -4,  -9,  -6,   4,   1,  -6,  -6,  -6,   1,  -9,  -9,  -5,   4,  -8,  -5,  -4, -14, -11},
    // Queen
    { -9,  22,  22,  27,  27,  19,  10,  20, -17,   4,  32,  44,  40,  28,  14,   4, -17,  10,  48,  50,  50,  50,  21,   2,  -1, -14,  52,  48,  48,  54,   7, -17, -15, -22,  22,  24,  24,  38, -10, -40, -25, -31,  -2,  -2,  -1, -14, -36, -41, -43, -20, -20, -20, -20, -20, -28, -49, -52, -44, -34, -34, -34, -45, -36, -45},
    // King
    {-74, -35, -18, -18, -11, -15, -38, -76, -12,  17,  14,  17,  17,  38,  23,  11,  10,  17,  23,  15,  20,  45,  44,  13,  -8,  22,  24,  27,  26,  33,  26,   3, -18,  -4,  21,  24,  27,  23,   9, -11, -19,  -3,  11,  21,  23,  16,   7,  -9, -27, -11,   4,  13,  14,   4,  -5, -17, -53, -34, -21, -11, -28, -14, -24, -43}
};

const int mg_val[] = {82, 337, 365, 477, 1025, 0};
const int eg_val[] = {94, 281, 297, 512, 936, 0};

int Engine::evaluate(chess::Board& board) {
    int mg[2] = {0, 0};
    int eg[2] = {0, 0};
    int game_phase = 0;

    for (int i = 0; i < 64; i++) {
        chess::Piece pc = board.at<chess::Piece>(chess::Square(i));
        if (pc == chess::Piece::NONE) continue;

        int c = (int)pc.color();
        int t = (int)pc.type();
        int sq = i;

        // If Black, flip the square index vertically
        if (c == 1) sq ^= 56; 

        mg[c] += mg_val[t] + mg_table[t][sq];
        eg[c] += eg_val[t] + eg_table[t][sq];

        // Phase calculation: Queen=4, Rook=2, Minor=1
        if (t == 1 || t == 2) game_phase += 1;
        else if (t == 3) game_phase += 2;
        else if (t == 4) game_phase += 4;
    }

    int mg_score = mg[(int)board.sideToMove()] - mg[!(int)board.sideToMove()];
    int eg_score = eg[(int)board.sideToMove()] - eg[!(int)board.sideToMove()];

    // Tapered Eval: Blend MG and EG based on phase
    int mg_phase = std::min(24, game_phase);
    int eg_phase = 24 - mg_phase;
    return (mg_score * mg_phase + eg_score * eg_phase) / 24;
}

int Engine::score_move(const chess::Move& move, chess::Board& board) {
    if (board.isCapture(move)) {
        auto victim = board.at<chess::Piece>(move.to());
        auto attacker = board.at<chess::Piece>(move.from());
        return 1000 + (int)victim.type() - (int)attacker.type();
    }
    return 0;
}

int Engine::search(chess::Board& board, int depth, int alpha, int beta) {
    nodes++;
    if (nodes % 2048 == 0) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count() > allocated_time) 
            stop_search = true;
    }

    if (depth <= 0) return evaluate(board);

    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);
    if (moves.empty()) return board.inCheck() ? -100000 : 0;

    std::sort(moves.begin(), moves.end(), [&](const chess::Move& a, const chess::Move& b) {
        return score_move(a, board) > score_move(b, board);
    });

    for (const auto& move : moves) {
        board.makeMove(move);
        int score = -search(board, depth - 1, -beta, -alpha);
        board.unmakeMove(move);

        if (stop_search) return 0;
        if (score >= beta) return beta;
        if (score > alpha) alpha = score;
    }
    return alpha;
}

chess::Move Engine::get_best_move(chess::Board& board, int time_limit_ms) {
    start_time = std::chrono::steady_clock::now();
    allocated_time = time_limit_ms;
    stop_search = false;
    nodes = 0;

    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);
    chess::Move best_move = moves[0];

    for (int depth = 1; depth <= 12; depth++) {
        int alpha = -1000000, beta = 1000000, best_score = -1000000;
        chess::Move temp_best = moves[0];

        for (const auto& move : moves) {
            board.makeMove(move);
            int score = -search(board, depth - 1, -beta, -alpha);
            board.unmakeMove(move);

            if (stop_search) break;
            if (score > best_score) { best_score = score; temp_best = move; }
            alpha = std::max(alpha, score);
        }

        if (stop_search) break;
        best_move = temp_best;
        std::cout << "info depth " << depth << " nodes " << nodes << " score cp " << best_score << std::endl;
    }
    return best_move;
}