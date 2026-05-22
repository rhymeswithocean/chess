#include "bishop.h"
#include <cstdlib>
using std::abs;

extern Piece* board[8][8];

bool Bishop::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    else if (x == cX && y == cY) return false;
    else if (abs(cX - x) != abs(cY - y)) return false;
    else if (board[x][y] != nullptr && board[x][y]->getColor() == color) return false;
    else if (willHit(x, y, cX, cY)) return false;

    return true;
}
