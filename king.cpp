#include "king.h"
#include "rook.h"
#include <cstdlib>
using std::abs;

extern Piece* board[8][8];

bool King::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    else if ((x == cX && y == cY) || abs(cX - x) > 1 || abs(cY - y) > 1) return false;
    else if (board[x][y] != nullptr && board[x][y]->getColor() == color) return false;
    else if (dynamic_cast<King*>(board[x][y]) != nullptr) return false;
    else if (!isSafe(x, y)) return false;

    return true;
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

    board[6][y] = this;
    board[5][y] = board[rX][y];
    board[kX][y] = nullptr;
    board[rX][y] = nullptr;
    return true;
}
