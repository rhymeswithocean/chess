#pragma once
#include "piece.h"

/**
 * Knight — moves in an L-shape: 2 squares in one axis and 1 in the other.
 * The only piece that can jump over other pieces.
 */
class Knight : public Piece {
public:
    /** @param color 'w' for white, 'b' for black */
    Knight(char color) : Piece(color, 'k') {}
    /** Returns true if (x, y) is exactly an L-shape (2+1 squares) away. */
    bool isValidMove(int x, int y) override;
};
