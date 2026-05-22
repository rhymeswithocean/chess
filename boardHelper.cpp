#include "boardHelper.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include <iostream>
#include <ostream>
#include <string>
#include <cctype>

using std::string;

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

void clearLines(int n) {
    for (int i = 0; i < n; i++)
        std::cout << "\033[1A\033[2K";
    std::cout << std::flush;
}

bool isValidPieceToMove(bool white, int x, int y) {
    // Is there a piece there?
    if (board[x][y] == nullptr) return false;
    // Is the piece on your team?
    if (board[x][y]->getColor() == (white ? 'b' : 'w')) return false; 

    // Is your King safe?
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[r][c] != nullptr &&
              dynamic_cast<King*>(board[r][c]) != nullptr &&
              board[r][c]->getColor() == (white ? 'w' : 'b') &&
              !board[r][c]->isSafe(r, c))
                return false;

    return true;
}

bool validLoc(string loc) {
    if (!std::isalpha(loc[0])) return false;
    if (!std::isdigit(loc[1])) return false;

    if (!(loc[0] >= 'a' && loc[0] <= 'h')) return false;
    if (!(loc[1] >= '1' && loc[1] <= '8')) return false;

    return true;
}

void storeParsedCoord(string coord, int& x, int& y) {
    x = coord[0] - 'a';
    y = coord[1] - '1';
}

string getPiece(bool white, string msg) {
    std::cout << msg << std::endl;
    std::cout << ">>> ";

    string piece;
    std::cin >> piece;

    if (validLoc(piece)) {
        int x, y;
        storeParsedCoord(piece, x, y);
        if (board[x][y]->getColor() == (white ? 'w' : 'b'))
            return piece;
        else
            return getPiece(white, "Invalid Piece. Enter piece to move:");
    } else {
        clearLines(2);
        return getPiece(white, "Invalid Location. Enter piece to move:");
    }
}

string getMove(Piece* piece, string msg) {
    std::cout << msg << std::endl;
    std::cout << ">>> ";

    string move;
    std::cin >> move;

    if (validLoc(move)) {
        int x, y;
        storeParsedCoord(move, x, y);
        if (piece->isValidMove(x, y))
            return move;
        else
            return getPiece(piece, "Invalid Piece. Enter piece to move:");
    } else {
        clearLines(2);
        return getPiece(piece, "Invalid Location. Enter piece to move:");
    }}

void turn(bool white) {
    std::cout << (white ? "WHITE" : "BLACK") << "TURN" << std::endl;
    printBoard();

    string piece = getPiece(white, "Enter ");
    int cX, cY;
    storeParsedCoord(piece, cX, cY);

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
