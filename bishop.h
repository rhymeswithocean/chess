#pragma once
#include "piece.h"

/**
 * Bishop — moves any number of squares diagonally.
 */
class Bishop : public Piece {
public:
    Bishop(char color) : Piece(color, 'b') {}
    bool isValidMove(int x, int y) override;
};
