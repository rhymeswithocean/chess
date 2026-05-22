#include "boardHelper.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include <iostream>

void print(const string& s) {
    std::cout << s;
}

void printBoard() {
    for (int c = 7; c >= 0; c--) {
        for (int r = 0; r <= 7; r++) {
            if (board[r][c]) std::cout << *board[r][c] << " ";
            else std::cout << ".. ";
        }
        std::cout << "\n";
    }
}

void clearBuf() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void setup() {
    // Rooks
    board[0][0] = new Rook('w');
    board[7][0] = new Rook('w');

    board[0][7] = new Rook('b');
    board[7][7] = new Rook('b');

    // Knights
    board[1][0] = new Knight('w');
    board[6][0] = new Knight('w');

    board[1][7] = new Knight('b');
    board[6][7] = new Knight('b');

    // Bishops
    board[2][0] = new Bishop('w');
    board[5][0] = new Bishop('w');

    board[2][7] = new Bishop('b');
    board[5][7] = new Bishop('b');

    // Pawns
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Pawn('w');
        board[i][6] = new Pawn('b');
    }

    // King
    board[4][0] = new King('w');
    board[4][7] = new King('b');

    // Queens
    board[3][0] = new Queen('w');
    board[3][7] = new Queen('b');
}
