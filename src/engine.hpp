#pragma once
#include "chess.hpp"
#include <chrono>
#include <string>

class Engine {
public:
    std::string version = "0.2.0";
    chess::Move get_best_move(chess::Board& board, int time_limit_ms);

private:
    int evaluate(chess::Board& board);
    int search(chess::Board& board, int depth, int alpha, int beta);
    int score_move(const chess::Move& move, chess::Board& board);

    long long nodes = 0;
    bool stop_search = false;
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    int allocated_time;
};