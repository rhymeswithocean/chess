#pragma once
#include "piece.h"

/**
 * Rook — moves any number of squares horizontally or vertically.
 */
class Rook : public Piece {
public:
    Rook(char color) : Piece(color, 'r') {}
    bool isValidMove(int x, int y) override;
};
