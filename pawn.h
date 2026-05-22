#pragma once
#include "piece.h"

/**
 * Pawn — moves 1 square forward, or 2 squares forward from its starting row.
 * Captures diagonally 1 square forward. Cannot capture on a forward move.
 * White moves toward higher row indices; black moves toward lower row indices.
 * Automatically promotes to a Queen upon reaching the back rank.
 */
class Pawn : public Piece {
public:
    Pawn(char color) : Piece(color, 'p') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};
