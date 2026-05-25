#pragma once
#include "piece.h"

/**
 * Pawn — moves 1 square forward, or 2 squares forward from its starting rank.
 * Captures diagonally 1 square forward. Supports en passant against a pawn
 * that just advanced two squares. Promotes to a Queen on reaching the back rank.
 * White moves toward higher rank indices; black toward lower.
 */
class Pawn : public Piece {
public:
    /** @param color 'w' for white, 'b' for black */
    Pawn(char color) : Piece(color, 'p') {}
    /** Returns true if (x, y) is a legal forward move, diagonal capture, or en passant. */
    bool isValidMove(int x, int y) override;
    /** Moves the pawn; handles en passant capture and promotes on the back rank. */
    void move(int x, int y) override;
    /** Sets the promotion piece for the next move (inline syntax, e.g. b7b8k). */
    void setPromotion(char c) { pendingPromotion = c; }
private:
    char pendingPromotion = '\0';
    Piece* makePromotion(char c);
    Piece* promoteChoice(string msg);
};
