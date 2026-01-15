#pragma once
#include "chess.hpp"
#include <string>

class Engine {
public:
    std::string version = "0.1.0";
    
    // This will pick the best move
    chess::Move get_best_move(chess::Board& board);
};