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

using std::string;

extern char winner;

void print(const string& s) {
    std::cout << s;
}

void printBoard() {
    for (int c = 7; c >= 0; c--) {
        std::cout << c + 1 << " ";
        for (int r = 0; r <= 7; r++) {
            if (board[r][c]) std::cout << *board[r][c] << " ";
            else std::cout << ".. ";
        }
        std::cout << "\n";
    }
std::cout << "  a  b  c  d  e  f  g  h" << std::endl << std::endl;
}

void clearBuf() {
    std::cout << "\033[2J\033[H" << std::flush;
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

bool validFmt(string fmt) {
    if (fmt.size() < 4) return false;
    if (!(fmt[0] >= 'a' && fmt[0] <= 'h')) return false;
    if (!(fmt[1] >= '1' && fmt[1] <= '8')) return false;
    if (!(fmt[2] >= 'a' && fmt[2] <= 'h')) return false;
    if (!(fmt[3] >= '1' && fmt[3] <= '8')) return false;
    if (fmt.size() >= 5 && (fmt[3] == '1' || fmt[3] == '8')) {
        char p = fmt[4];
        if (p != 'Q' && p != 'r' && p != 'b' && p != 'k') return false;
    }
    return true;
}

void storeParsedCoords(string coord, int& cX, int& cY, int& x, int& y) {
    cX = coord[0] - 'a';
    cY = coord[1] - '1';
    x =  coord[2] - 'a';
    y =  coord[3] - '1';
}

bool leavesKingInCheck(int cX, int cY, int x, int y) {
    Piece* moving  = board[cX][cY];
    Piece* target  = board[x][y];
    char   color   = moving->getColor();

    // En passant: pawn moves diagonally to an empty square — side-captured pawn must also vanish
    Piece* epCaptured = nullptr;
    if (dynamic_cast<Pawn*>(moving) && cX != x && target == nullptr) {
        epCaptured = board[x][cY];
        board[x][y] = nullptr;
    }

    board[x][y]     = moving;
    board[cX][cY] = nullptr;

    bool inCheck = false;
    for (int r = 0; r < 8 && !inCheck; r++)
        for (int c = 0; c < 8 && !inCheck; c++)
            if (board[r][c] && dynamic_cast<King*>(board[r][c]) &&
                board[r][c]->getColor() == color &&
                !board[r][c]->isSafe(r, c))
                inCheck = true;

    board[cX][cY] = moving;
    board[x][y]     = target;
    if (epCaptured) board[x][cY] = epCaptured;

    return inCheck;
}

void boardRefresh(bool white) {
    clearBuf();
    std::cout << (white ? "WHITE" : "BLACK") << " TURN\n\n";
    printBoard();
}

string getMove(string msg) {
    std::cout << msg << "\n>>> ";
    string move;
    std::cin >> move;

    if (!validFmt(move)) return "";

    int cX, cY, x, y;
    storeParsedCoords(move, cX, cY, x, y);

    Piece* piece = board[cX][cY];
    if (!piece->isValidMove(x, y)) return "";

    if (move.size() >= 5) {
        Pawn* pawn = dynamic_cast<Pawn*>(piece);
        if (pawn) pawn->setPromotion(move[4]);
    }

    piece->storeCurrentPos(cX, cY);
    if (leavesKingInCheck(cX, cY, x, y)) return "";

    return move;
}

void turn(bool white) {
    string move;
    int cX, cY, x, y;
    string moveMsg = "Enter move:";

    while (true) {
        boardRefresh(white);
        move = getMove(moveMsg);
        if (move.empty()) { moveMsg = "Invalid. Enter move:"; continue; }

        storeParsedCoords(move, cX, cY, x, y);

        break;
    }

    board[cX][cY]->move(x, y);
}

bool gameOver() {
    int dx[] = { 1, 1, 0,-1,-1,-1, 0, 1};
    int dy[] = { 0,-1,-1,-1, 0, 1, 1, 1};

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (board[r][c] == nullptr) continue;
            King* king = dynamic_cast<King*>(board[r][c]);
            if (king == nullptr) continue;

            int count = 0;
            for (int i = 0; i < 8; i++) {
                if (king->isValidMove(r + dx[i], c + dy[i]))
                    count++;
            }

            if (count > 0) continue;

            // King has no moves, check if any other friendly piece can move
            char color = king->getColor();
            for (int fr = 0; fr < 8; fr++) {
                for (int fc = 0; fc < 8; fc++) {
                    if (board[fr][fc] == nullptr) continue;
                    if (board[fr][fc]->getColor() != color) continue;
                    if (dynamic_cast<King*>(board[fr][fc]) != nullptr) continue;
                    for (int tx = 0; tx < 8; tx++)
                        for (int ty = 0; ty < 8; ty++)
                            if (board[fr][fc]->isValidMove(tx, ty) &&
                                !leavesKingInCheck(fr, fc, tx, ty))
                                goto nextKing;
                }
            }

            if (!king->isSafe(r, c))
                winner = color == 'w' ? 'b' : 'w';
            // stalemate: winner left empty
            return true;

            nextKing:;
        }
    }
    return false;
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
