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

bool validLoc(string loc) {
    if (loc.size() < 2) return false;
    if (!(loc[0] >= 'a' && loc[0] <= 'h')) return false;
    if (!(loc[1] >= '1' && loc[1] <= '8')) return false;
    return true;
}

void storeParsedCoord(string coord, int& x, int& y) {
    x = coord[0] - 'a';
    y = coord[1] - '1';
}

// Step 1: simulate a move, check if the moving side's king is left in check, then undo
bool leavesKingInCheck(int fromX, int fromY, int toX, int toY) {
    Piece* moving  = board[fromX][fromY];
    Piece* target  = board[toX][toY];
    char   color   = moving->getColor();

    // En passant: pawn moves diagonally to an empty square — side-captured pawn must also vanish
    Piece* epCaptured = nullptr;
    if (dynamic_cast<Pawn*>(moving) && fromX != toX && target == nullptr) {
        epCaptured       = board[toX][fromY];
        board[toX][fromY] = nullptr;
    }

    board[toX][toY]     = moving;
    board[fromX][fromY] = nullptr;

    bool inCheck = false;
    for (int r = 0; r < 8 && !inCheck; r++)
        for (int c = 0; c < 8 && !inCheck; c++)
            if (board[r][c] && dynamic_cast<King*>(board[r][c]) &&
                board[r][c]->getColor() == color &&
                !board[r][c]->isSafe(r, c))
                inCheck = true;

    board[fromX][fromY] = moving;
    board[toX][toY]     = target;
    if (epCaptured) board[toX][fromY] = epCaptured;

    return inCheck;
}

string getPiece(bool white, string msg) {
    std::cout << msg << "\n>>> ";
    string piece;
    std::cin >> piece;
    if (!validLoc(piece)) return "";
    int x, y;
    storeParsedCoord(piece, x, y);
    if (board[x][y] == nullptr || board[x][y]->getColor() != (white ? 'w' : 'b')) return "";
    return piece;
}

string getMove(Piece* piece, string msg) {
    std::cout << msg << "\n>>> ";
    string move;
    std::cin >> move;
    if (!validLoc(move)) return "";
    int x, y;
    storeParsedCoord(move, x, y);
    if (!piece->isValidMove(x, y)) return "";
    int fromX, fromY;
    piece->storeCurrentPos(fromX, fromY);
    if (leavesKingInCheck(fromX, fromY, x, y)) return "";
    return move;
}

void turn(bool white) {
    extern Piece* epPawn;
    epPawn = nullptr;

    string from, to;
    int cX, cY;
    string pieceMsg = "Enter piece to move:";

    while (true) {
        clearBuf();
        std::cout << (white ? "WHITE" : "BLACK") << " TURN\n\n";
        printBoard();
        from = getPiece(white, pieceMsg);
        if (from.empty()) { pieceMsg = "Invalid. Enter piece to move:"; continue; }
        storeParsedCoord(from, cX, cY);

        string moveMsg = "Enter move:";
        while (true) {
            clearBuf();
            std::cout << (white ? "WHITE" : "BLACK") << " TURN\n\n";
            printBoard();
            std::cout << "Moving: " << from << "\n";
            to = getMove(board[cX][cY], moveMsg);
            if (!to.empty()) break;
            moveMsg = "Invalid. Enter move:";
        }
        break;
    }

    int nX, nY;
    storeParsedCoord(to, nX, nY);
    board[cX][cY]->move(nX, nY);
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

            // King has no moves — check if any other friendly piece can move
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
