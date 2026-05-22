#pragma once
#include "piece.h"

/**
 * Bishop — moves any number of squares diagonally.
 */
class Bishop : public Piece {
public:
    /** @param color 'w' for white, 'b' for black */
    Bishop(char color) : Piece(color, 'b') {}
    /** Returns true if (x, y) is reachable along a clear diagonal. */
    bool isValidMove(int x, int y) override;
};
