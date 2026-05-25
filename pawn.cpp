#include "pawn.h"
#include "boardHelper.h"
#include "queen.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include <cstdlib>
#include <iostream>
using std::abs;

extern Piece* board[8][8];
extern Piece* epPawn;

bool Pawn::isValidMove(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);
    const int direction = (color == 'w') ? 1 : -1;
    const int startRow  = (color == 'w') ? 1 :  6;

    if (x > 7 || x < 0 || y > 7 || y < 0) return false;
    if (x == cX && y == cY) return false;

    int dy = y - cY;        // signed rank change — forward direction
    int dx = abs(x - cX);  // absolute file change — sideways

    // Diagonal capture: 1 forward, 1 sideways, enemy piece present
    if (dy == direction && dx == 1) {
        if (board[x][y] != nullptr && board[x][y]->getColor() != color) return true;
        // En passant: destination is empty but the adjacent pawn just moved two squares
        if (epPawn != nullptr && board[x][y] == nullptr) {
            int epX, epY;
            epPawn->storeCurrentPos(epX, epY);
            if (epX == x && epY == cY) return true;
        }
        return false;
    }

    // All remaining moves must stay in the same file
    if (x != cX) return false;

    // 1 square forward: destination must be empty
    if (dy == direction)
        return board[x][y] == nullptr;

    // 2 squares forward from starting rank: both squares must be empty
    if (dy == 2 * direction && cY == startRow)
        return board[x][y] == nullptr && board[cX][cY + direction] == nullptr;

    return false;
}

Piece* Pawn::makePromotion(char c) {
    switch (c) {
        case 'Q': return new Queen(color);
        case 'k': return new Knight(color);
        case 'r': return new Rook(color);
        case 'b': return new Bishop(color);
        default:  return promoteChoice("Invalid. Promote your pawn (Q=queen, k=knight, r=rook, b=bishop):");
    }
}

Piece* Pawn::promoteChoice(string msg) {
    std::cout << "\n\n" << msg << "\n>>> ";
    char c;
    std::cin >> c;
    return makePromotion(c);
}

void Pawn::move(int x, int y) {
    int cX, cY;
    storeCurrentPos(cX, cY);

    // En passant capture: diagonal move to empty square — remove the captured pawn
    if (x != cX && board[x][y] == nullptr) {
        delete board[x][cY];
        board[x][cY] = nullptr;
    }

    epPawn = (abs(y - cY) == 2) ? this : nullptr;

    delete board[x][y];
    if (y == 7 || y == 0) {
        Piece* promoted;
        if (pendingPromotion != '\0') {
            promoted = makePromotion(pendingPromotion);
            pendingPromotion = '\0';
        } else {
            promoted = promoteChoice("Promote your pawn (q=queen, k=knight, r=rook, b=bishop):");
        }
        board[x][y] = promoted;
    } else {
        board[x][y] = this;
    }

    board[cX][cY] = nullptr;
    hasMoved = true;
}
