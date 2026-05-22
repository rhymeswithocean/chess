#include "queen.h"
#include <cstdlib>
using std::abs;

extern Piece* board[8][8];

bool Queen::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    if (x == cX && y == cY) return false;
    if (board[x][y] != nullptr && board[x][y]->getColor() == color) return false;

    bool isDiagonal = abs(cX - x) == abs(cY - y);
    bool isStraight = (x == cX || y == cY);

    if (!isDiagonal && !isStraight) return false;
    if (willHit(x, y, cX, cY)) return false;

    return true;
}
