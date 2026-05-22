#pragma once
#include "piece.h"

/**
 * Knight — moves in an L-shape: 2 squares in one axis and 1 in the other.
 * The only piece that can jump over other pieces.
 */
class Knight : public Piece {
public:
    Knight(char color) : Piece(color, 'k') {}
    bool isValidMove(int x, int y) override;
};
