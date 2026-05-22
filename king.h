#pragma once
#include "piece.h"

/**
 * King — moves exactly 1 square in any direction.
 * Also supports castling via longCastle() and shortCastle().
 */
class King : public Piece {
public:
    /** @param color 'w' for white, 'b' for black */
    King(char color) : Piece(color, 'K') {}
    /** Returns true if (x, y) is within 1 square in any direction and is safe. */
    bool isValidMove(int x, int y) override;
    /**
     * Performs queenside castling if legal. Returns true on success.
     */
    bool longCastle();
    /**
     * Performs kingside castling if legal. Returns true on success.
     */
    bool shortCastle();
};
