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
    /** Returns true if (x, y) is a legal king move, including castling. */
    bool isValidMove(int x, int y) override;
    /** Moves the king, executing castling when a two-square horizontal move is detected. */
    void move(int x, int y) override;
    /**
     * Performs queenside castling if legal. Returns true on success.
     */
    bool longCastle();
    /**
     * Performs kingside castling if legal. Returns true on success.
     */
    bool shortCastle();
};
