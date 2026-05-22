#include "knight.h"
#include <cstdlib>
using std::abs;

extern Piece* board[8][8];

bool Knight::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    int deltaX = abs(cX - x);
    int deltaY = abs(cY - y);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    if (board[x][y] != nullptr && board[x][y]->getColor() == color) return false;
    if ((deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1)) return true;

    return false;
}
