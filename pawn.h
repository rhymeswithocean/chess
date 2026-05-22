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
    /** @param color 'w' for white, 'b' for black */
    Pawn(char color) : Piece(color, 'p') {}
    /** Returns true if (x, y) is a legal forward move or diagonal capture. */
    bool isValidMove(int x, int y) override;
    /** Moves the pawn, promoting it to a Queen if it reaches the back rank. */
    void move(int x, int y) override;
};
