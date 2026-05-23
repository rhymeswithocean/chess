#include "boardHelper.h"
#include "piece.h"
#include <iostream>

Piece* board[8][8] = {};
char winner;
Piece* epPawn = nullptr;

int main (int argc, char *argv[]) {
    setup();
    clearBuf();
    bool white = true;
    while (!gameOver()) {
        clearBuf();
        turn(white);
        white = !white;
    }
    clearBuf();
    if (winner)
        std::cout << "CHECKMATE: " << (winner == 'w' ? "WHITE" : "BLACK") << " WINS\n";
    else
        std::cout << "STALEMATE: draw\n";
    std::cout << "Press Enter to quit.";
    std::cin.get();
    return 0;
}

