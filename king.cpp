#include "king.h"
#include "rook.h"
#include <cstdlib>
using std::abs;

extern Piece* board[8][8];

bool King::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    if (x == cX && y == cY) return false;

    // Castling: king unmoved, destination is the castling square on the home rank
    if (!hasMoved && y == cY) {
        int ry = color == 'w' ? 0 : 7;
        if (cY == ry) {
            if (x == 6) {
                Rook* r = dynamic_cast<Rook*>(board[7][ry]);
                if (r && !r->getHasMoved() && !board[5][ry] && !board[6][ry] &&
                    isSafe(cX, ry) && isSafe(5, ry) && isSafe(6, ry))
                    return true;
            }
            if (x == 2) {
                Rook* r = dynamic_cast<Rook*>(board[0][ry]);
                if (r && !r->getHasMoved() &&
                    !board[1][ry] && !board[2][ry] && !board[3][ry] &&
                    isSafe(cX, ry) && isSafe(3, ry) && isSafe(2, ry))
                    return true;
            }
        }
    }

    if (abs(cX - x) > 1 || abs(cY - y) > 1) return false;
    if (board[x][y] != nullptr && board[x][y]->getColor() == color) return false;
    if (dynamic_cast<King*>(board[x][y]) != nullptr) return false;
    if (!isSafe(x, y)) return false;

    return true;
}

void King::move(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);
    if (abs(x - cX) == 2) {
        if (x > cX) shortCastle();
        else longCastle();
        hasMoved = true;
        return;
    }
    Piece::move(x, y);
}

bool King::longCastle() {
    int cX, cY;
    storeCurrentPos(cX, cY);

    int y = color == 'w' ? 0 : 7;
    int kX = 4;
    int rX = 0;

    if (cX != kX || cY != y) return false;
    else if (hasMoved) return false;
    else if (dynamic_cast<Rook*>(board[rX][y]) == nullptr) return false;
    else if (dynamic_cast<Rook*>(board[rX][y])->getHasMoved()) return false;

    for (int i = 1; i <= 3; i++) {
        if (board[kX - i][y] != nullptr) return false;
    }
    if (!isSafe(kX, y) || !isSafe(3, y) || !isSafe(2, y)) return false;

    board[2][y] = this;
    board[3][y] = board[rX][y];
    board[kX][y] = nullptr;
    board[rX][y] = nullptr;
    return true;
}

bool King::shortCastle() {
    int cX, cY;
    storeCurrentPos(cX, cY);

    int y = color == 'w' ? 0 : 7;
    int kX = 4;
    int rX = 7;

    if (cX != kX || cY != y) return false;
    else if (hasMoved) return false;
    else if (dynamic_cast<Rook*>(board[rX][y]) == nullptr) return false;
    else if (dynamic_cast<Rook*>(board[rX][y])->getHasMoved()) return false;

    for (int i = 1; i <= 2; i++) {
        if (board[kX + i][y] != nullptr) return false;
    }
    if (!isSafe(kX, y) || !isSafe(5, y) || !isSafe(6, y)) return false;

    board[6][y] = this;
    board[5][y] = board[rX][y];
    board[kX][y] = nullptr;
    board[rX][y] = nullptr;
    return true;
}
