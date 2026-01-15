#include <iostream>
#include <vector>
#include <string>
#include "engine.hpp"

int main() {
    Engine sockfish;
    chess::Board board;
    std::vector<std::string> pgn_moves;

    std::cout << "--- Sockfish v0.2.0 Self-Play Match ---" << std::endl;

    while (true) {
        // Correct check: first is Reason, second is Result
        auto game_status = board.isGameOver();
        chess::GameResultReason reason = game_status.first;
        chess::GameResult result = game_status.second;

        if (reason != chess::GameResultReason::NONE) {
            std::cout << "\n================================" << std::endl;
            std::cout << "GAME OVER!" << std::endl;

            // --- START PGN OUTPUT ---
            std::cout << "\n[Event \"Sockfish Self-Play\"]" << std::endl;
            std::cout << "[Site \"Localhost\"]" << std::endl;
            std::cout << "[White \"Sockfish " << sockfish.version << "\"]" << std::endl;
            std::cout << "[Black \"Sockfish " << sockfish.version << "\"]" << std::endl;
            
            // Determine PGN Result string
            std::string result_str = "*";
            if (result == chess::GameResult::DRAW) {
                result_str = "1/2-1/2";
            } else if (result == chess::GameResult::WIN) {
                // If the game ended on White's turn, Black won (and vice versa)
                result_str = (board.sideToMove() == chess::Color::WHITE ? "0-1" : "1-0");
            }
            
            std::cout << "[Result \"" << result_str << "\"]" << std::endl << std::endl;

            // Loop through stored moves and format them
            for (size_t i = 0; i < pgn_moves.size(); i++) {
                if (i % 2 == 0) {
                    std::cout << (i / 2 + 1) << ". ";
                }
                std::cout << pgn_moves[i] << " ";
            }
            std::cout << result_str << std::endl;
            // --- END PGN OUTPUT ---
            
            break;
        }

        // 1. Engine thinks
        chess::Move best_move = sockfish.get_best_move(board, 500);
        
        if (best_move == chess::Move()) {
            std::cout << "No move found." << std::endl;
            break;
        }

        // 2. CRITICAL: Get SAN before making the move to avoid invalid FENs
        std::string san_move = chess::uci::moveToSan(board, best_move);
        pgn_moves.push_back(san_move);

        // 3. Update the internal board
        board.makeMove(best_move);

        // 4. Live update for the console
        std::cout << "Move " << pgn_moves.size() << ": " << san_move << std::endl;
    }

    return 0;
}