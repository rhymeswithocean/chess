#include "pawn.h"
#include "queen.h"
#include <cstdlib>
using std::abs;

extern Piece* board[8][8];

bool Pawn::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);
    const int direction = (color == 'w') ? 1 : -1;
    const int startRow  = (color == 'w') ? 1 :  6;

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    if (x == cX && y == cY) return false;

    int dx = x - cX;
    int dy = abs(y - cY);

    // Diagonal capture: 1 forward, 1 sideways, enemy piece present
    if (dx == direction && dy == 1)
        return board[x][y] != nullptr && board[x][y]->getColor() != color;

    // All remaining moves must stay in the same column
    if (y != cY) return false;

    // 1 square forward: destination must be empty
    if (dx == direction)
        return board[x][y] == nullptr;

    // 2 squares forward from starting row: both squares must be empty
    if (dx == 2 * direction && cX == startRow)
        return board[x][y] == nullptr && board[cX + direction][cY] == nullptr;

    return false;
}

void Pawn::move(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    delete board[x][y];
    if (x == 7)
        board[x][y] = new Queen(color);
    else
        board[x][y] = this;

    board[cX][cY] = nullptr;
    hasMoved = true;
}
