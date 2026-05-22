#include "piece.h"
#include<string>
#include<cstdlib>
using std::string;
using std::abs;


extern Piece* board[8][8];

Piece::Piece(char color, char shorthand) : color(color), shorthand(shorthand) {}

bool isSafe(int x, int y) { return true; }

bool Piece::canTake(int x, int y) {
    if (board[x][y] == nullptr || board[x][y]->getColor() == this->color) {
        return false;
    }
    return true;
}

bool willHit(int x, int y, int cX, int cY) {
    char type; // will be v(ertical), h(orizintal), or d(iagonal)
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

bool King::isValidMove(int x, int y) { 
    int cX, cY;
    storeCurrentPos(cX, cY);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    else if ((x == cX && y == cY) || abs(cX - x) > 1 || abs(cY - y) > 1) return false;
    else if (!isSafe(x, y)) return false;
    
    return true;
}

void King::move(int x, int y) {}

bool Queen::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    if (x == cX && y == cY) return false;

    bool isDiagonal = abs(cX - x) == abs(cY - y);
    bool isStraight = (x == cX || y == cY);

    if (!isDiagonal && !isStraight) return false;
    if (willHit(x, y, cX, cY)) return false;

    return true;
}
void Queen::move(int x, int y) {}

bool Rook::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    else if (x == cX && y == cY) return false;
    else if (x != cX && y != cY) return false;
    else if (willHit(x, y, cX, cY)) return false;

    return true;
}
void Rook::move(int x, int y) {}

bool Bishop::isValidMove(int x, int y) { 
    int cX, cY;
    storeCurrentPos(cX, cY);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    else if (x == cX && y == cY) return false;
    else if (abs(cX - x) != abs(cY - y)) return false;
    else if (willHit(x, y, cX, cY)) return false;

    return true;
}
void Bishop::move(int x, int y) {}

bool Knight::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    int deltaX = abs(cX - x);
    int deltaY = abs(cY - y);

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    else if ((deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1)) {
        return true;
    }

    return false; 
}
void Knight::move(int x, int y) {}

bool Pawn::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);
    int direction = (color == 'w') ? -1 : 1;
    int startRow  = (color == 'w') ?  6 : 1;

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
void Pawn::move(int x, int y) {}
