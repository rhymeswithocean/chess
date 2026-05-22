#pragma once
#include "piece.h"

/**
 * Queen — moves any number of squares diagonally or in a straight line.
 */
class Queen : public Piece {
public:
    Queen(char color) : Piece(color, 'Q') {}
    bool isValidMove(int x, int y) override;
};
