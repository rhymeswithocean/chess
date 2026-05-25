#include "piece.h"
#include <string>
#include <cstdlib>
using std::string;
using std::abs;

Piece::Piece(char color, char shorthand) : color(color), shorthand(shorthand) {}

bool Piece::isSafe(int x, int y) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = board[r][c];
            if (!p || p->getColor() == color) continue;

            // King handled separately — calling its isValidMove would call
            // isSafe again, causing infinite recursion
            if (p->getShorthand() == 'K') {
                if (abs(r - x) <= 1 && abs(c - y) <= 1) return false;
                continue;
            }

            if (p->isValidMove(x, y)) return false;
        }
    }
    return true;
}

bool Piece::canTake(int x, int y) {
    if (board[x][y] == nullptr || board[x][y]->getColor() == this->color) {
        return false;
    }
    return true;
}

bool willHit(int x, int y, int cX, int cY) {
    char type;
    if (cX == x) type = 'v';
    else if (cY == y) type = 'h';
    else if (abs(cX - x) == abs(cY - y)) type = 'd';
    else return true;

    int end;
    if (type == 'v') end = abs(cY - y) - 1;
    else end = abs(cX - x) - 1;

    int multX;
    if (x - cX < 0) multX = -1;
    else multX = 1;

    int multY;
    if (y - cY < 0) multY = -1;
    else multY = 1;

    for (int i = 1; i <= end; i++) {
        if (type == 'v') {
            if (board[x][cY + (i * multY)] != nullptr) return true;
        } else if (type == 'h') {
            if (board[cX + (i * multX)][y] != nullptr) return true;
        } else if (type == 'd') {
            if (board[cX + (i * multX)][cY + (i * multY)] != nullptr) return true;
        }
    }
    return false;
}

string Piece::toString() const { return {color, shorthand}; }

std::ostream& operator<<(std::ostream& os, const Piece& p) {
    os << p.toString();
    return os;
}

void Piece::storeCurrentPos(int& x, int& y) {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[r][c] == this) {
                x = r;
                y = c;
                return;
            }
}

void Piece::move(int x, int y) {
    extern Piece* epPawn;
    epPawn = nullptr;

    int cX, cY;
    storeCurrentPos(cX, cY);

    delete board[x][y];
    board[x][y] = this;
    board[cX][cY] = nullptr;
    hasMoved = true;
}
