#include "engine.hpp"
#include <random>

chess::Move Engine::get_best_move(chess::Board& board) {
    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);

    if (moves.size() == 0) {
        return chess::Move(); 
    }

    // Random move selection for v0.1.0
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, (int)moves.size() - 1);

    return moves[dist(gen)];
}