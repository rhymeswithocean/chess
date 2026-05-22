#pragma once
#include "piece.h"

/**
 * Queen — moves any number of squares diagonally or in a straight line.
 */
class Queen : public Piece {
public:
    /** @param color 'w' for white, 'b' for black */
    Queen(char color) : Piece(color, 'Q') {}
    /** Returns true if (x, y) is reachable along a clear diagonal or straight line. */
    bool isValidMove(int x, int y) override;
};
