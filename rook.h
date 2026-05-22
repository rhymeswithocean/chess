#pragma once
#include "piece.h"

/**
 * Rook — moves any number of squares horizontally or vertically.
 */
class Rook : public Piece {
public:
    /** @param color 'w' for white, 'b' for black */
    Rook(char color) : Piece(color, 'r') {}
    /** Returns true if (x, y) is reachable along a clear horizontal or vertical line. */
    bool isValidMove(int x, int y) override;
};
