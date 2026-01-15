#include <iostream>
#include "engine.hpp"

int main() {
    Engine sockfish_v1;
    chess::Board board;

    std::cout << "Testing Engine Version: " << sockfish_v1.version << std::endl;

    // Simulate a quick test game
    for(int i = 0; i < 5; i++) {
        chess::Move m = sockfish_v1.get_best_move(board);
        board.makeMove(m);
        std::cout << "Move " << i+1 << ": " << chess::uci::moveToUci(m) << std::endl;
    }

    std::cout << "Final FEN: " << board.getFen() << std::endl;
    return 0;
}